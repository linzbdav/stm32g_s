#ifndef __SEGMENT_H_
#define __SEGMENT_H_

enum MOVE_TYPE
{
	MOVE_TYPE_NULL,
	MOVE_TYPE_ALINE,
	MOVE_TYPE_DWELL
};

enum seBufferState
{
	SE_BUFFER_EMPTY = 0,
	SE_BUFFER_LOADING,
	SE_BUFFER_QUEUED,
	SE_BUFFER_PENDING,
	SE_BUFFER_RUNNING
};

enum moveState
{
	MOVE_OFF = 0,
	MOVE_NEW,
	MOVE_RUN,
	MOVE_SKIP
};

#define SEGMENT_BUFFER_POOL_SIZE 4

typedef struct segment_def_struct seg_def_t;
struct segment_def_struct {
	seg_def_t *nx;
	seg_def_t *pv;

	uint8_t buffer_state;
	uint8_t move_type;
	uint8_t move_code;
	uint8_t move_state;

	uint8_t direction[3];
	uint32_t position[3];
	uint32_t time;
};

typedef struct segment_pool_struct seg_pol_t;
struct segment_pool_struct
{
	uint8_t buffers_available;
	seg_def_t *w;
	seg_def_t *q;
	seg_def_t *r;
	seg_def_t bf[SEGMENT_BUFFER_POOL_SIZE];
};

extern seg_pol_t se;

void seg_init( void );

seg_def_t *se_get_run_buffer(void);
seg_def_t *se_get_write_buffer(void);
void se_queue_write_buffer( const uint8_t move_type );
void se_unget_write_buffer( void );
#define se_get_prev_buffer(b) ((seg_def_t *)(b->pv))
#define se_get_next_buffer(b) ((seg_def_t *)(b->nx))
#endif // __SEGMENT_H_
