/*
 * file:	dummies.c
 * author:	GAndaLF
 * brief:	Unused functions needed only for compilation.
 */

#include "platform_specific.h"

#include "hbridge/hbridge.h"

void motor_all_off(void)
{
    /* Actual motor off implementation as this hw test uses motors. */
    hbridge_left_speed_set(0);
    hbridge_right_speed_set(0);
}
