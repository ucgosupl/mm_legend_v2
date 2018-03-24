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

static MapWallGetMock *mapWallLeftGetMock = nullptr;

MapWallGetMock::MapWallGetMock(map_wall_state_t retVal) : retVal_(retVal) {};

int32_t MapWallGetMock::getCount()
{
    return cnt_;
}

int32_t MapWallGetMock::getArg1()
{
    return arg1_;
}

map_wall_state_t MapWallGetMock::call(int32_t cell_id)
{
    cnt_++;

    arg1_ = cell_id;

    return retVal_;
}

void mapWallLeftGetMockSet(MapWallGetMock *mock)
{
    mapWallLeftGetMock = mock;
}

map_wall_state_t map_wall_left_get(int32_t cell_id)
{
    if (nullptr != mapWallLeftGetMock)
    {
        return mapWallLeftGetMock->call(cell_id);
    }

    return MAP_WALL_UNKNOWN;
}
