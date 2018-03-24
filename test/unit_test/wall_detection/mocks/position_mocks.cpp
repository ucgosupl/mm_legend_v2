/*
 * file:    position_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for position module.
 */

#include "platform_specific.h"

extern "C"
{
    #include "position/position.h"
}

#include "position_mocks.hpp"

float position_x_get(void)
{
    return 0;
}

float position_y_get(void)
{
    return 0;
}
