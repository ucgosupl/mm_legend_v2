/*
 * file:	map_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for map module.
 */

#ifndef _MAP_MOCKS_HPP_
#define _MAP_MOCKS_HPP_

using MapWallGetMock = Ret1ArgMock<map_wall_state_t, int32_t>;
using MapAddWallNoWallMock = Ret1ArgMock<map_wall_state_t, int32_t>;

void mapWallLeftGetMockSet(MapWallGetMock *mock);
void mapWallRightGetMockSet(MapWallGetMock *mock);
void mapWallTopGetMockSet(MapWallGetMock *mock);
void mapWallBottomGetMockSet(MapWallGetMock *mock);

void mapAddLeftWallMockSet(MapAddWallNoWallMock *mock);
void mapAddRightWallMockSet(MapAddWallNoWallMock *mock);
void mapAddTopWallMockSet(MapAddWallNoWallMock *mock);
void mapAddBottomWallMockSet(MapAddWallNoWallMock *mock);

void mapAddLeftNoWallMockSet(MapAddWallNoWallMock *mock);
void mapAddRightNoWallMockSet(MapAddWallNoWallMock *mock);
void mapAddTopNoWallMockSet(MapAddWallNoWallMock *mock);
void mapAddBottomNoWallMockSet(MapAddWallNoWallMock *mock);

#endif /* _MAP_MOCKS_HPP_ */
