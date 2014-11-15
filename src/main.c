//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Steuerung eines Steppermotors.
// Schaltung    :
//---------------------------------------------------------------------------
// Hardware     : STM32F051
// Takt         : 48MHz
// Sprache      : ARM C
// Datum        : 26.09.2014
// Version      : 1
// Autor        : David Linzberger
//---------------------------------------------------------------------------
/* Includes */
#include "main.h"
#include "gpio.h"
#include "hardware.h"
#include "usart.h"
#include "spi.h"
//#include "segment.h"
#include "stepper.h"
//#include "encoder.h"
#include "controller.h"
#include "commands.h"
#include "switch.h"
/* Private typedef */
/* Private define */
/* Private macro */
/* Private variables */
volatile uint32_t system_millis;
volatile uint32_t wait_millis;
/* Private function prototypes */
/* Private functions */
void sys_tick_handler(void)
{
	system_millis++;
	if( SerialCommsTimer > 0 )
	{
		SerialCommsTimer--;
	}
	if( wait_millis != 0 )
	{
		wait_millis--;
	}
}

void wait_ms( uint8_t time )
{
	wait_millis = time;
	while( wait_millis > 0 );
}

uint32_t SysTickTimer_getValue()
{
	return system_millis;
}

void systick_init(void)
{
	systick_set_reload(48000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	// this done last
	systick_interrupt_enable();
}

void system_init(void)
{
	//rcc_clock_setup_in_hsi_out_48mhz();
	rcc_osc_on(HSE);
	rcc_wait_for_osc_ready(HSE);
	rcc_set_sysclk_source(HSE);
	
	rcc_set_ppre(RCC_CFGR_PPRE_NODIV);
	rcc_set_hpre(RCC_CFGR_HPRE_NODIV);
	
	flash_set_ws(FLASH_ACR_LATENCY_024_048MHZ);
	
	/* 16MHz * 3 / 1 = 48MHz */
	rcc_set_prediv( RCC_CFGR2_PREDIV_NODIV );
	rcc_set_pll_multiplication_factor(RCC_CFGR_PLLMUL_MUL3);
	
	RCC_CFGR |= RCC_CFGR_PLLSRC;
	RCC_CFGR &= ~RCC_CFGR_PLLSRC0;
	rcc_osc_on(PLL);
	rcc_wait_for_osc_ready(PLL);
	rcc_set_sysclk_source(PLL);
	
	rcc_ppre_frequency = 48000000;
	rcc_core_frequency = 48000000;
	
	systick_init();
}

void initApplication()
{
    system_init();

	hardware_init();
	switch_init();
	
	
	controller_init();
	stepper_init();
}

int main()
{
    initApplication();

    while(1)
    {
		controller_run();
    }

    return(0);
}
