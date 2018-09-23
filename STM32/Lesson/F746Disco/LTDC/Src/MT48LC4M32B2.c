#include "MT48LC4M32B2.h"
#include "stm32f7xx_ll_fmc.h"
#include "stm32f7xx_hal_sdram.h"
# include "stm32f7xx_hal_dma.h"
#include "stm32f7xx_hal_def.h"
#include "stm32f7xx_hal_dma_ex.h"




extern SDRAM_HandleTypeDef hsdram1;
FMC_SDRAM_CommandTypeDef command;
HAL_StatusTypeDef hal_stat;


/*********************Функция инициализации SDRAM************************/
void MT48LC4M32B2_Init(void)
{
	__IO uint32_t tmpmrd =0;
  command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;//вкл.тактирование
  command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;//обращение к первому банку 
  command.AutoRefreshNumber = 1;//автообновления
  command.ModeRegisterDefinition = 0;
  hal_stat = HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);//запись в регистр
  HAL_Delay(1);
	command.CommandMode = FMC_SDRAM_CMD_PALL;//деактивирует все банки памяти перед регенеацией 
  command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  command.AutoRefreshNumber = 1;//автообновления
  command.ModeRegisterDefinition = 0;
  hal_stat = HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);//запись в регистр
	HAL_Delay(1);
	command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;//задаём режим автоорегенерации, необходимый для нормального функционирования SDRAM
  command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  command.AutoRefreshNumber = 8;
  command.ModeRegisterDefinition = 0;
  hal_stat = HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);
  HAL_Delay(1);
	//включаем размер пакета, последовательный режим передачи, латентность 2 такта, стандартный режим, одиночный режим записи пакета
	 tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_2           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
  command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  command.AutoRefreshNumber = 1;
  command.ModeRegisterDefinition = tmpmrd;
  hal_stat = HAL_SDRAM_SendCommand(&hsdram1, &command, SDRAM_TIMEOUT);
	 /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) — 20 */
  /* Set the device refresh counter */
  hsdram1.Instance->SDRTR |= ((uint32_t)((1292)<< 1));
	
}




