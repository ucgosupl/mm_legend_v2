/* Utilities for printing fix16_t datatypes. */

#ifndef _FIXSTRING_H_
#define _FIXSTRING_H_

#include <stdio.h>
#include <fix16.h>
#include "fixmatrix.h"

/* All print_*() functions have interface similar to fprintf().
 */
void print_mf16(const mf16 *matrix);

#endif
