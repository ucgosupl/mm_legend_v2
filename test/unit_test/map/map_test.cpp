#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
}

#define REGULAR_CELL    (2 * MAP_WIDTH + 3)

TEST_GROUP(map)
{
    void setup()
    {
        map_init();
    }

    void teardown()
    {
    }
};

TEST(map, StateUnknownAfterInit)
{
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL + 1));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL + 2));

   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + 1));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + 2));

   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + 1));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + 2));

   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL + 1));
   CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL + 2));
}

TEST(map, StateAbsentAfterAddingLeftNoWall)
{
    map_add_left_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_left_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, AdjacentRightStateAbsentAfterAddingLeftNoWall)
{
    map_add_left_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_right_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL - 1));

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL + 1));
}

TEST(map, StateAbsentAfterAddingRightNoWall)
{
    map_add_right_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_right_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, AdjacentLeftStateAbsentAfterAddingRightNoWall)
{
    map_add_right_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL - 1));

    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_left_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL + 1));
}

TEST(map, StateAbsentAfterAddingTopNoWall)
{
    map_add_top_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_top_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, AdjacentBottomStateAbsentAfterAddingTopNoWall)
{
    map_add_top_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL - MAP_WIDTH));

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_bottom_get(REGULAR_CELL + MAP_WIDTH));
}

TEST(map, StateAbsentAfterAddingBottomNoWall)
{
    map_add_bottom_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, AdjacentTopStateAbsentAfterAddingBottomNoWall)
{
    map_add_bottom_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_top_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL - MAP_WIDTH));

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL + MAP_WIDTH));
}

TEST(map, StatePresentAfterAddingLeftWall)
{
    map_add_left_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_left_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, AdjacentRightStatePresentAfterAddingLeftWall)
{
    map_add_left_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_right_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL - 1));

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL + 1));
}

TEST(map, StatePresentAfterAddingRightWall)
{
    map_add_right_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_right_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, AdjacentLeftStatePresentAfterAddingRightWall)
{
    map_add_right_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL - 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL - 1));

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_left_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + 1));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL + 1));
}

TEST(map, StatePresentAfterAddingTopWall)
{
    map_add_top_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get(REGULAR_CELL));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, AdjacentBottomStatePresentAfterAddingTopWall)
{
    map_add_top_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(REGULAR_CELL - MAP_WIDTH));

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(REGULAR_CELL + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(REGULAR_CELL + MAP_WIDTH));
}

TEST(map, StatePresentAfterAddingBottomWall)
{
    map_add_bottom_wall(2 * MAP_WIDTH + 3);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(2 * MAP_WIDTH + 3));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(2 * MAP_WIDTH + 3));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(2 * MAP_WIDTH + 3));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(2 * MAP_WIDTH + 3));
}

TEST(map, AdjacentTopStatePresentAfterAddingBottomWall)
{
    map_add_bottom_wall(2 * MAP_WIDTH + 3);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(2 * MAP_WIDTH + 3 - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(2 * MAP_WIDTH + 3 - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get(2 * MAP_WIDTH + 3 - MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(2 * MAP_WIDTH + 3 - MAP_WIDTH));

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(2 * MAP_WIDTH + 3 + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(2 * MAP_WIDTH + 3 + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(2 * MAP_WIDTH + 3 + MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(2 * MAP_WIDTH + 3 + MAP_WIDTH));
}

/* Corner cases for left and right cannot be easly checked as they are prevented by other checks. */

TEST(map, TopEdgeCornerCase)
{
    map_add_top_wall(MAP_SIZE - 3);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(MAP_SIZE - 3));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(MAP_SIZE - 3));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get(MAP_SIZE - 3));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_bottom_get(MAP_SIZE - 3));

    /* With no guard, add top wall writes above labirynth map cause exception. */
}

TEST(map, BottomEdgeCornerCase)
{
    map_add_bottom_wall(3);

    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_left_get(3));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_right_get(3));
    CHECK_EQUAL(MAP_WALL_UNKNOWN, map_wall_top_get(3));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(3));

    /* With no guard, add bottom wall writes above labirynth map cause exception. */
}

TEST(map, DontChangeIfLeftNotUnknown)
{
    map_add_left_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_left_get(REGULAR_CELL));

    map_add_left_no_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_left_get(REGULAR_CELL));
}

TEST(map, DontChangeIfRightNotUnknown)
{
    map_add_right_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_right_get(REGULAR_CELL));

    map_add_right_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_right_get(REGULAR_CELL));
}

TEST(map, DontChangeIfTopNotUnknown)
{
    map_add_top_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get(REGULAR_CELL));

    map_add_top_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get(REGULAR_CELL));
}

TEST(map, DontChangeIfBottomNotUnknown)
{
    map_add_bottom_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(REGULAR_CELL));

    map_add_bottom_wall(REGULAR_CELL);

    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(REGULAR_CELL));
}

TEST(map, InitialStateLeft)
{
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_left_get(MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_left_get((MAP_HEIGHT - 1) * MAP_WIDTH));
}

TEST(map, InitialStateRight)
{
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_right_get(MAP_WIDTH - 1));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_right_get(MAP_HEIGHT * MAP_WIDTH - 1));
}

TEST(map, InitialStateBottom)
{
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(1));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(MAP_WIDTH - 2));
}

TEST(map, InitialStateTop)
{
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get((MAP_HEIGHT - 1) * MAP_WIDTH));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get(MAP_HEIGHT * MAP_WIDTH - 1));
}

TEST(map, InitialStateStart)
{
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_top_get(0));
    CHECK_EQUAL(MAP_WALL_PRESENT, map_wall_bottom_get(MAP_WIDTH));

    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_right_get(0));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_left_get(1));
}

TEST(map, InitialStateCenter)
{
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_right_get((MAP_HEIGHT/2 - 1) * MAP_WIDTH + MAP_WIDTH/2 - 1));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_left_get((MAP_HEIGHT/2 - 1) * MAP_WIDTH + MAP_WIDTH/2));

    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_right_get(MAP_HEIGHT/2  * MAP_WIDTH + MAP_WIDTH/2 - 1));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_left_get(MAP_HEIGHT/2 * MAP_WIDTH + MAP_WIDTH/2));

    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_top_get((MAP_HEIGHT/2 - 1) * MAP_WIDTH + MAP_WIDTH/2 - 1));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_bottom_get(MAP_HEIGHT/2 * MAP_WIDTH + MAP_WIDTH/2 - 1));

    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_top_get((MAP_HEIGHT/2 - 1) * MAP_WIDTH + MAP_WIDTH/2));
    CHECK_EQUAL(MAP_WALL_ABSENT, map_wall_bottom_get(MAP_HEIGHT/2 * MAP_WIDTH + MAP_WIDTH/2));
}
