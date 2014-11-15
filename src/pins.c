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
