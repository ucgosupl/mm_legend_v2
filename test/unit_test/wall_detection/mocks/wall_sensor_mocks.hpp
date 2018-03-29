/*
 * file:	map_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for wall sensors.
 */

#ifndef _WALL_SENSOR_MOCKS_HPP_
#define _WALL_SENSOR_MOCKS_HPP_

class WallSensorGetMock
{
private:
    int32_t cnt_ = 0;
    int32_t arg1_ = -1;
    int32_t retVal_ = 0;

public:
    WallSensorGetMock() = default;
    WallSensorGetMock(int32_t retVal);

    int32_t getCount();
    int32_t getArg1();
    int32_t call(int32_t cell_id);
};

void wallSensorGetMockSet(WallSensorGetMock *mock);

#endif /* _WALL_SENSOR_MOCKS_HPP_ */
