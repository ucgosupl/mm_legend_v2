/*
 * file:	map_validate_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for map_validate module.
 */

#ifndef _MAP_VALIDATE_MOCKS_HPP_
#define _MAP_VALIDATE_MOCKS_HPP_

class MapValidateWallMock
{
private:
    int32_t cnt_ = 0;
    int32_t arg1_ = -1;
    map_wall_state_t arg2_ = MAP_WALL_ERROR;

public:
    MapValidateWallMock() = default;

    int32_t getCount();
    int32_t getArg1();
    map_wall_state_t getArg2();
    void call(int32_t cell_id, map_wall_state_t wall_state);
};

void mapValidateWallLeftMockSet(MapValidateWallMock *mock);
void mapValidateWallRightMockSet(MapValidateWallMock *mock);
void mapValidateWallTopMockSet(MapValidateWallMock *mock);
void mapValidateWallBottomMockSet(MapValidateWallMock *mock);

#endif /* _MAP_VALIDATE_MOCKS_HPP_ */
