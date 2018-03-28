#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
    #include "map/map_internal.h"
}

#include "mocks/map_mocks.hpp"

#define REGULAR_CELL    (2 * MAP_WIDTH + 3)

TEST_GROUP(map_validate_present)
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

        mapWallLeftGetMockSet(nullptr);
        mapWallRightGetMockSet(nullptr);
        mapWallTopGetMockSet(nullptr);
        mapWallBottomGetMockSet(nullptr);
    }
};

TEST(map_validate_present, LeftWallGetCalledCorrectly)
{
    MapWallGetMock mapWallLeftGetMock;

    mapWallLeftGetMockSet(&mapWallLeftGetMock);

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapWallLeftGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallLeftGetMock.getArg1());
}

TEST(map_validate_present, LeftNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());
}

TEST(map_validate_present, LeftNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());
}

TEST(map_validate_present, LeftPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddLeftWallMock.getArg1());
}

TEST(map_validate_present, LeftOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_left(REGULAR_CELL + 1, MAP_WALL_PRESENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddLeftWallMock.getCount());
}

TEST(map_validate_present, LeftPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;
    MapWallGetMock mapWallLeftGetMock(1);

    mapAddLeftWallMockSet(&mapAddLeftWallMock);
    mapWallLeftGetMockSet(&mapWallLeftGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());
}

TEST(map_validate_present, RightWallGetCalledCorrectly)
{
    MapWallGetMock mapWallRightGetMock;

    mapWallRightGetMockSet(&mapWallRightGetMock);

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapWallRightGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallRightGetMock.getArg1());
}

TEST(map_validate_present, RightNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());
}

TEST(map_validate_present, RightNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());
}

TEST(map_validate_present, RightPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddRightWallMock.getArg1());
}

TEST(map_validate_present, RightOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightWallMock;

    mapAddRightWallMockSet(&mapAddRightWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddRightWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddRightWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_right(REGULAR_CELL + 1, MAP_WALL_PRESENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddRightWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddRightWallMock.getCount());
}

TEST(map_validate_present, RightPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightWallMock;
    MapWallGetMock mapWallRightGetMock(1);

    mapAddRightWallMockSet(&mapAddRightWallMock);
    mapWallRightGetMockSet(&mapWallRightGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddRightWallMock.getCount());
}

TEST(map_validate_present, TopWallGetCalledCorrectly)
{
    MapWallGetMock mapWallTopGetMock;

    mapWallTopGetMockSet(&mapWallTopGetMock);

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapWallTopGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallTopGetMock.getArg1());
}

TEST(map_validate_present, TopNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}

TEST(map_validate_present, TopNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}

TEST(map_validate_present, TopPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddTopWallMock.getArg1());
}

TEST(map_validate_present, TopOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopWallMock;

    mapAddTopWallMockSet(&mapAddTopWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddTopWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddTopWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_top(REGULAR_CELL + 1, MAP_WALL_PRESENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddTopWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddTopWallMock.getCount());
}

TEST(map_validate_present, TopPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopWallMock;
    MapWallGetMock mapWallTopGetMock(1);

    mapAddTopWallMockSet(&mapAddTopWallMock);
    mapWallTopGetMockSet(&mapWallTopGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}

TEST(map_validate_present, BottomWallGetCalledCorrectly)
{
    MapWallGetMock mapWallBottomGetMock;

    mapWallBottomGetMockSet(&mapWallBottomGetMock);

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(1, mapWallBottomGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallBottomGetMock.getArg1());
}

TEST(map_validate_present, BottomNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_validate_present, BottomNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_validate_present, BottomPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddBottomWallMock.getArg1());
}

TEST(map_validate_present, BottomOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL + 1, MAP_WALL_PRESENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL + 1, MAP_WALL_PRESENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddBottomWallMock.getCount());
}

TEST(map_validate_present, BottomPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomWallMock;
    MapWallGetMock mapWallBottomGetMock(1);

    mapAddBottomWallMockSet(&mapAddBottomWallMock);
    mapWallBottomGetMockSet(&mapWallBottomGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_validate_present, LeftPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;
    MapAddWallNoWallMock mapAddRightWallMock;
    MapAddWallNoWallMock mapAddTopWallMock;
    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);
    mapAddRightWallMockSet(&mapAddRightWallMock);
    mapAddTopWallMockSet(&mapAddTopWallMock);
    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddLeftWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddRightWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddTopWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_validate_present, RightPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;
    MapAddWallNoWallMock mapAddRightWallMock;
    MapAddWallNoWallMock mapAddTopWallMock;
    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);
    mapAddRightWallMockSet(&mapAddRightWallMock);
    mapAddTopWallMockSet(&mapAddTopWallMock);
    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddRightWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddTopWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_validate_present, TopPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;
    MapAddWallNoWallMock mapAddRightWallMock;
    MapAddWallNoWallMock mapAddTopWallMock;
    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);
    mapAddRightWallMockSet(&mapAddRightWallMock);
    mapAddTopWallMockSet(&mapAddTopWallMock);
    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddTopWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddRightWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddBottomWallMock.getCount());
}

TEST(map_validate_present, BottomPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftWallMock;
    MapAddWallNoWallMock mapAddRightWallMock;
    MapAddWallNoWallMock mapAddTopWallMock;
    MapAddWallNoWallMock mapAddBottomWallMock;

    mapAddLeftWallMockSet(&mapAddLeftWallMock);
    mapAddRightWallMockSet(&mapAddRightWallMock);
    mapAddTopWallMockSet(&mapAddTopWallMock);
    mapAddBottomWallMockSet(&mapAddBottomWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_PRESENT);
    }

    CHECK_EQUAL(1, mapAddBottomWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddLeftWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddRightWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_PRESENT);
    CHECK_EQUAL(0, mapAddTopWallMock.getCount());
}
