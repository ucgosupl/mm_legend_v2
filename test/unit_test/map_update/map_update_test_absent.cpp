#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
}

#include "mocks/map_mocks.hpp"

#define WALL_THRESHOLD          20.0f
#define CORNER_THRESHOLD        30.0f
#define DELTA                           0.01f

TEST_GROUP(map_update_absent)
{
    void setup()
    {
    }

    void teardown()
    {
        mapAddLeftNoWallMockSet(nullptr);
        mapAddRightNoWallMockSet(nullptr);
        mapAddTopNoWallMockSet(nullptr);
        mapAddBottomNoWallMockSet(nullptr);
    }
};

TEST(map_update_absent, LeftNoWallRangeAndSensorInBounds1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
    CHECK_EQUAL(17, mapAddLeftNoWallMock.getArg1());
}

TEST(map_update_absent, LeftNoWallRangeAndSensorInBounds2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
    CHECK_EQUAL(18, mapAddLeftNoWallMock.getArg1());
}

TEST(map_update_absent, LeftNoWallRangeTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallSensorTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallRangeMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallRangeMinimumTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallSensorMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallSensorMinimumTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallRangeMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallRangeMinimumTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallSensorMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, LeftNoWallSensorMinimumTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallRangeAndSensorInBounds1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
    CHECK_EQUAL(17, mapAddBottomNoWallMock.getArg1());
}

TEST(map_update_absent, BottomNoWallRangeAndSensorInBounds2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
    CHECK_EQUAL(18, mapAddBottomNoWallMock.getArg1());
}

TEST(map_update_absent, BottomNoWallRangeTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallSensorTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallRangeMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallRangeMinimumTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallSensorMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallSensorMinimumTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallRangeMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallRangeMinimumTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallSensorMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, BottomNoWallSensorMinimumTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallRangeAndSensorInBounds1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
    CHECK_EQUAL(17, mapAddRightNoWallMock.getArg1());
}

TEST(map_update_absent, RightNoWallRangeAndSensorInBounds2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 3 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
    CHECK_EQUAL(18, mapAddRightNoWallMock.getArg1());
}

TEST(map_update_absent, RightNoWallRangeTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallSensorTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallRangeMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallRangeMinimumTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallSensorMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallSensorMinimumTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallRangeMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallRangeMinimumTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallSensorMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
}

TEST(map_update_absent, RightNoWallSensorMinimumTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}


TEST(map_update_absent, TopNoWallRangeAndSensorInBounds1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
    CHECK_EQUAL(17, mapAddTopNoWallMock.getArg1());
}

TEST(map_update_absent, TopNoWallRangeAndSensorInBounds2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
    CHECK_EQUAL(18, mapAddTopNoWallMock.getArg1());
}

TEST(map_update_absent, TopNoWallRangeTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD + DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallSensorTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_THRESHOLD - DELTA);

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallRangeMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallRangeMinimumTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD - DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallSensorMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + (CORNER_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallSensorMinimumTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallRangeMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallRangeMinimumTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallSensorMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD + DELTA);
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
}

TEST(map_update_absent, TopNoWallSensorMinimumTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_THRESHOLD - DELTA);
    sensor_pos.y = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

//todo: add defines for easier coordinate calculation
