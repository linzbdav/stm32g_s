#include "main.h"
#include "spi.h"

void spi_init(void)
{
	/* Enable the SPI periph */
	rcc_periph_clock_enable( RCC_SPI2 ); 

	/* SPI configuration */
	/*
	spi_set_master_mode( SPI2_BASE );
	spi_set_baudrate_prescaler( SPI2_BASE, SPI_CR1_BR_FPCLK_DIV_32 );
	spi_set_clock_polarity_0( SPI2_BASE );
	spi_set_clock_phase_1( SPI2_BASE );
	spi_set_full_duplex_mode( SPI2_BASE );
	spi_set_unidirectional_mode( SPI2_BASE );
	spi_set_data_size( SPI2_BASE, SPI_CR2_DS_16BIT );
	spi_send_msb_first( SPI2_BASE );
	spi_set_nss_high( SPI2_BASE );
	// spi_enable_ss_output( SPI2_BASE );
	//spi_fifo_reception_threshold_16bit( SPI2_BASE );
	//SPI_I2SCFGR( SPI2_BASE ) &= ~SPI_I2SCFGR_I2SMOD;
	spi_enable( SPI2_BASE );
	*/
	spi_init_master( SPI2_BASE,
					 SPI_CR1_BAUDRATE_FPCLK_DIV_64,
					 SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
					 SPI_CR1_CPHA_CLK_TRANSITION_1,
					 SPI_CR1_CRCL_8BIT,
					 SPI_CR1_MSBFIRST );
	spi_disable_crc( SPI2_BASE );
	spi_set_full_duplex_mode( SPI2_BASE );
	spi_set_unidirectional_mode( SPI2_BASE );
	spi_set_data_size( SPI2_BASE, SPI_CR2_DS_8BIT );
	spi_fifo_reception_threshold_8bit( SPI2_BASE );
	spi_enable_software_slave_management( SPI2_BASE );
	spi_set_nss_high( SPI2_BASE );
	spi_enable( SPI2_BASE );
}

uint16_t spi_rw( uint8_t dataHi, uint8_t dataLo )
{
	uint16_t readData = 0;
	spi_send8( SPI2_BASE, dataHi );
	readData |= spi_read8( SPI2_BASE ) << 8;
	spi_send8( SPI2_BASE, dataLo );
	readData |= spi_read8( SPI2_BASE );
	
//	readData |= spi_xfer( SPI2_BASE, dataHi ) << 8;
//	readData |= spi_xfer( SPI2_BASE, dataLo );
	return readData;
}
