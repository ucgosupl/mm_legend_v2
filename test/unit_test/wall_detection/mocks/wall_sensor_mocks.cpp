/*
 * file:    map_mocks.hpp
 * author:  GAndaLF
 * brief:   Mock functions for wall sensors.
 */

#include "platform_specific.h"

extern "C"
{
    #include "wall_sensor/wall_sensor.h"
}

#include "wall_sensor_mocks.hpp"

static WallSensorGetMock *wallSensorGetMock = nullptr;

WallSensorGetMock::WallSensorGetMock(int32_t retVal) : retVal_(retVal) {};

int32_t WallSensorGetMock::getCount()
{
    return cnt_;
}

int32_t WallSensorGetMock::getArg1()
{
    return arg1_;
}

int32_t WallSensorGetMock::call(int32_t cell_id)
{
    cnt_++;

    arg1_ = cell_id;

    return retVal_;
}

void wallSensorGetMockSet(WallSensorGetMock *mock)
{
    wallSensorGetMock = mock;
}

int32_t wall_sensor_dist_mm_get(int32_t sensor_id)
{
    if (nullptr != wallSensorGetMock)
    {
        return wallSensorGetMock->call(sensor_id);
    }

    return 0;
}
