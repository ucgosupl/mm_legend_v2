/*
 * file:    map_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for map module.
 */

#include "platform_specific.h"

extern "C"
{
    #include "map/map.h"
}

#include "map_mocks.hpp"

static MapWallGetMock *mapWallLeftGetMock = nullptr;
static MapWallGetMock *mapWallRightGetMock = nullptr;
static MapWallGetMock *mapWallTopGetMock = nullptr;
static MapWallGetMock *mapWallBottomGetMock = nullptr;

static MapAddWallNoWallMock *mapAddLeftWallMock = nullptr;
static MapAddWallNoWallMock *mapAddRightWallMock = nullptr;
static MapAddWallNoWallMock *mapAddTopWallMock = nullptr;
static MapAddWallNoWallMock *mapAddBottomWallMock = nullptr;

static MapAddWallNoWallMock *mapAddLeftNoWallMock = nullptr;
static MapAddWallNoWallMock *mapAddRightNoWallMock = nullptr;
static MapAddWallNoWallMock *mapAddTopNoWallMock = nullptr;
static MapAddWallNoWallMock *mapAddBottomNoWallMock = nullptr;

MapWallGetMock::MapWallGetMock(map_wall_state_t retVal) : retVal_(retVal) {};

int32_t MapWallGetMock::getCount()
{
    return cnt_;
}

int32_t MapWallGetMock::getArg1()
{
    return arg1_;
}

map_wall_state_t MapWallGetMock::call(int32_t cell_id)
{
    cnt_++;

    arg1_ = cell_id;

    return retVal_;
}

void mapWallLeftGetMockSet(MapWallGetMock *mock)
{
    mapWallLeftGetMock = mock;
}

map_wall_state_t map_wall_left_get(int32_t cell_id)
{
    if (nullptr != mapWallLeftGetMock)
    {
        return mapWallLeftGetMock->call(cell_id);
    }

    return MAP_WALL_UNKNOWN;
}

void mapWallRightGetMockSet(MapWallGetMock *mock)
{
    mapWallRightGetMock = mock;
}

map_wall_state_t map_wall_right_get(int32_t cell_id)
{
    if (nullptr != mapWallRightGetMock)
    {
        return mapWallRightGetMock->call(cell_id);
    }

    return MAP_WALL_UNKNOWN;
}

void mapWallTopGetMockSet(MapWallGetMock *mock)
{
    mapWallTopGetMock = mock;
}

map_wall_state_t map_wall_top_get(int32_t cell_id)
{
    if (nullptr != mapWallTopGetMock)
    {
        return mapWallTopGetMock->call(cell_id);
    }

    return MAP_WALL_UNKNOWN;
}

void mapWallBottomGetMockSet(MapWallGetMock *mock)
{
    mapWallBottomGetMock = mock;
}

map_wall_state_t map_wall_bottom_get(int32_t cell_id)
{
    if (nullptr != mapWallBottomGetMock)
    {
        return mapWallBottomGetMock->call(cell_id);
    }

    return MAP_WALL_UNKNOWN;
}

int32_t MapAddWallNoWallMock::getCount()
{
    return cnt_;
}

int32_t MapAddWallNoWallMock::getArg1()
{
    return arg1_;
}

void MapAddWallNoWallMock::call(int32_t cell_id)
{
    cnt_++;

    arg1_ = cell_id;
}

void mapAddLeftWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddLeftWallMock = mock;
}

void map_add_left_wall(int32_t cell_id)
{
    if (nullptr != mapAddLeftWallMock)
    {
        mapAddLeftWallMock->call(cell_id);
    }
}

void mapAddRightWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddRightWallMock = mock;
}

void map_add_right_wall(int32_t cell_id)
{
    if (nullptr != mapAddRightWallMock)
    {
        mapAddRightWallMock->call(cell_id);
    }
}

void mapAddTopWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddTopWallMock = mock;
}

void map_add_top_wall(int32_t cell_id)
{
    if (nullptr != mapAddTopWallMock)
    {
        mapAddTopWallMock->call(cell_id);
    }
}

void mapAddBottomWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddBottomWallMock = mock;
}

void map_add_bottom_wall(int32_t cell_id)
{
    if (nullptr != mapAddBottomWallMock)
    {
        mapAddBottomWallMock->call(cell_id);
    }
}

void mapAddLeftNoWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddLeftNoWallMock = mock;
}

void map_add_left_no_wall(int32_t cell_id)
{
    if (nullptr != mapAddLeftNoWallMock)
    {
        mapAddLeftNoWallMock->call(cell_id);
    }
}

void mapAddRightNoWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddRightNoWallMock = mock;
}

void map_add_right_no_wall(int32_t cell_id)
{
    if (nullptr != mapAddRightNoWallMock)
    {
        mapAddRightNoWallMock->call(cell_id);
    }
}

void mapAddTopNoWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddTopNoWallMock = mock;
}

void map_add_top_no_wall(int32_t cell_id)
{
    if (nullptr != mapAddTopNoWallMock)
    {
        mapAddTopNoWallMock->call(cell_id);
    }
}

void mapAddBottomNoWallMockSet(MapAddWallNoWallMock *mock)
{
    mapAddBottomNoWallMock = mock;
}

void map_add_bottom_no_wall(int32_t cell_id)
{
    if (nullptr != mapAddBottomNoWallMock)
    {
        mapAddBottomNoWallMock->call(cell_id);
    }
}
