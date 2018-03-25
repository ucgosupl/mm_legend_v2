#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
}

#include "mocks/map_mocks.hpp"

#define WALL_PRESENT_THRESHOLD          20.0f
#define CORNER_PRESENT_THRESHOLD        30.0f
#define DELTA                           0.01f

TEST_GROUP(map_update_present)
{
    void setup()
    {
    }

    void teardown()
    {
        mapAddLeftWallMockSet(nullptr);
        mapAddRightWallMockSet(nullptr);
        mapAddTopWallMockSet(nullptr);
        mapAddBottomWallMockSet(nullptr);
    }
};

TEST(map_update_present, LeftWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
    CHECK_EQUAL(17, mapAddLeftWallMock.getArg1());
}

TEST(map_update_present, LeftWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
    CHECK_EQUAL(18, mapAddLeftWallMock.getArg1());
}

TEST(map_update_present, LeftWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, LeftWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMinimalTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMinimalTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, LeftWallDetectedMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
}

TEST(map_update_present, BottomWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
    CHECK_EQUAL(17, mapAddBottomWallMock.getArg1());
}

TEST(map_update_present, BottomWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
    CHECK_EQUAL(18, mapAddBottomWallMock.getArg1());
}

TEST(map_update_present, BottomWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, BottomWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMinimalTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMinimalTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, BottomWallDetectedMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
}

TEST(map_update_present, RightWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
    CHECK_EQUAL(17, mapAddRightWallMock.getArg1());
}

TEST(map_update_present, RightWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 3 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
    CHECK_EQUAL(18, mapAddRightWallMock.getArg1());
}

TEST(map_update_present, RightWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());
}

TEST(map_update_present, RightWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
}

TEST(map_update_present, RightWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());
}

TEST(map_update_present, RightWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
}

TEST(map_update_present, RightWallDetectedMinimalTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());
}

TEST(map_update_present, RightWallDetectedMaximumNotTooCloseToBottomCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
}

TEST(map_update_present, RightWallDetectedMinimalTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());
}

TEST(map_update_present, RightWallDetectedMaximumNotTooCloseToTopCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM;
    wall_pos.y = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
}

TEST(map_update_present, TopWallDetected1)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
    CHECK_EQUAL(17, mapAddTopWallMock.getArg1());
}

TEST(map_update_present, TopWallDetected2)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
    CHECK_EQUAL(18, mapAddTopWallMock.getArg1());
}

TEST(map_update_present, TopWallDetectedTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}

TEST(map_update_present, TopWallDetectedMinimalNotTooClose)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM - (WALL_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
}

TEST(map_update_present, TopWallDetectedTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD + DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}

TEST(map_update_present, TopWallDetectedMaximalNotTooFar)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM + (WALL_PRESENT_THRESHOLD - DELTA);

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
}

TEST(map_update_present, TopWallDetectedMinimalTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}

TEST(map_update_present, TopWallDetectedMaximumNotTooCloseToLeftCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
}

TEST(map_update_present, TopWallDetectedMinimalTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = 2 * MAP_CELL_WIDTH_MM - (CORNER_PRESENT_THRESHOLD - DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}

TEST(map_update_present, TopWallDetectedMaximumNotTooCloseToRightCorner)
{
    struct coords sensor_pos;
    struct coords wall_pos;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    sensor_pos.x = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;
    sensor_pos.y = MAP_CELL_WIDTH_MM + MAP_CELL_WIDTH_MM / 2.0f;

    wall_pos.x = MAP_CELL_WIDTH_MM + (CORNER_PRESENT_THRESHOLD + DELTA);
    wall_pos.y = 2 * MAP_CELL_WIDTH_MM;

    map_update(&sensor_pos, &wall_pos, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
}
