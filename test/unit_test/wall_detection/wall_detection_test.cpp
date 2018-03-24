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

TEST_GROUP(wall_detection_fun)
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

TEST(wall_detection_fun, FirstTest)
{
    FAIL("Implement your test!");
}
