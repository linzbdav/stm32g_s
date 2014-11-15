#include "main.h"
#include "usart.h"

uint8_t rbuf[RBUFSIZE];
uint8_t tbuf[TBUFSIZE];
cbuff_t tran_buf;
cbuff_t recv_buf;

/******************************************
 * Function Name	: RS485_init
 * Description		: Init usart1 using PB6, PB7 pins
 *                    115200, 8, 1, none flow control
 *                    DE/nRE using PA12
 * Input            : None
 * Ouput			: None
 * Return			: None
*******************************************/
void usart_init()
{
	rcc_periph_clock_enable( RCC_USART1);
	
	/* Enable the USARTx Interrupt */
	nvic_enable_irq( NVIC_USART1_IRQ );
	
	usart_set_baudrate( USART1, 115200 );
	usart_set_databits( USART1, 8 );
	usart_set_stopbits( USART1, USART_CR2_STOP_1_0BIT );
	usart_set_parity( USART1, USART_PARITY_NONE );
	usart_set_flow_control( USART1, USART_FLOWCONTROL_NONE );
	usart_set_mode( USART1, USART_MODE_TX_RX );
	/* Enable the USART1 */
	usart_enable( USART1 );
	
	usart_enable_rx_interrupt( USART1 );
	
	cbuff_init( &tran_buf, &tbuf[0], TBUFSIZE );
	cbuff_init( &recv_buf, &rbuf[0], RBUFSIZE );
}

void serial_send(uint8_t *buf, uint32_t len)
{
	cbuff_enqueue( &tran_buf, buf, len );
	usart_enable_tx_interrupt( USART1 );
}

uint8_t serial_read( uint8_t *buf )
{
	if( cbuff_isempty( &recv_buf ) )
	{
		return 0;
	}

	*buf = cbuff_dequeue1( &recv_buf );
	return 1;
}

void usart_queue_flush( void )
{
	usart_disable_tx_interrupt( USART1 );
	cbuff_reset( &recv_buf );
	cbuff_reset( &tran_buf );
}

void usart1_isr(void)
{
	uint8_t ch;
	if( usart_get_interrupt_source( USART1, USART_ISR_RXNE ) )
	{
		ch = usart_recv( USART1 );
		cbuff_enqueue( &recv_buf, &ch, 1);
	}
	
	if( usart_get_interrupt_source( USART1, USART_ISR_TXE ) )
	{
		ch = cbuff_dequeue1( &tran_buf );
		usart_send( USART1, ch );
		
		if( cbuff_isempty( &tran_buf ) )
		{
			usart_disable_tx_interrupt( USART1 );
		}
	}
}
