#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
    #include "position/position.h"
    #include "wall_detection/wall_detection.h"
}

#include "mocks/map_mocks.hpp"
#include "mocks/position_mocks.hpp"

TEST_GROUP(wall_detection_calculate_cell)
{
    void setup()
    {
    }

    void teardown()
    {
        posXMockSet(nullptr);
        posYMockSet(nullptr);

        mapWallLeftGetMockSet(nullptr);
    }
};

TEST(wall_detection_calculate_cell, CheckIfCell0Detected1)
{
    PositionGetMock posXMock(0);
    PositionGetMock posYMock(0);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(0, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell0Detected2)
{
    PositionGetMock posXMock(CELL_WIDTH_MM - 1);
    PositionGetMock posYMock(0);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(0, mapWallLeftMock.getArg1());
}


TEST(wall_detection_calculate_cell, CheckIfCell0Detected3)
{
    PositionGetMock posXMock(0);
    PositionGetMock posYMock(CELL_WIDTH_MM - 1);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(0, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell1Detected1)
{
    PositionGetMock posXMock(CELL_WIDTH_MM);
    PositionGetMock posYMock(0);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(1, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell1Detected2)
{
    PositionGetMock posXMock(2 * CELL_WIDTH_MM - 1);
    PositionGetMock posYMock(0);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(1, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell1Detected3)
{
    PositionGetMock posXMock(CELL_WIDTH_MM);
    PositionGetMock posYMock(CELL_WIDTH_MM - 1);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(1, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell2Detected1)
{
    PositionGetMock posXMock(2 * CELL_WIDTH_MM);
    PositionGetMock posYMock(0);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(2, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell16Detected1)
{
    PositionGetMock posXMock(0);
    PositionGetMock posYMock(CELL_WIDTH_MM);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(MAP_WIDTH, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell16Detected2)
{
    PositionGetMock posXMock(CELL_WIDTH_MM - 1);
    PositionGetMock posYMock(CELL_WIDTH_MM);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(MAP_WIDTH, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell17Detected1)
{
    PositionGetMock posXMock(CELL_WIDTH_MM);
    PositionGetMock posYMock(CELL_WIDTH_MM);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(MAP_WIDTH + 1, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell32Detected1)
{
    PositionGetMock posXMock(0);
    PositionGetMock posYMock(2 * CELL_WIDTH_MM);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(2 * MAP_WIDTH, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfCell15Detected1)
{
    PositionGetMock posXMock(MAP_WIDTH * CELL_WIDTH_MM - 1);
    PositionGetMock posYMock(0);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(MAP_WIDTH - 1, mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfPosXOutOfBoundsDetected)
{
    PositionGetMock posXMock(MAP_WIDTH * CELL_WIDTH_MM);
    PositionGetMock posYMock(0);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(0, mapWallLeftMock.getCount());
}

TEST(wall_detection_calculate_cell, CheckIfCell240Detected1)
{
    PositionGetMock posXMock(0);
    PositionGetMock posYMock(MAP_WIDTH * CELL_WIDTH_MM - 1);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(MAP_WIDTH * (MAP_WIDTH - 1), mapWallLeftMock.getArg1());
}

TEST(wall_detection_calculate_cell, CheckIfPosYOutOfBoundsDetected)
{
    PositionGetMock posXMock(0);
    PositionGetMock posYMock(MAP_WIDTH * CELL_WIDTH_MM);
    MapWallGetMock mapWallLeftMock;

    posXMockSet(&posXMock);
    posYMockSet(&posYMock);
    mapWallLeftGetMockSet(&mapWallLeftMock);

    wall_detection();

   CHECK_EQUAL(0, mapWallLeftMock.getCount());
}
