#include "LSM6DS0.h"

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;
uint8_t buf2[14]={0};
char str1[400]={0};



/**********************Функция индикации ошибки***************/
void Error(void)
{
	LD2_OFF;
}

/********************Функция чтения из регистра*************/
static uint8_t I2Cx_ReadData(uint16_t Addr,uint8_t Reg)
{
	HAL_StatusTypeDef status=HAL_OK;
	uint8_t value=0;
	status=HAL_I2C_Mem_Read(&hi2c1,Addr,Reg,I2C_MEMADD_SIZE_8BIT,&value,1,0x10000);
	if(status != HAL_OK) Error();
  return value;
}

/**************************Функция записи в регистр*********************/
static void I2Cx_WriteData(uint16_t Addr,uint8_t reg,uint8_t Value)
{
	HAL_StatusTypeDef status=HAL_OK;
	
	status=HAL_I2C_Mem_Write(&hi2c1,Addr,reg,I2C_MEMADD_SIZE_8BIT,&Value,1,0x10000);
	if(status!=HAL_OK)
	{
		Error();
	}
}

/***********************Функция чтения**************************/
uint8_t Accel_IO_Read(uint16_t DeviceAddr, uint8_t RegisterAddr)
{
  return I2Cx_ReadData(DeviceAddr, RegisterAddr);
}

/*************************Функция записи*************************/
void Accel_IO_Write(uint16_t DeviceAddr, uint8_t RegisterAddr,uint8_t Value)
{
	I2Cx_WriteData(DeviceAddr,RegisterAddr,Value);
}

/******************Функция получения значений в буффер************/
void Accel_GetXYZ(int16_t* pData)
{
        uint8_t buffer[6];
        uint8_t i=0;
		 buffer[0] = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_X_L_XL);
        buffer[1] = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_X_H_XL);
        buffer[2] = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Y_L_XL);
        buffer[3] = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Y_H_XL);
        buffer[4] = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Z_L_XL);
        buffer[5] = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Z_H_XL);
        for(i=0;i<3;i++)
        {
			pData[i] = ((int16_t)((uint16_t)buffer[2*i+1]<<8)+buffer[2*i]);
        }
}


/******************Функция получения значений в буффер из гироскопа************/
void Gyro_GetXYZ(int16_t* pData)
{
	uint8_t buffer[6];
	uint8_t i=0;
	buffer[0]=Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_X_L_G);
	buffer[1]=Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_X_H_G);
	buffer[2]=Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Y_L_G);
	buffer[3]=Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Y_H_G);
	buffer[4]=Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Z_L_G);
	buffer[5]=Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_OUT_Z_H_G);
	for(i=0;i<3;i++)
	{
		pData[i] = ((int16_t)((uint16_t)buffer[2*i+1]<<8)+buffer[2*i]);
	}
}





/**************************Функция чтения индификатора***************/
uint8_t Accel_ReadID(void)
{
        uint8_t ctrl = 0x00;
		ctrl=Accel_IO_Read(0xD6,0x0F);
        return ctrl;
}


/************Получение значений от акселерометра************/
void GETValueAccel_Read(void)
{
	int16_t buffer[3] = {0};
    int16_t xval, yval, zval;
	Accel_GetXYZ(buffer);
	 xval=buffer[0];
     yval=buffer[1];
     zval=buffer[2];
	sprintf(str1,"Accel-X:%06d Y:%06d Z:%06d\r\n", xval, yval, zval);
    HAL_UART_Transmit_DMA(&huart2, (uint8_t*)str1,strlen(str1));
//        buf2[0]=0x12;
//        buf2[1]=0x10;
//        buf2[2]=(uint8_t)(xval>>8);
//        buf2[3]=(uint8_t)xval;
//        buf2[4]=0x10;
//        buf2[5]=0x10;
//        buf2[6]=(uint8_t)(zval>>8);
//        buf2[7]=(uint8_t)zval;
//        buf2[8]=0x13;
//        HAL_UART_Transmit(&huart2,buf2,9,0x1000);
        if(xval>1500)
        {
			  LD2_ON;
        }
		else
		{
			 LD2_OFF;
		}
        HAL_Delay(100);
	
}



/*************************Функция считывания данных с  гироскопа**********************/
void ReadGero(void)
{
	
	int16_t buffer[3] = {0};
	int16_t xval, yval, zval;
	Gyro_GetXYZ(buffer);
	xval=buffer[0]-103;
	yval=buffer[1]-47;
	zval=buffer[2]-41;
  sprintf(str1,"Gyro-X:%06d Y:%06d Z:%06d\r\n", xval, yval, zval);
  HAL_UART_Transmit_DMA(&huart2, (uint8_t*)str1,strlen(str1));
	
	if(zval>500)
	{
		LD2_ON;
	}
	else 
	{
		LD2_OFF;
	}
	HAL_Delay(200);
}



/******************Инициализация регистров*****************/
void AccInit(uint16_t InitStruct)
{
	//установим бит BDU
	uint8_t value=0;
	value = Accel_IO_Read(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG8);
	value &= ~LSM6DS0_ACC_GYRO_BDU_MASK;
	value |= LSM6DS0_ACC_GYRO_BDU_ENABLE;
	Accel_IO_Write(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG8, value);//пока выключим датчик (ODR_XL = 000)
	//пока выключим датчик (ODR_XL = 000)
	value = Accel_IO_Read(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG6_XL);
	value &= ~LSM6DS0_ACC_GYRO_ODR_XL_MASK;
	value |= LSM6DS0_ACC_GYRO_ODR_XL_POWER_DOWN;
	Accel_IO_Write(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG6_XL, value);
	//Full scale selection 2G
	value = Accel_IO_Read(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG6_XL);
	value &= ~LSM6DS0_ACC_GYRO_FS_XL_MASK;
	value |= LSM6DS0_ACC_GYRO_FS_XL_2g;
	Accel_IO_Write(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG6_XL, value);
	//Включим оси
	value = Accel_IO_Read(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG5_XL);     
	value &= ~(LSM6DS0_ACC_GYRO_XEN_XL_MASK |
													 LSM6DS0_ACC_GYRO_YEN_XL_MASK |
													 LSM6DS0_ACC_GYRO_ZEN_XL_MASK);
	value |= (LSM6DS0_ACC_GYRO_XEN_XL_ENABLE |
													LSM6DS0_ACC_GYRO_YEN_XL_ENABLE |
													LSM6DS0_ACC_GYRO_ZEN_XL_ENABLE);
	Accel_IO_Write(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG5_XL, value);
		//Включим Data Rate 119 Гц
	value = Accel_IO_Read(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG6_XL);
	value &= ~LSM6DS0_ACC_GYRO_ODR_XL_MASK;
	value |= LSM6DS0_ACC_GYRO_ODR_XL_119Hz;
	Accel_IO_Write(0xD6, LSM6DS0_ACC_GYRO_CTRL_REG6_XL, value);
}



/*************Функция инициализации регистров гироскопа***************/
void GyroInit(uint16_t InitStruct)
{
	uint8_t value = 0;
	//пока выключим датчик (ODR_XL = 000)
	value = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G);
	value&=~LSM6DS0_ACC_GYRO_ODR_G_MASK;
	value|=LSM6DS0_ACC_GYRO_ODR_G_POWER_DOWN;
	Accel_IO_Write(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G,value);
	//Full scale selection 500dps
	value = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G);
	value&=~LSM6DS0_ACC_GYRO_FS_G_MASK;
	value|=LSM6DS0_ACC_GYRO_FS_G_500dps;
	Accel_IO_Write(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G,value);
	//Включим оси
	value = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG4);
	value&=~(LSM6DS0_ACC_GYRO_XEN_G_ENABLE|\
					 LSM6DS0_ACC_GYRO_YEN_G_ENABLE|\
					 LSM6DS0_ACC_GYRO_ZEN_G_ENABLE);
	value|=(LSM6DS0_ACC_GYRO_XEN_G_MASK|\
					LSM6DS0_ACC_GYRO_YEN_G_MASK|\
					LSM6DS0_ACC_GYRO_ZEN_G_MASK);
	Accel_IO_Write(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG4,value);
	//Включим HPF и LPF (фильтрация)
	value = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG2_G);
	value&=~LSM6DS0_ACC_GYRO_OUT_SEL_MASK;
	value|=LSM6DS0_ACC_GYRO_OUT_SEL_USE_HPF_AND_LPF2;
	Accel_IO_Write(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG2_G,value);
	//Включим BW (пропускная способность). При 952 Гц настроек
	//будет пропускная способность 100 Гц
	value = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G);
	value&=~LSM6DS0_ACC_GYRO_BW_G_MASK;
	value|=LSM6DS0_ACC_GYRO_BW_G_ULTRA_HIGH;
	Accel_IO_Write(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G,value);
	//Включим Data Rate 952 Гц
	value = Accel_IO_Read(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G);
	value&=~LSM6DS0_ACC_GYRO_ODR_G_MASK;
	value|=LSM6DS0_ACC_GYRO_ODR_G_952Hz;
	Accel_IO_Write(0xD6,LSM6DS0_ACC_GYRO_CTRL_REG1_G,value);


}






/****************************Основная инициализация акселерометра************/
void Accel_Ini(void)
{
  uint16_t ctrl = 0x0000;
	if(Accel_ReadID()==0x68)
		
	{
		LD2_ON;
	}
	else Error();
	LD2_OFF;
  HAL_Delay(1000);
  AccInit(ctrl);
	 LD2_ON;

}

/****************************Основная инициализация гироскопа************/
void Gyro_Ini(void)
{
	uint16_t ctrl = 0x0000;
	if(Accel_ReadID()==0x68)
		
	{
		LD2_ON;
	}
	else Error();
	LD2_OFF;
  HAL_Delay(1000);
  GyroInit(ctrl);
	 LD2_ON;
}


