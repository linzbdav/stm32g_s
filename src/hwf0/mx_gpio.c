/**
  ******************************************************************************
  * File Name          : mx_gpio.c
  * Date               : 24/02/2014 17:46:28
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  *
  * COPYRIGHT 2014 STMicroelectronics
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
#include "mx_gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

void mx_pinout_config(void) {
	/* Private typedef ---------------------------------------------------------*/
	GPIO_InitTypeDef GPIO_InitStruct;


	/** I2C1 GPIO Configuration	
		 PB8	 ------> I2C1_SCL
		 PB9	 ------> I2C1_SDA
	*/
	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_1);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_1);


	/** SPI2 GPIO Configuration	
		 PB13	 ------> SPI2_SCK
		 PB14	 ------> SPI2_MISO
		 PB15	 ------> SPI2_MOSI
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_0);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_0);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_0);


	/** SYS GPIO Configuration	
		 PF0-OSC_IN	 ------> SYS_OSC_IN
		 PF1-OSC_OUT	 ------> SYS_OSC_OUT
		 PA13	 ------> SYS_SWDAT
		 PA14	 ------> SYS_SWCLK
	*/



	/** USART1 GPIO Configuration	
		 PB6	 ------> USART1_TX
		 PB7	 ------> USART1_RX
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);

	/*Configure GPIO pin alternate function */
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);


	/** Configure pins as GPIO
		 PC13	 ------> GPIO_Input
		 PC14-OSC32_IN	 ------> GPIO_Output
		 PC15-OSC32_OUT	 ------> GPIO_Output
		 PA0	 ------> GPIO_Output
		 PA1	 ------> GPIO_Input
		 PA2	 ------> GPIO_Input
		 PA3	 ------> GPIO_Output
		 PA4	 ------> GPIO_Output
		 PA5	 ------> GPIO_Input
		 PA6	 ------> GPIO_Input
		 PA7	 ------> GPIO_Output
		 PB0	 ------> GPIO_Output
		 PB1	 ------> GPIO_Input
		 PB2	 ------> GPIO_Input
		 PB10	 ------> GPIO_Output
		 PB11	 ------> GPIO_Output
		 PB12	 ------> GPIO_Output
		 PA8	 ------> GPIO_Output
		 PA9	 ------> GPIO_Output
		 PA10	 ------> GPIO_Input
		 PA11	 ------> GPIO_Input
		 PA12	 ------> GPIO_Input
		 PF6	 ------> GPIO_Input
		 PF7	 ------> GPIO_Input
		 PA15	 ------> GPIO_Output
		 PB3	 ------> GPIO_Output
		 PB4	 ------> GPIO_Output
		 PB5	 ------> GPIO_Output
	*/


	/*Enable or disable the AHB peripheral clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOF, ENABLE);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
