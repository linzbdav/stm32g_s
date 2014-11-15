//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Pin definitionen des Schrittmotor treibers
// Schaltung    :
//---------------------------------------------------------------------------
// Hardware     : STM32F051
// Takt         : 48MHz
// Sprache      : ARM C
// Datum        : 14.11.2014
// Version      : 1
// Autor        : David Linzberger
//---------------------------------------------------------------------------
#include "main.h"
#include "pins.h"

void pin_set( pin_def_t *p )
{
	gpio_set( p->port, p->pin );
}

void pin_reset( pin_def_t *p )
{
   gpio_clear( p->port, p->pin );
}

void pin_toggle( pin_def_t *p )
{
  gpio_toggle(p->port, p->pin);
}

uint8_t pin_getState( pin_def_t *p )
{
  return gpio_get( p->port, p->pin );
}

uint8_t pin_readInput( pin_def_t *p )
{
	return gpio_get( p->port, p->pin );
}
