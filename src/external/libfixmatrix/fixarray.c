#include "fixarray.h"
#include <string.h> /* For memcpy() */

fix16_t fa16_dot(const fix16_t *a, uint_fast8_t a_stride,
                 const fix16_t *b, uint_fast8_t b_stride,
                 uint_fast8_t n)
{
    fix16_t sum = 0;
    
    while (n--)
    {
        if (*a != 0 && *b != 0)
        {
            sum += (*a) * (*b);
        }
        
        // Go to next item
        a += a_stride;
        b += b_stride;
    }
    
    return sum;
}

// Calculates the norm of a vector
fix16_t fa16_norm(const fix16_t *a, uint_fast8_t a_stride, uint_fast8_t n)
{
    fix16_t sum = 0;
    
    while (n--)
    {
        if (*a != 0)
        {
            sum += (*a) * (*a);
        }
        
        a += a_stride;
    }
    
    return fix16_sqrt(sum);
}

void fa16_unalias(void *dest, void **a, void **b, void *tmp, unsigned size)
{
    if (dest == *a)
    {
        memcpy(tmp, *a, size);
        *a = tmp;
        
        if (dest == *b)
            *b = tmp;
    }
    else if (dest == *b)
    {
        memcpy(tmp, *b, size);
        *b = tmp;
    }
}
