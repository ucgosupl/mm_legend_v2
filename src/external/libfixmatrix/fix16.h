/*
 * file:	fix16.h
 * author:	GAndaLF
 * brief:	Short file description.
 */

#ifndef _FIX16_H_
#define _FIX16_H_

#include <stdint.h>
#include <math.h>

#define fix16_one   1

#define fix16_add(a, b) ((a) + (b))
#define fix16_sub(a, b) ((a) - (b))
#define fix16_mul(a, b) ((a) * (b))
#define fix16_div(a, b) ((a) / (b))

#define fix16_sqrt(a)   sqrtf(a)
#define fix16_sin(a)    sinf(a)
#define fix16_cos(a)    cosf(a)

typedef float fix16_t;

#endif /* _FIX16_H_ */
