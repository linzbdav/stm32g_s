#ifndef __PINS_H_
#define __PINS_H_

#define GPIO_TypeDef uint32_t

typedef struct pin_def_struct pin_def_t;
struct pin_def_struct {
	GPIO_TypeDef port;
	uint16_t pin;
};

void pin_set( pin_def_t *p );
void pin_reset( pin_def_t *p );
void pin_toggle( pin_def_t *p );
uint8_t pin_getState( pin_def_t *p );
uint8_t pin_readInput( pin_def_t *p );

#endif // __PINS_H_
