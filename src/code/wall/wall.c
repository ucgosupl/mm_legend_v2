/*
 * file:	wall.c
 * author:	GAndaLF
 * brief:   Wall detection task.
 */

#include "platform_specific.h"

#include "led/led.h"
#include "photo/photo.h"

#include "wall.h"

static void wall_task(void *params);

void wall_init(void)
{

}

int32_t wall_side_l_dist_mm_get(void)
{
    return 0;
}

int32_t wall_side_r_dist_mm_get(void)
{
    return 0;
}

int32_t wall_diag_l_dist_mm_get(void)
{
    return 0;
}

int32_t wall_diag_r_dist_mm_get(void)
{
    return 0;
}

int32_t wall_front_l_dist_mm_get(void)
{
    return 0;
}

int32_t wall_front_r_dist_mm_get(void)
{
    return 0;
}

static void wall_task(void *params)
{
    //todo: control IR LEDs, read voltage from phototransistors, convert to mm.
}
