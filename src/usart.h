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
#ifndef _USART_H
#define _USART_H
/* Includes */
/* Private typedef */
/* Private define */
#define RBUFSIZE	256
#define TBUFSIZE	256
#define ADRESSE		0xAA
/* Private macro */
/* Private variables */
/* Private function prototypes */
void usart_init();
void serial_send(uint8_t *buf, uint32_t len);
uint8_t serial_read( uint8_t *buf );
void usart_queue_flush( void );
/* Private functions */
#endif // _USART_H
