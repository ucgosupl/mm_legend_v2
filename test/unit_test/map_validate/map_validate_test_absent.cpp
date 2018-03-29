#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
    #include "map/map_internal.h"
}

#include "mocks/map_mocks.hpp"

#define REGULAR_CELL    (2 * MAP_WIDTH + 3)

TEST_GROUP(map_validate_absent)
{
    void setup()
    {
        map_validate_init();
    }

    void teardown()
    {
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

TEST(map_validate_absent, LeftWallGetCalledCorrectly)
{
    MapWallGetMock mapWallLeftGetMock;

    mapWallLeftGetMockSet(&mapWallLeftGetMock);

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapWallLeftGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallLeftGetMock.getArg1());
}

TEST(map_validate_absent, LeftNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_validate_absent, LeftNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_validate_absent, LeftPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddLeftNoWallMock.getArg1());
}

TEST(map_validate_absent, LeftOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_left(REGULAR_CELL + 1, MAP_WALL_ABSENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddLeftNoWallMock.getCount());
}

TEST(map_validate_absent, LeftPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;
    MapWallGetMock mapWallLeftGetMock(1);

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);
    mapWallLeftGetMockSet(&mapWallLeftGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());
}

TEST(map_validate_absent, RightWallGetCalledCorrectly)
{
    MapWallGetMock mapWallRightGetMock;

    mapWallRightGetMockSet(&mapWallRightGetMock);

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapWallRightGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallRightGetMock.getArg1());
}

TEST(map_validate_absent, RightNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_validate_absent, RightNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_validate_absent, RightPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddRightNoWallMock.getArg1());
}

TEST(map_validate_absent, RightOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightNoWallMock;

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_right(REGULAR_CELL + 1, MAP_WALL_ABSENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddRightNoWallMock.getCount());
}

TEST(map_validate_absent, RightPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddRightNoWallMock;
    MapWallGetMock mapWallRightGetMock(1);

    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);
    mapWallRightGetMockSet(&mapWallRightGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());
}

TEST(map_validate_absent, TopWallGetCalledCorrectly)
{
    MapWallGetMock mapWallTopGetMock;

    mapWallTopGetMockSet(&mapWallTopGetMock);

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapWallTopGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallTopGetMock.getArg1());
}

TEST(map_validate_absent, TopNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_validate_absent, TopNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_validate_absent, TopPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddTopNoWallMock.getArg1());
}

TEST(map_validate_absent, TopOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopNoWallMock;

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_top(REGULAR_CELL + 1, MAP_WALL_ABSENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddTopNoWallMock.getCount());
}

TEST(map_validate_absent, TopPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddTopNoWallMock;
    MapWallGetMock mapWallTopGetMock(1);

    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);
    mapWallTopGetMockSet(&mapWallTopGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}

TEST(map_validate_absent, BottomWallGetCalledCorrectly)
{
    MapWallGetMock mapWallBottomGetMock;

    mapWallBottomGetMockSet(&mapWallBottomGetMock);

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(1, mapWallBottomGetMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapWallBottomGetMock.getArg1());
}

TEST(map_validate_absent, BottomNoPermanentAddAfterFirstDetection)
{
    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_absent, BottomNoPermanentAddAfterOneDetectionBelowThreshold)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 1; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_absent, BottomPermanentAddAfterDetectionThresholdReached)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());
    CHECK_EQUAL(REGULAR_CELL, mapAddBottomNoWallMock.getArg1());
}

TEST(map_validate_absent, BottomOneCellPernamentlyAddedThenOther)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    /* Single cell added. */
    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell not added immediately. */
    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());

    for (i = 0; i < MAP_DETECTION_THRESHOLD - 2; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL + 1, MAP_WALL_ABSENT);
    }

    /* Check if other cell not added before threshold. */
    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL + 1, MAP_WALL_ABSENT);

    /* Check if other cell added after threshold. */
    CHECK_EQUAL(2, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_absent, BottomPermanentNotAddedIfAlreadyAddedEarlier)
{
    int32_t i;

    MapAddWallNoWallMock mapAddBottomNoWallMock;
    MapWallGetMock mapWallBottomGetMock(1);

    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);
    mapWallBottomGetMockSet(&mapWallBottomGetMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_absent, LeftPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;
    MapAddWallNoWallMock mapAddRightNoWallMock;
    MapAddWallNoWallMock mapAddTopNoWallMock;
    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);
    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);
    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);
    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddLeftNoWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_absent, RightPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;
    MapAddWallNoWallMock mapAddRightNoWallMock;
    MapAddWallNoWallMock mapAddTopNoWallMock;
    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);
    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);
    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);
    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddRightNoWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_absent, TopPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;
    MapAddWallNoWallMock mapAddRightNoWallMock;
    MapAddWallNoWallMock mapAddTopNoWallMock;
    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);
    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);
    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);
    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddTopNoWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());

    map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddBottomNoWallMock.getCount());
}

TEST(map_validate_absent, BottomPermanentAddOtherWallsNotAddedAfterSingleDetection)
{
    int32_t i;

    MapAddWallNoWallMock mapAddLeftNoWallMock;
    MapAddWallNoWallMock mapAddRightNoWallMock;
    MapAddWallNoWallMock mapAddTopNoWallMock;
    MapAddWallNoWallMock mapAddBottomNoWallMock;

    mapAddLeftNoWallMockSet(&mapAddLeftNoWallMock);
    mapAddRightNoWallMockSet(&mapAddRightNoWallMock);
    mapAddTopNoWallMockSet(&mapAddTopNoWallMock);
    mapAddBottomNoWallMockSet(&mapAddBottomNoWallMock);

    for (i = 0; i < MAP_DETECTION_THRESHOLD; i++)
    {
        map_validate_wall_bottom(REGULAR_CELL, MAP_WALL_ABSENT);
    }

    CHECK_EQUAL(1, mapAddBottomNoWallMock.getCount());

    map_validate_wall_left(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddLeftNoWallMock.getCount());

    map_validate_wall_right(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddRightNoWallMock.getCount());

    map_validate_wall_top(REGULAR_CELL, MAP_WALL_ABSENT);
    CHECK_EQUAL(0, mapAddTopNoWallMock.getCount());
}
