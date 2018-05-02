#include "platform_specific.h"

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

extern "C" void update_wall_with_sensor(struct coords *robot_pos, int32_t sensor_id, int32_t sensor_data);

TEST_GROUP(calculate_sensor_fun)
{
    void setup()
    {
    }

    void teardown()
    {
        mapUpdateMockSet(nullptr);
    }
};

TEST(calculate_sensor_fun, FrontLeftSensorOffset1)
{
    struct coords robot_pos = {0};
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_FRONT_L, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(WALL_SENSOR_FRONT_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(WALL_SENSOR_FRONT_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(WALL_SENSOR_FRONT_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, FrontLeftSensorOffset2)
{
    struct coords robot_pos;
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    robot_pos.x = 100.0f;
    robot_pos.y = 100.0f;
    robot_pos.alpha = 100.0f;

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_FRONT_L, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(100.0f + WALL_SENSOR_FRONT_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(100.0f + WALL_SENSOR_FRONT_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(100.0f + WALL_SENSOR_FRONT_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, FrontRighttSensorOffset1)
{
    struct coords robot_pos = {0};
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_FRONT_R, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(WALL_SENSOR_FRONT_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(-WALL_SENSOR_FRONT_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(WALL_SENSOR_FRONT_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, FrontRightSensorOffset2)
{
    struct coords robot_pos;
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    robot_pos.x = 100.0f;
    robot_pos.y = 100.0f;
    robot_pos.alpha = 100.0f;

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_FRONT_R, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(100.0f + WALL_SENSOR_FRONT_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(100.0f - WALL_SENSOR_FRONT_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(100.0f + WALL_SENSOR_FRONT_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, DiagLeftSensorOffset1)
{
    struct coords robot_pos = {0};
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_DIAG_L, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(WALL_SENSOR_DIAG_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(WALL_SENSOR_DIAG_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(WALL_SENSOR_DIAG_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, DiagLeftSensorOffset2)
{
    struct coords robot_pos;
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    robot_pos.x = 100.0f;
    robot_pos.y = 100.0f;
    robot_pos.alpha = 100.0f;

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_DIAG_L, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(100.0f + WALL_SENSOR_DIAG_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(100.0f + WALL_SENSOR_DIAG_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(100.0f + WALL_SENSOR_DIAG_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, DiagRighttSensorOffset1)
{
    struct coords robot_pos = {0};
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_DIAG_R, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(WALL_SENSOR_DIAG_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(-WALL_SENSOR_DIAG_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(-WALL_SENSOR_DIAG_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, DiagRightSensorOffset2)
{
    struct coords robot_pos;
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    robot_pos.x = 100.0f;
    robot_pos.y = 100.0f;
    robot_pos.alpha = 100.0f;

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_DIAG_R, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(100.0f + WALL_SENSOR_DIAG_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(100.0f - WALL_SENSOR_DIAG_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(100.0f - WALL_SENSOR_DIAG_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, SideLeftSensorOffset1)
{
    struct coords robot_pos = {0};
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_SIDE_L, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(WALL_SENSOR_SIDE_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(WALL_SENSOR_SIDE_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(WALL_SENSOR_SIDE_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, SideLeftSensorOffset2)
{
    struct coords robot_pos;
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    robot_pos.x = 100.0f;
    robot_pos.y = 100.0f;
    robot_pos.alpha = 100.0f;

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_SIDE_L, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(100.0f + WALL_SENSOR_SIDE_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(100.0f + WALL_SENSOR_SIDE_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(100.0f + WALL_SENSOR_SIDE_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, SideRighttSensorOffset1)
{
    struct coords robot_pos = {0};
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_SIDE_R, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(WALL_SENSOR_SIDE_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(-WALL_SENSOR_SIDE_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(-WALL_SENSOR_SIDE_OFFSET_A, sensor_pos->alpha);
}

TEST(calculate_sensor_fun, SideRightSensorOffset2)
{
    struct coords robot_pos;
    struct coords *sensor_pos;

    MapUpdateMock mapUpdateMock;

    mapUpdateMockSet(&mapUpdateMock);

    robot_pos.x = 100.0f;
    robot_pos.y = 100.0f;
    robot_pos.alpha = 100.0f;

    update_wall_with_sensor(&robot_pos, WALL_SENSOR_SIDE_R, WALL_NOT_FOUND);

    sensor_pos = mapUpdateMock.getArg1();

    CHECK_EQUAL(100.0f + WALL_SENSOR_SIDE_OFFSET_X, sensor_pos->x);
    CHECK_EQUAL(100.0f - WALL_SENSOR_SIDE_OFFSET_Y, sensor_pos->y);
    CHECK_EQUAL(100.0f - WALL_SENSOR_SIDE_OFFSET_A, sensor_pos->alpha);
}
