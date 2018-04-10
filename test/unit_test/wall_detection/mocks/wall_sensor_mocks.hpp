/*
 * file:	map_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for wall sensors.
 */

#ifndef _WALL_SENSOR_MOCKS_HPP_
#define _WALL_SENSOR_MOCKS_HPP_

using WallSensorGetMock = Ret1ArgMock<int32_t, int32_t>;

void wallSensorGetMockSet(WallSensorGetMock *mock);

#endif /* _WALL_SENSOR_MOCKS_HPP_ */
