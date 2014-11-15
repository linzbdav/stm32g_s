
#ifndef _CIRCULAR_BUFFER_H
#define _CIRCULAR_BUFFER_H

typedef struct {
	uint16_t size;
	uint16_t start;
	uint16_t end;
	uint8_t *buffer;
} cbbuf;

void cbInit( cbbuf *cb, uint16_t size, uint8_t *buf );
void cbClear( cbbuf *cb );
uint8_t cbIsFull( cbbuf *cb );
uint8_t cbIsEmpty( cbbuf *cb );
void cbWrite( cbbuf *cb, uint8_t elem );
uint8_t cbRead( cbbuf *cb );

#endif // _CIRCULAR_BUFFER_H