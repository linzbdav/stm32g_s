#ifndef __ENCODER_H_
#define __ENCODER_H_


#define ENCODER_STEP_ROUNDING 0

#define SET_ENCODER_STEP_SIGN(m,s)	en.en[m].step_sign = s;
#define INCREMENT_ENCODER(m)		en.en[m].steps_run += en.en[m].step_sign;
#define ACCUMULATE_ENCODER(m)		en.en[m].encoder_steps += en.en[m].steps_run; en.en[m].steps_run = 0;

typedef struct enEncoder
{
	int8_t step_sign;
	int16_t steps_run;
	int32_t encoder_steps;
} enEncoder_t;

typedef struct enEncoders
{
	enEncoder_t en[3];
} enEncoders_t;

extern enEncoders_t en;

void encoder_init(void);

void en_reset_encoders(void);
int32_t en_read_encoder( uint8_t m );

#endif // __ENCODER_H_
