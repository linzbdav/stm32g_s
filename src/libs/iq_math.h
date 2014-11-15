/* Fixed point aritmetics
 *
 */
#ifndef __IQ_MATH_H_
#define __IQ_MATH_H_

#ifndef INLINE
#define INLINE static inline
#endif

#define Q		14
#define K		(1 << ( ( Q ) - 1 ) )

#define IQ_ZERO	0
#define IQ_ONE	( 1 << Q )
#define IQ_TWO	( 1 << ( ( Q ) + 1 ) )

typedef int32_t frac;
typedef int64_t accum;

#define TODOBLE(d, q)	( (double)(d) / (double)(1<<(q)))
#define TOFP(d, q)		((frac)((d) * (double)(1<<(q))))

extern accum isqrt_rem;

INLINE frac iq_add( frac a, frac b)
{
	return a + b;
}

INLINE frac iq_sub( frac a, frac b )
{
	return a - b;
}

INLINE frac iq_mul( frac a, frac b )
{
	accum tmp = (accum)a * (accum)b;
	tmp += K;	// round midrange
	return tmp >> Q;
}

INLINE frac iq_div( frac a, frac b )
{
	accum tmp = (accum)a << Q;
	tmp += b/2;	// round midrange
	return (frac)tmp / b;
}

INLINE frac iq_addi( frac a, int16_t b )
{
	return a + ( b << Q );
}

INLINE frac iq_subi( frac a, int16_t b )
{
	return a - ( b << Q );
}

INLINE frac iq_muli( frac a, int16_t b )
{
	return a * b;
}

INLINE frac iq_divi( frac a, int16_t b )
{
	return a / b;
}

accum iq_sqrt( accum x );

#endif // __IQ_MATH_H_
