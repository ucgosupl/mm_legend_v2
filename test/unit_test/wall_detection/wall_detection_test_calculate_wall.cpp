#include "platform_specific.h"
#include <cmath>

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
    #include "wall_detection/wall_detection.h"
    #include "wall_sensor/wall_sensor.h"
    #include "wall_sensor/wall_sensor_offsets.h"
}

#include "mock_templates.hpp"
#include "mocks/map_update_mocks.hpp"

extern "C"  map_wall_state_t calculate_wall_pos(struct coords *sensor_pos, int32_t sensor_data, struct coords *wall_pos);

TEST_GROUP(calculate_wall_fun)
{
    void setup()
    {
    }

    void teardown()
    {
        mapUpdateMockSet(nullptr);
    }
};

TEST(calculate_wall_fun, WallTooClose)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    int32_t sensor_data = WALL_TOO_CLOSE;

    map_wall_state_t ret_val;

    ret_val = calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, ret_val);
}

TEST(calculate_wall_fun, SensorAboveThresholdRetVal)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    int32_t sensor_data = 130 + 1;

    map_wall_state_t ret_val;

    ret_val = calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    CHECK_EQUAL(MAP_WALL_ABSENT, ret_val);
}

TEST(calculate_wall_fun, SensorAboveThresholdWallPosCalculated1)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    int32_t sensor_data = 130 + 1;

    calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    DOUBLES_EQUAL(130.0f, wall_pos.x, 0.001f);
    DOUBLES_EQUAL(0.0f, wall_pos.y, 0.001f);
}


TEST(calculate_wall_fun, SensorAboveThresholdWallPosCalculated2)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    int32_t sensor_data = 130 + 1;
    sensor_pos.alpha = 90.0f / 180.0f * M_PI;

    calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    DOUBLES_EQUAL(0.0f, wall_pos.x, 0.001f);
    DOUBLES_EQUAL(130.0f, wall_pos.y, 0.001f);
}

TEST(calculate_wall_fun, SensorBelowThreshold)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    int32_t sensor_data = 130;

    map_wall_state_t ret_val;

    ret_val = calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    CHECK_EQUAL(MAP_WALL_PRESENT, ret_val);
}

TEST(calculate_wall_fun, SensorBelowThresholdWallPosCalculated1)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    int32_t sensor_data = 80;

    calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    DOUBLES_EQUAL(80.0f, wall_pos.x, 0.001f);
    DOUBLES_EQUAL(0.0f, wall_pos.y, 0.001f);
}


TEST(calculate_wall_fun, SensorBelowThresholdWallPosCalculated2)
{
    struct coords sensor_pos = {0};
    struct coords wall_pos = {0};

    int32_t sensor_data = 80;
    sensor_pos.alpha = 90.0f / 180.0f * M_PI;

    calculate_wall_pos(&sensor_pos, sensor_data, &wall_pos);

    DOUBLES_EQUAL(0.0f, wall_pos.x, 0.001f);
    DOUBLES_EQUAL(80.0f, wall_pos.y, 0.001f);
}
