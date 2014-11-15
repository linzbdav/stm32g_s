//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Steuerung eines Steppermotors.
// Schaltung    :
//---------------------------------------------------------------------------
// Hardware     : STM32F051
// Takt         : 48MHz
// Sprache      : ARM C
// Datum        : 20.09.2014
// Version      : 1
// Autor        : David Linzberger
//---------------------------------------------------------------------------
/* Includes */
#include "main.h"
#include "controller.h"
#include "gpio.h"

/* Private typedef */
/* Private define */
/* Private macro */
/* Private variables */
/* Private function prototypes */
static void _clock_config();
static void _gpio_setup();

/* Public functions */
void pinout_config(void)
{
	_clock_config();
	_gpio_setup();
}


/* Private functions */
static void _clock_config(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);	
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOF);
}

static void _gpio_setup(void)
{
	/** I2C1 GPIO Configuration	
		 PB8	 ------> I2C1_SCL
		 PB9	 ------> I2C1_SDA
	*/
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8 | GPIO9 );
	gpio_set_output_options( GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO8 | GPIO9 );
	gpio_set_af(GPIOB, GPIO_AF1, GPIO8);
	gpio_set_af(GPIOB, GPIO_AF1, GPIO9);
	
	/** SPI2 GPIO Configuration
	 *   PB13    ------> SPI2_SCK
	 *   PB14    ------> SPI2_MISO
	 *   PB15    ------> SPI2_MOSI
	 */
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO13|GPIO14|GPIO15 );
	gpio_set_output_options( GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_HIGH, GPIO13|GPIO14|GPIO15 );
	gpio_set_af(GPIOB, GPIO_AF0, GPIO13 );
	gpio_set_af(GPIOB, GPIO_AF0, GPIO14 );
	gpio_set_af(GPIOB, GPIO_AF0, GPIO15 );
	
	/** USART1 GPIO Configuration
	 *   PB6     ------> USART1_TX
	 *   PB7     ------> USART1_RX
	 */
	gpio_mode_setup(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6|GPIO7 );
	gpio_set_output_options( GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO6|GPIO7 );
	gpio_set_af(GPIOB, GPIO_AF0, GPIO6 );
	gpio_set_af(GPIOB, GPIO_AF0, GPIO7 );
	
	/** Configure pins as GPIO
	 *	 PC13	 ------> GPIO_Input
	 *	 PC14-OSC32_IN	 ------> GPIO_Output
	 *	 PC15-OSC32_OUT	 ------> GPIO_Output
	 *	 PA0	 ------> GPIO_Output
	 *	 PA1	 ------> GPIO_Input
	 *	 PA2	 ------> GPIO_Input
	 *	 PA3	 ------> GPIO_Output
	 *	 PA4	 ------> GPIO_Output
	 *	 PA5	 ------> GPIO_Input
	 *	 PA6	 ------> GPIO_Input
	 *	 PA7	 ------> GPIO_Output
	 *	 PB0	 ------> GPIO_Output
	 *	 PB1	 ------> GPIO_Input
	 *	 PB2	 ------> GPIO_Input
	 *	 PB10	 ------> GPIO_Output
	 *	 PB11	 ------> GPIO_Output
	 *	 PB12	 ------> GPIO_Output
	 *	 PA8	 ------> GPIO_Output
	 *	 PA9	 ------> GPIO_Output
	 *	 PA10	 ------> GPIO_Input
	 *	 PA11	 ------> GPIO_Input
	 *	 PA12	 ------> GPIO_Input
	 *	 PF6	 ------> GPIO_Input
	 *	 PF7	 ------> GPIO_Input
	 *	 PA15	 ------> GPIO_Output
	 *	 PB3	 ------> GPIO_Output
	 *	 PB4	 ------> GPIO_Output
	 *	 PB5	 ------> GPIO_Output
	 */
	gpio_mode_setup(GPIOC, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO13 );
	gpio_set_output_options( GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO13 );
	
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14|GPIO15 );
	gpio_set_output_options( GPIOC, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO14|GPIO15 );
	
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0|GPIO3|GPIO4|GPIO7|GPIO8|GPIO9|GPIO15 );
	gpio_set_output_options( GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO0|GPIO3|GPIO4|GPIO7|GPIO8|GPIO9|GPIO15 );
	
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO1|GPIO2|GPIO5|GPIO6|GPIO10|GPIO11|GPIO12 );
	gpio_set_output_options( GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO1|GPIO2|GPIO5|GPIO6|GPIO10|GPIO11|GPIO12 );
	
	gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO0|GPIO10|GPIO11|GPIO12|GPIO3|GPIO4|GPIO5 );
	gpio_set_output_options( GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO0|GPIO10|GPIO11|GPIO12|GPIO3|GPIO4|GPIO5 );
	
	gpio_mode_setup(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO1|GPIO2 );
	gpio_set_output_options( GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO1|GPIO2 );
	
	gpio_mode_setup(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO6|GPIO7 );
	gpio_set_output_options( GPIOF, GPIO_OTYPE_PP, GPIO_OSPEED_MED, GPIO6|GPIO7 );
}
