/*
 * file:	map_validate_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for map_validate module.
 */

#ifndef _MAP_VALIDATE_MOCKS_HPP_
#define _MAP_VALIDATE_MOCKS_HPP_

using MapValidateWallMock = NoRet2ArgMock<int32_t, map_wall_state_t>;

void mapValidateWallLeftMockSet(MapValidateWallMock *mock);
void mapValidateWallRightMockSet(MapValidateWallMock *mock);
void mapValidateWallTopMockSet(MapValidateWallMock *mock);
void mapValidateWallBottomMockSet(MapValidateWallMock *mock);

#endif /* _MAP_VALIDATE_MOCKS_HPP_ */
