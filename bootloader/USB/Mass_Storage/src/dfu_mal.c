/**
  ******************************************************************************
  * @file    dfu_mal.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Generic media access Layer
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "dfu_mal.h"
#include "usb_lib.h"
#include "usb_type.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t  MAL_Buffer[wTransferSize]; /* RAM Buffer for Downloaded Data */


extern ONE_DESCRIPTOR DFU_String_Descriptor[7];

static const uint16_t  TimingTable[5][2] =
  { /*       Sector Erase time,            Sector Program time*/    
    { SPI_FLASH_SECTOR_ERASE_TIME,    SPI_FLASH_SECTOR_WRITE_TIME },    /* SPI Flash */
    { M29W128F_SECTOR_ERASE_TIME,     M29W128F_SECTOR_WRITE_TIME },     /* NOR Flash M29W128F */
    { INTERN_FLASH_SECTOR_ERASE_TIME, INTERN_FLASH_SECTOR_WRITE_TIME }, /* Internal Flash */
    { M29W128G_SECTOR_ERASE_TIME,     M29W128G_SECTOR_WRITE_TIME },     /* NOR Flash M29W128G */
    { S29GL128_SECTOR_ERASE_TIME,     S29GL128_SECTOR_WRITE_TIME }      /* NOR Flash S29GL128 */
  };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(void)	//初始化存储设备用
{
	return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Erase
* Description    : Erase sector
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Erase(uint32_t SectorAddress)	//存储设备擦除调用函数
{
	FLASH_ErasePage(SectorAddress);	//选择页擦除函数

	return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write (uint32_t SectorAddress, uint32_t DataLength)	//往FLASH写入数据
{
	uint32_t idx = 0;

	if(DataLength & 0x3)	//数据对齐
	{
		for(idx = DataLength; idx < ((DataLength & 0xFFFC) + 4); idx++)
		{
			MAL_Buffer[idx] = 0xFF;
		}
	}

	//开始写入DataLength长度数据    
	for (idx = 0; idx <  DataLength; idx = idx + 4)
	{
		FLASH_ProgramWord(SectorAddress, *(uint32_t *)(MAL_Buffer + idx));  
		SectorAddress += 4;
	}

	return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint8_t *MAL_Read (uint32_t SectorAddress, uint32_t DataLength)	//读取FLASH数据
{
	return (uint8_t*)SectorAddress;
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_GetStatus(uint32_t SectorAddress , uint8_t Cmd, uint8_t *buffer)	//读取FLASH操作状态
{
	 uint8_t x = (SectorAddress  >> 26) & 0x03 ; /* 0x000000000 --> 0 */
  /* 0x640000000 --> 1 */
  /* 0x080000000 --> 2 */

  uint8_t y = Cmd & 0x01;
  SET_POLLING_TIMING(TimingTable[x][y]);  /* x: Erase/Write Timing */
  /* y: Media              */
  return MAL_OK;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
