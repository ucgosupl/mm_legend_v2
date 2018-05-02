/*
 * file:	map_update_mocks.hpp
 * author:	GAndaLF
 * brief:	Mock functions for map update module.
 */

#ifndef _MAP_UPDATE_MOCKS_HPP_
#define _MAP_UPDATE_MOCKS_HPP_

class MapUpdateMock : public NoRet3ArgMock<struct coords, struct coords, map_wall_state_t>
{
private:
    //int32_t cnt_ = 0;
    //struct coords arg1_ = {0};
    //struct coords arg2_ = {0};
    //map_wall_state_t arg3_ = MAP_WALL_ERROR;

public:
    MapUpdateMock() = default;

    //int32_t getCount();
    struct coords * getArg1();
    struct coords * getArg2();
    //map_wall_state_t getArg3();
    void call(struct coords *sensor_pos, struct coords *wall_pos, map_wall_state_t wall_state);
};

void mapUpdateMockSet(MapUpdateMock *mock);

#endif /* _MAP_UPDATE_MOCKS_HPP_ */
