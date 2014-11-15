#ifndef SWITCH_H_ONCE
#define SWITCH_H_ONCE

#define SW_PAIRS				3
#define SW_POSITIONS			2

// switch modes
#define SW_HOMING_BIT			0x01
#define SW_LIMIT_BIT			0x02

#define SW_MODE_DISABLED		0
#define SW_MODE_HOMING			SW_HOMING_BIT
#define SW_MODE_LIMIT			SW_LIMIT_BIT
#define SW_MODE_HOMING_LIMIT	(SW_HOMING_BIT | SW_LIMIT_BIT )
#define SW_MODE_MAX_VALUE		SW_MODE_HOMING_LIMIT;

enum swType {
	SW_TYPE_NORMALLY_OPEN = 0,
	SW_TYPE_NORMALLY_CLOSED
};

enum swState {
	SW_DISABLED = 1,
	SW_OPEN = 0,
	SW_CLOSED = 2
};

enum swPosition {
	SW_MIN = 0,
	SW_MAX
};

enum swEdge {
	SW_NO_EDGE = 0,
	SW_LEADING,
	SW_TRAILING
};

/*
 * Defines for old switch handling code
 */
// timer for debouncing switches
#define SW_LOCKOUT_TICKS		25	// 25=250ms 
#define SW_DEGLITCH_TICKS		3	// 3 = 30ms

enum swDebounce {
	SW_IDLE = 0,
	SW_DEGLITCHING,
	SW_LOCKOUT
};

enum swNums {
	SW_MIN_X = 0,
	SW_MAX_X,
	SW_MIN_Y,
	SW_MAX_Y,
	SW_MIN_Z,
	SW_MAX_Z,
	NUM_SWITCHES
};

#define SW_OFFSET			SW_MAX_X
#define NUM_SWITCH_PAIRS	( NUM_SWITCHES / 2 )

#define MIN_SWITCH(axis) 	( axis * 2 )
#define MAX_SWITCH(axis) 	( axis * 2 + 1 )

// Structures from new-style switch code
typedef struct swSwitch
{
	// public
	uint8_t type;
	uint8_t mode;
	int8_t state;
	
	// private
	uint8_t edge;
	uint16_t debounce_ticks;
	uint32_t debounce_timeout;
	void(*when_open)(struct swSwitch *s);
	void(*when_closed)(struct swSwitch *s);
	void(*on_leading)(struct swSwitch *s);
	void(*on_trailing)(struct swSwitch *s);
} switch_t;
typedef void (*sw_callback)(switch_t *s);

typedef struct swSwitchArray
{
	uint8_t type;
	switch_t s[SW_PAIRS][SW_POSITIONS];
} switches_t;

extern switches_t sw;

/*
 * Function prototypes
 */
void switch_init();
void switch_reset();
stat_t poll_switches();


void reset_switches(void);

int8_t poll_switch(switch_t *s, uint8_t pin_value );
uint8_t get_switch_mode(uint8_t axis, uint8_t position );
uint8_t get_switch_type(uint8_t axis, uint8_t position );
int8_t read_switch(uint8_t axis, uint8_t position );




#endif
