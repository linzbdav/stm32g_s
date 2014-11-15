/*
 * cbuff.h -- Microcontroller circular buffer
 *
 */

#ifndef CBUFF_H_
#define CBUFF_H_

typedef struct
{
   // Buffer space that this circular buffer manages
   // Best performance if this is first since then &cbuff_t == buff
   unsigned char *buff;

   // Start and end indices of valid data in the buffer
   // Read from start; Write to end
   int start;
   int end;

   // Number of bytes in the buffer
   int cnt;

   // Number of bytes remaining in the buffer
   int remain;

   // Fix size of the buffer
   int size;
} cbuff_t;

// Initialize a circular buffer to use the designated static buffer that is len bytes big
cbuff_t *cbuff_init(cbuff_t *buff, unsigned char *staticbuff, int len);

/*
 * cbuff_reset -- Reset the buffer to an empty buffer starting at the first byte.
 * 
 * This is essentially the same as cbuff_init() but without needing to
 * pass the other parameters.
 *
 * Returns the number of bytes discard (i.e., the bytes in the buffer).
 */
int cbuff_reset(cbuff_t *buff);

// True if the buffer is full
static inline int cbuff_isfull(cbuff_t *buff)
{
   return buff->remain == 0;
}

// True if the buffer is empty
static inline int cbuff_isempty(cbuff_t *buff)
{
   return buff->cnt == 0;
}

// True if the buffer is not empty (could be full)
static inline int cbuff_isnonempty(cbuff_t *buff)
{
   return buff->cnt > 0;
}

// True if the buffer has room for size bytes (or less)
static inline int cbuff_hasspace(cbuff_t *buff)
{
   return buff->remain >= buff->size;
}

int cbuff_enqueue(cbuff_t *buff, unsigned char *dat, int len);
int cbuff_enqueue1_from_register(cbuff_t *buff, unsigned char *reg);
int cbuff_dequeue1(cbuff_t *buff);
int cbuff_dequeue1_to_register(cbuff_t *buff, unsigned char *reg);
int cbuff_dequeue(cbuff_t *buff, unsigned char *dest, int len);

#endif
