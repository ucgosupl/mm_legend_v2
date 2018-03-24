/*
 * file:    map_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for map module.
 */

#include "platform_specific.h"

extern "C"
{
    #include "map/map.h"
}

#include "map_mocks.hpp"

map_wall_state_t map_wall_left_get(int32_t cell_id)
{
    return MAP_WALL_UNKNOWN;
}
