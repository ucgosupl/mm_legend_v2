/*
 * file:	map_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for map module.
 */

#ifndef _MAP_MOCKS_HPP_
#define _MAP_MOCKS_HPP_

class MapWallGetMock
{
private:
    int32_t cnt_ = 0;
    int32_t arg1_ = -1;
    map_wall_state_t retVal_ = MAP_WALL_UNKNOWN;

public:
    MapWallGetMock() = default;
    MapWallGetMock(map_wall_state_t retVal);

    int32_t getCount();
    int32_t getArg1();
    map_wall_state_t call(int32_t cell_id);
};

void mapWallLeftGetMockSet(MapWallGetMock *mock);

#endif /* _MAP_MOCKS_HPP_ */
