#include "main.h"
#include "segment.h"

seg_pol_t se;

#define _bump(a) ((a<SEGMENT_BUFFER_POOL_SIZE-1)?(a+1):0)

static void _init_buffers(void);

void seg_init( void )
{
	_init_buffers();
}

static void _init_buffers(void)
{
	seg_def_t *pv;
	uint8_t i;

	se.w = &se.bf[0];
	se.q = &se.bf[0];
	se.r = &se.bf[0];
	pv = &se.bf[SEGMENT_BUFFER_POOL_SIZE - 1];
	for( i = 0; i < SEGMENT_BUFFER_POOL_SIZE; i++ )
	{
		se.bf[i].nx = &se.bf[_bump(i)];
		se.bf[i].pv = pv;
		pv = &se.bf[i];
	}
	se.buffers_available = SEGMENT_BUFFER_POOL_SIZE;
}

seg_def_t *se_get_write_buffer()
{
	if( se.w->buffer_state == SE_BUFFER_EMPTY )
	{
		seg_def_t *w = se.w;
		seg_def_t *nx = se.w->nx;
		seg_def_t *pv = se.w->pv;
		//memset( se.w, 0, sizeof( seg_buf_t ) );
		w->nx = nx;
		w->pv = pv;
		w->buffer_state = SE_BUFFER_LOADING;
		se.buffers_available--;
		se.w = w->nx;
		return w;
	}
	return NULL;
}

void se_unget_write_buffer( void )
{
	se.w = se.w->pv;
	se.w->buffer_state = SE_BUFFER_EMPTY;
	se.buffers_available++;
}

void se_queue_write_buffer( const uint8_t move_type )
{
	se.q->move_type = move_type;
	se.q->move_state = MOVE_NEW;
	se.q->buffer_state = SE_BUFFER_QUEUED;
	se.q = se.q->nx;
}

seg_def_t *se_get_run_buffer()
{
	if((se.r->buffer_state == SE_BUFFER_QUEUED) ||
	   (se.r->buffer_state == SE_BUFFER_PENDING))
	{
		se.r->buffer_state = SE_BUFFER_RUNNING;
	}
	if( se.r->buffer_state == SE_BUFFER_RUNNING )
	{
		return se.r;
	}
	return NULL;
}
