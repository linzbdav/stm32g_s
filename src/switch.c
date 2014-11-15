//---------------------------------------------------------------------------
// Titel        : Stepper Driver STM32F0
//---------------------------------------------------------------------------
// Funktion     : Endschalter Funktionen
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
#include "switch.h"
#include "hardware.h"
#include "pins.h"

switches_t sw;

static void _trigger_feedhold(switch_t *s);
static void _trigger_cycle_start(switch_t *s);
static void _no_action(switch_t *s) { return; }

void switch_init(void)
{
	sw.type = SW_TYPE_NORMALLY_OPEN;
	switch_reset();
}

void switch_reset(void)
{
	uint8_t i, axis, position;
	switch_t *s;
	
	for( axis = 0; axis<SW_PAIRS; axis++ )
	{
		for( position = 0; position<SW_POSITIONS; position++)
		{
			s = &sw.s[axis][position];
			
			s->type = sw.type;
			s->mode = SW_MODE_DISABLED;
			s->state = false;
			s->debounce_ticks = SW_LOCKOUT_TICKS;
			s->debounce_timeout = 0;
			
			// functions bound to each switch
			s->when_open = _no_action;
			s->when_closed = _no_action;
			s->on_leading = _trigger_feedhold;
			s->on_trailing = _trigger_cycle_start;
		}
	}
}

/*
 * poll_switches() - run a polling cycle on all switches
 */
stat_t poll_switches()
{
	poll_switch( &sw.s[AXIS_X][SW_MIN], (bool)pin_readInput( &hw.sw[SW_MIN_X].sw ) );
	poll_switch( &sw.s[AXIS_X][SW_MAX], (bool)pin_readInput( &hw.sw[SW_MAX_X].sw ) );
	poll_switch( &sw.s[AXIS_Y][SW_MIN], (bool)pin_readInput( &hw.sw[SW_MIN_Y].sw ) );
	poll_switch( &sw.s[AXIS_Y][SW_MAX], (bool)pin_readInput( &hw.sw[SW_MAX_Y].sw ) );
	poll_switch( &sw.s[AXIS_Z][SW_MIN], (bool)pin_readInput( &hw.sw[SW_MIN_Z].sw ) );
	poll_switch( &sw.s[AXIS_Z][SW_MAX], (bool)pin_readInput( &hw.sw[SW_MAX_Z].sw ) );
	
	return ( STAT_OK );
}

/*
 * poll_switch() - read switch with NO/NC, debouncing and edge detection
 * 
 * 		Returns true if switch state changed - e.g. leading or falling edge detected
 * 		Assumes pin_value **input** = 1 means open, 0 is closed.
 * 		Pin sense is adjusted to mean:
 * 			0 = open for both NO and NC switches
 * 			1 = closed for both NO and NC switches
 * 			-1= switch disabled
 * 
 * 		Also sets disabled switches to switch state -1
 */
int8_t poll_switch( switch_t *s, uint8_t pin_value )
{
	// instant return conditions: switch disabled or in a lockout period
	if( s->mode == SW_MODE_DISABLED )
	{
		s->state = SW_DISABLED;
		return false;
	}
	if( s->debounce_timeout > SysTickTimer_getValue() )
	{
		return false;
	}
	
	// return if no change in state
	uint8_t pin_sense_corrected = (pin_value ^ (s->type ^ 1 ));
	if( s->state == pin_sense_corrected )
	{
		s->edge = SW_NO_EDGE;
		if( s->state == SW_OPEN )
		{
			s->when_open(s);
		}
		else
		{
			s->when_closed(s);
		}
		return false;
	}
	
	// the switch legitimately changed state - process edges
	if( ( s->state = pin_sense_corrected ) == SW_OPEN )
	{
		s->edge = SW_TRAILING;
		s->on_trailing(s);
	}
	else
	{
		s->edge = SW_LEADING;
		s->on_leading(s);
	}
	s->debounce_timeout = (SysTickTimer_getValue() + s->debounce_ticks);
	return true;
}

static void _trigger_feedhold( switch_t *s )
{
	
}

static void _trigger_cycle_start( switch_t *s )
{
	
}

uint8_t get_switch_mode( uint8_t axis, uint8_t position )
{
	return sw.s[axis][position].mode;
}

uint8_t get_switch_type( uint8_t axis, uint8_t position )
{
	return sw.s[axis][position].type;
}

int8_t read_switch( uint8_t axis, uint8_t position )
{
	return sw.s[axis][position].state;
}

