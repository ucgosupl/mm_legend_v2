/*
 * file:    solver_mocks.cpp
 * author:  GAndaLF
 * brief:   Mock functions for solver module.
 */

#include "platform_specific.h"

extern "C"
{
    #include "solver/solver.h"
}

#include "solver_mocks.hpp"

static SolverCalcPathMock *solverCalcPathToCenterMock = nullptr;
static SolverCalcPathMock *solverCalcPathToStartMock = nullptr;

static SolverCellNextGetMock *solverCellNextGetMock = nullptr;

int32_t SolverCalcPathMock::getCount()
{
    return cnt_;
}

void SolverCalcPathMock::call()
{
    cnt_++;
}

void solverCalcPathToCenterMockSet(SolverCalcPathMock *mock)
{
    solverCalcPathToCenterMock = mock;
}

void solver_calc_path_to_center(void)
{
    if (nullptr != solverCalcPathToCenterMock)
    {
        return solverCalcPathToCenterMock->call();
    }
}

void solverCalcPathToStartMockSet(SolverCalcPathMock *mock)
{
    solverCalcPathToStartMock = mock;
}

void solver_calc_path_to_start(void)
{
    if (nullptr != solverCalcPathToStartMock)
    {
        return solverCalcPathToStartMock->call();
    }
}

SolverCellNextGetMock::SolverCellNextGetMock(int32_t retVal) : retVal_(retVal) {};

int32_t SolverCellNextGetMock::getCount()
{
    return cnt_;
}

int32_t SolverCellNextGetMock::getArg1()
{
    return arg1_;
}

int32_t SolverCellNextGetMock::call(int32_t cell_id)
{
    cnt_++;

    arg1_ = cell_id;

    return retVal_;
}

void solverCellNextGetMockSet(SolverCellNextGetMock *mock)
{
    solverCellNextGetMock = mock;
}

int32_t solver_cell_id_next_get(int32_t cell_id)
{
    if (nullptr != solverCellNextGetMock)
    {
        return solverCellNextGetMock->call(cell_id);
    }

    return 0;
}
