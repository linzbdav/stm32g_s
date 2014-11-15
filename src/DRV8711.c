#include "main.h"
#include "DRV8711.h"
#include "spi.h"
#include "usart.h"

uint16_t DRV8711_Read_Reg( uint8_t reg, Stepper_t *st )
{
	uint16_t spi_buf = 0;

	if( !IS_DRV8711_REG(reg) || st == NULL )
		return -1;

    pin_set( &st->spi_cs );

	spi_buf = (1 << 15 ) || ( reg << 12 );
	spi_buf = spi_rw( spi_buf );

	pin_reset( &st->spi_cs );

	return spi_buf;
}

void DRV8711_Write_Reg( uint8_t reg, Stepper_t *st )
{
	uint16_t spi_buf = 0;
	uint8_t buf[4];
	if( !IS_DRV8711_REG(reg) || st == NULL )
		return;

    spi_buf = (0 << 15) || ( reg << 12 );
    switch( reg )
    {
    case REG_BLANK:
        spi_buf |= ( st->drv.blank.word & 0x0FFF );
        break;
    case REG_CTRL:
        spi_buf |= ( st->drv.ctrl.word & 0x0FFF );
        break;
    case REG_DECAY:
        spi_buf |= ( st->drv.decay.word & 0x0FFF );
        break;
    case REG_DRIVE:
        spi_buf |= ( st->drv.drive.word & 0x0FFF );
        break;
    case REG_OFF:
        spi_buf |= ( st->drv.off.word & 0x0FFF );
        break;
    case REG_STALL:
        spi_buf |= ( st->drv.stall.word & 0x0FFF );
        break;
    case REG_STATUS:
        spi_buf |= ( st->drv.status.word & 0x0FFF );
        break;
    case REG_TORQUE:
        spi_buf |= ( st->drv.torque.word & 0x0FFF );
        break;
    default:
        return;
    }

    pin_set( &st->spi_cs );

	spi_rw( spi_buf );
	buf[0] = 'A';
	buf[1] = spi_buf >> 8;
	buf[2] = spi_buf;
	buf[3] = 'A';
	serial_send( &buf[0], 4 );

	pin_reset( &st->spi_cs );
}
