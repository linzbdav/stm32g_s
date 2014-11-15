
#include "main.h"
uint8_t prints_mem( void const *vp, uint8_t n, uint8_t *buf, uint8_t max_len )
{
    if( n > max_len )
        return 0;

    uint8_t i;
    uint8_t const *p = vp;

    for( i = 0; i < n; i++ )
    {
        *buf = p[i];
        buf++;
    }

    return i;
}
