#include "stm32f0xx.h"
#include "cbbuf.h"


uint8_t cbIncr( cbbuf *cb, int p );

void cbInit( cbbuf *cb, uint16_t size, uint8_t *buf )
{
	cb->size = size;
	cb->start = 0;
	cb->end = 0;
	cb->buffer = buf;
}

void cbClear( cbbuf *cb )
{
	cb->start = 0;
	cb->end = 0;
}

uint8_t cbIsFull( cbbuf *cb )
{
	return cb->end == (cb->start ^ cb->size );
}

uint8_t cbIsEmpty( cbbuf *cb )
{
	return cb->end == cb->start;
}

uint8_t cbIncr( cbbuf *cb, int p )
{
	return (p+1) & (2*cb->size-1);
}

void cbWrite( cbbuf *cb, uint8_t elem )
{
	cb->buffer[cb->end & (cb->size-1)] = elem;
	if( cbIsFull(cb) )
	{
		cb->start = cbIncr(cb, cb->start);
	}
	cb->end = cbIncr(cb, cb->end);
}

uint8_t cbRead( cbbuf *cb )
{
	uint8_t rc;
	rc = cb->buffer[cb->start&(cb->size-1)];
	cb->start = cbIncr(cb, cb->start);
	return rc;
}