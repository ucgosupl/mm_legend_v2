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
    map_wall_state_t retVal_ = MAP_WALL_ERROR;

public:
    MapWallGetMock() = default;
    MapWallGetMock(map_wall_state_t retVal);

    int32_t getCount();
    int32_t getArg1();
    map_wall_state_t call(int32_t cell_id);
};

void mapWallLeftGetMockSet(MapWallGetMock *mock);
void mapWallRightGetMockSet(MapWallGetMock *mock);
void mapWallTopGetMockSet(MapWallGetMock *mock);
void mapWallBottomGetMockSet(MapWallGetMock *mock);

class MapAddWallNoWallMock
{
private:
    int32_t cnt_ = 0;
    int32_t arg1_ = -1;

public:
    MapAddWallNoWallMock() = default;

    int32_t getCount();
    int32_t getArg1();
    void call(int32_t cell_id);
};

void mapAddLeftWallMockSet(MapAddWallNoWallMock *mock);
void mapAddRightWallMockSet(MapAddWallNoWallMock *mock);
void mapAddTopWallMockSet(MapAddWallNoWallMock *mock);
void mapAddBottomWallMockSet(MapAddWallNoWallMock *mock);

void mapAddLeftNoWallMockSet(MapAddWallNoWallMock *mock);
void mapAddRightNoWallMockSet(MapAddWallNoWallMock *mock);
void mapAddTopNoWallMockSet(MapAddWallNoWallMock *mock);
void mapAddBottomNoWallMockSet(MapAddWallNoWallMock *mock);

#endif /* _MAP_MOCKS_HPP_ */
