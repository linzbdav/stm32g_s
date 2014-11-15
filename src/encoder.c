#include "main.h"
#include "encoder.h"

enEncoders_t en;

void encoder_init()
{

}

void en_reset_encoders(void)
{
}

int32_t en_read_encoder( uint8_t m )
{
	return (en.en[m].encoder_steps + ENCODER_STEP_ROUNDING );
}

