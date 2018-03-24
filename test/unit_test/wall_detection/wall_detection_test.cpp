#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "wall_detection/wall_detection.h"
}

TEST_GROUP(wall_detection_fun)
{
};

TEST(wall_detection_fun, FirstTest)
{
    wall_detection();
   FAIL("Fail me!");
}
