#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
    #include "map/map_internal.h"
}

#include "mocks/map_mocks.hpp"

#define REGULAR_CELL    (2 * MAP_WIDTH + 3)

TEST_GROUP(map_validate_common)
{
    void setup()
    {
        map_validate_init();
    }

    void teardown()
    {
        mapAddLeftWallMockSet(nullptr);
        mapAddRightWallMockSet(nullptr);
        mapAddTopWallMockSet(nullptr);
        mapAddBottomWallMockSet(nullptr);

        mapAddLeftNoWallMockSet(nullptr);
        mapAddRightNoWallMockSet(nullptr);
        mapAddTopNoWallMockSet(nullptr);
        mapAddBottomNoWallMockSet(nullptr);

        mapWallLeftGetMockSet(nullptr);
        mapWallRightGetMockSet(nullptr);
        mapWallTopGetMockSet(nullptr);
        mapWallBottomGetMockSet(nullptr);
    }
};

TEST(map_validate_common, LeftIfPresentAfterAbsentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
}

TEST(map_validate_common, LeftIfAbsentAfterPresentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
}

TEST(map_validate_common, RightIfPresentAfterAbsentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
}

TEST(map_validate_common, RightIfAbsentAfterPresentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
}

TEST(map_validate_common, TopIfPresentAfterAbsentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
}

TEST(map_validate_common, TopIfAbsentAfterPresentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
}

TEST(map_validate_common, BottomIfPresentAfterAbsentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_common, BottomIfAbsentAfterPresentResetBothCounters)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
}


//mocki przeniesc do common_mocks
