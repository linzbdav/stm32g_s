//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Steuerung eines Steppermotors.
// Schaltung    :
//---------------------------------------------------------------------------
// Hardware     : STM32F051
// Takt         : 48MHz
// Sprache      : ARM C
// Datum        : 03.01.2014
// Version      : 1
// Autor        : David Linzberger
//---------------------------------------------------------------------------
#ifndef _SPI_H
#define _SPI_H
/* Includes */
/* Private typedef */
/* Private define */

#define SPIx			SPI2
#define SPIx_CLK		RCC_APB1Periph_SPI2
#define SPIx_IRQn		SPI2_IRQn

// Buffersize must be 2^n
/* Private macro */
/* Private variables */
/* Private function prototypes */
void spi_init();
uint16_t spi_rw( uint8_t, uint8_t );
/* Private functions */

#endif // _SPI_H
