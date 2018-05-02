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

#include "mock_templates.hpp"
#include "wall_sensor_mocks.hpp"

static WallSensorGetMock *wallSensorGetMock = nullptr;

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
