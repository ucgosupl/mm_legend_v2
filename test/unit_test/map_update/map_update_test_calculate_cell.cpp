#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "map/map.h"
}

extern "C" int32_t calculate_cell(int32_t x, int32_t y);

TEST_GROUP(wall_detection_calculate_cell)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(wall_detection_calculate_cell, CheckIfCell0Detected1)
{
   CHECK_EQUAL(0, calculate_cell(0, 0));
}

TEST(wall_detection_calculate_cell, CheckIfCell0Detected2)
{
   CHECK_EQUAL(0, calculate_cell(MAP_CELL_WIDTH_MM - 1, 0));
}

TEST(wall_detection_calculate_cell, CheckIfCell0Detected3)
{
    CHECK_EQUAL(0, calculate_cell(0, MAP_CELL_WIDTH_MM - 1));
}

TEST(wall_detection_calculate_cell, CheckIfCell1Detected1)
{
    CHECK_EQUAL(1, calculate_cell(MAP_CELL_WIDTH_MM, 0));
}

TEST(wall_detection_calculate_cell, CheckIfCell1Detected2)
{
    CHECK_EQUAL(1, calculate_cell(2 * MAP_CELL_WIDTH_MM - 1, 0));
}

TEST(wall_detection_calculate_cell, CheckIfCell1Detected3)
{
    CHECK_EQUAL(1, calculate_cell(MAP_CELL_WIDTH_MM, MAP_CELL_WIDTH_MM - 1));
}

TEST(wall_detection_calculate_cell, CheckIfCell2Detected1)
{
    CHECK_EQUAL(2, calculate_cell(2 * MAP_CELL_WIDTH_MM, 0));
}

TEST(wall_detection_calculate_cell, CheckIfCell16Detected1)
{
    CHECK_EQUAL(16, calculate_cell(0, MAP_CELL_WIDTH_MM));
}

TEST(wall_detection_calculate_cell, CheckIfCell16Detected2)
{
    CHECK_EQUAL(16, calculate_cell(MAP_CELL_WIDTH_MM - 1, MAP_CELL_WIDTH_MM));
}

TEST(wall_detection_calculate_cell, CheckIfCell17Detected1)
{
    CHECK_EQUAL(17, calculate_cell(MAP_CELL_WIDTH_MM, MAP_CELL_WIDTH_MM));
}

TEST(wall_detection_calculate_cell, CheckIfCell32Detected1)
{
    CHECK_EQUAL(32, calculate_cell(0, 2 * MAP_CELL_WIDTH_MM));
}

TEST(wall_detection_calculate_cell, CheckIfCell15Detected1)
{
    CHECK_EQUAL(15, calculate_cell(MAP_WIDTH * MAP_CELL_WIDTH_MM - 1, 0));
}

TEST(wall_detection_calculate_cell, CheckIfPosXOutOfBoundsDetected)
{
    CHECK_EQUAL(-1, calculate_cell(MAP_WIDTH * MAP_CELL_WIDTH_MM, 0));
}

TEST(wall_detection_calculate_cell, CheckIfCell240Detected1)
{
    CHECK_EQUAL(240, calculate_cell(0, MAP_WIDTH * MAP_CELL_WIDTH_MM - 1));
}

TEST(wall_detection_calculate_cell, CheckIfPosYOutOfBoundsDetected)
{
    CHECK_EQUAL(-1, calculate_cell(0, MAP_WIDTH * MAP_CELL_WIDTH_MM));
}
