/*
 * file:    map_update_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for map update module.
 */

#include "platform_specific.h"

#include <cstring>

extern "C"
{
    #include "map/map.h"
    #include "wall_sensor/wall_sensor.h"
}

#include "mock_templates.hpp"
#include "map_update_mocks.hpp"

static MapUpdateMock *mapUpdateMock = nullptr;

struct coords * MapUpdateMock::getArg1()
{
    return &arg1_;
}

struct coords * MapUpdateMock::getArg2()
{
    return &arg2_;
}

void MapUpdateMock::call(struct coords *sensor_pos, struct coords *wall_pos, map_wall_state_t wall_state)
{
    cnt_++;

    memmove(&arg1_, sensor_pos, sizeof(struct coords));
    memmove(&arg2_, wall_pos, sizeof(struct coords));
    arg3_ = wall_state;
}

void mapUpdateMockSet(MapUpdateMock *mock)
{
    mapUpdateMock = mock;
}

void map_update(struct coords *sensor_pos, struct coords *wall_pos, map_wall_state_t wall_state)
{
    if (nullptr != mapUpdateMock)
    {
        mapUpdateMock->call(sensor_pos, wall_pos, wall_state);
    }
}
