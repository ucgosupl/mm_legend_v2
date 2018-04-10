#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
    #include "position/position.h"
    #include "wall_detection/wall_detection.h"
    #include "wall_sensor/wall_sensor.h"
    #include "wall_sensor/wall_sensor_offsets.h"
}

#include "mock_templates.hpp"
#include "mocks/map_update_mocks.hpp"
#include "mocks/position_mocks.hpp"
#include "mocks/wall_sensor_mocks.hpp"

extern "C" void update_wall_with_sensor(struct coords *robot_pos, int32_t sensor_id, int32_t sensor_data);

TEST_GROUP(wall_detection_fun)
{
    void setup()
    {
    }

    void teardown()
    {
        posXMockSet(nullptr);
        posYMockSet(nullptr);
        posAlphaMockSet(nullptr);

        wallSensorGetMockSet(nullptr);

        mapUpdateMockSet(nullptr);
    }
};

TEST(wall_detection_fun, MapUpdateNotCalledWhenWallStateUnknown)
{
    struct coords robot_pos = {0};

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_FRONT_L, WALL_TOO_CLOSE);

    CHECK_EQUAL(0, mapUpdateMock.getCount());
}

TEST(wall_detection_fun, RobotPosAndSensorDataInfluenceMapUpdate)
{
    struct coords *sensor_pos;

    PositionGetMock posXMock(100.0f);
    PositionGetMock posYMock(50.0f);
    PositionGetMock posAlphaMock(30.0f);

    WallSensorGetMock wallSensorGetMock(WALL_NOT_FOUND);

    MapUpdateMock mapUpdateMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    posAlphaMockSet(&posAlphaMock);

    wallSensorGetMockSet(&wallSensorGetMock);

    mapUpdateMockSet(&mapUpdateMock);

    wall_detection();

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(100.0f + WALL_SENSOR_DIAG_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(50.0f + WALL_SENSOR_DIAG_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(30.0f + WALL_SENSOR_DIAG_OFFSET_A, sensor_pos->alpha);
}
