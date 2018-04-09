#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "search/search.h"
    #include "search/search_internal.h"
}

#include "mocks/solver_mocks.hpp"
#include "mocks/search_mocks.hpp"
#include "mocks/profile_mocks.hpp"

extern "C"
{
    search_state_t search_state_get(void);
    void search_state_set(search_state_t val);

    int32_t search_cell_id_current_get(void);
    void search_cell_id_current_set(int32_t val);

    int32_t search_cell_id_next_get(void);
    void search_cell_id_next_set(int32_t val);

    bool search_is_solver_center_get(void);
    void search_is_solver_center_set(bool val);
}

TEST_GROUP(search_state_machine)
{
    void setup()
    {
        search_init();
    }

    void teardown()
    {
        solverCalcPathToCenterMockSet(nullptr);
        solverCalcPathToStartMockSet(nullptr);
        solverCellNextGetMockSet(nullptr);

        searchIsWallBlockingMockSet(nullptr);
        searchNextMoveGetMockSet(nullptr);
        searchIsFinalPathFoundMockSet(nullptr);

        profileSearchTurnLeftMockSet(nullptr);
        profileSearchTurnRightMockSet(nullptr);
        profileSearchTurnAroundMockSet(nullptr);
        profileSearchMoveForwardMockSet(nullptr);
    }
};

TEST(search_state_machine, Init)
{
    search_state_set(SEARCH_STATE_ERROR);
    search_cell_id_current_set(-1);

    search_init();

    CHECK_EQUAL(SEARCH_STATE_SOLVE, search_state_get());
    CHECK_EQUAL(0, search_cell_id_current_get());
    CHECK_TRUE(search_is_solver_center_get());
}

TEST(search_state_machine, AfterInitSolveCalled)
{
    SolverCalcPathMock solverCalcPathToCenterMock;

    solverCalcPathToCenterMockSet(&solverCalcPathToCenterMock);

    search_state_machine();

    CHECK_EQUAL(1, solverCalcPathToCenterMock.getCount());
}

TEST(search_state_machine, WhenStateGetNextSolveNotCalled)
{
    SolverCalcPathMock solverCalcPathToCenterMock;

    solverCalcPathToCenterMockSet(&solverCalcPathToCenterMock);
    search_state_set(SEARCH_STATE_GET_NEXT);

    search_state_machine();

    CHECK_EQUAL(0, solverCalcPathToCenterMock.getCount());
}

TEST(search_state_machine, NextGetCalled)
{
    SolverCellNextGetMock solverCellNextGetMock;

    solverCellNextGetMockSet(&solverCellNextGetMock);

    search_state_machine();

    CHECK_EQUAL(1, solverCellNextGetMock.getCount());
    CHECK_EQUAL(0, solverCellNextGetMock.getArg1());
}

TEST(search_state_machine, GivenSolverCenterWhenGoalReachedThenSwitchToSolverStart)
{
    SolverCalcPathMock solverCalcPathToCenterMock;
    SolverCalcPathMock solverCalcPathToStartMock;
    SolverCellNextGetMock solverCellNextGetMock(-1);

    solverCalcPathToCenterMockSet(&solverCalcPathToCenterMock);
    solverCalcPathToStartMockSet(&solverCalcPathToStartMock);
    solverCellNextGetMockSet(&solverCellNextGetMock);

    search_state_set(SEARCH_STATE_GET_NEXT);
    search_is_solver_center_set(true);
    search_state_machine();

    CHECK_EQUAL(0, solverCalcPathToCenterMock.getCount());
    CHECK_EQUAL(0, solverCalcPathToStartMock.getCount());

    search_state_machine();

    CHECK_EQUAL(0, solverCalcPathToCenterMock.getCount());
    CHECK_EQUAL(1, solverCalcPathToStartMock.getCount());
}

TEST(search_state_machine, GivenSolverStartWhenGoalReachedAndNotFinishedThenSwitchToSolverCenter)
{
    SolverCalcPathMock solverCalcPathToCenterMock;
    SolverCalcPathMock solverCalcPathToStartMock;
    SolverCellNextGetMock solverCellNextGetMock(-1);

    solverCalcPathToCenterMockSet(&solverCalcPathToCenterMock);
    solverCalcPathToStartMockSet(&solverCalcPathToStartMock);
    solverCellNextGetMockSet(&solverCellNextGetMock);

    search_state_set(SEARCH_STATE_GET_NEXT);
    search_is_solver_center_set(false);
    search_state_machine();

    CHECK_EQUAL(0, solverCalcPathToCenterMock.getCount());
    CHECK_EQUAL(0, solverCalcPathToStartMock.getCount());

    search_state_machine();

    CHECK_EQUAL(1, solverCalcPathToCenterMock.getCount());
    CHECK_EQUAL(0, solverCalcPathToStartMock.getCount());
}

TEST(search_state_machine, GivenSolverStartWhenGoalReachedAndFinishedThenStateFinished)
{
    SolverCalcPathMock solverCalcPathToCenterMock;
    SolverCalcPathMock solverCalcPathToStartMock;
    SolverCellNextGetMock solverCellNextGetMock(-1);
    SearchIsFinalPathFoundMock searchIsFinalPathFoundMock(true);

    solverCalcPathToCenterMockSet(&solverCalcPathToCenterMock);
    solverCalcPathToStartMockSet(&solverCalcPathToStartMock);
    solverCellNextGetMockSet(&solverCellNextGetMock);
    searchIsFinalPathFoundMockSet(&searchIsFinalPathFoundMock);

    search_state_set(SEARCH_STATE_GET_NEXT);
    search_is_solver_center_set(false);
    search_state_machine();

    CHECK_EQUAL(SEARCH_STATE_FINISHED, search_state_get());

    search_state_machine();

    CHECK_EQUAL(SEARCH_STATE_FINISHED, search_state_get());
}

TEST(search_state_machine, IsWallBlockingCalled)
{
    SolverCellNextGetMock solverCellNextGetMock(10);
    SearchIsWallBlockingMock searchIsWallBlockingMock(false);

    solverCellNextGetMockSet(&solverCellNextGetMock);
    searchIsWallBlockingMockSet(&searchIsWallBlockingMock);

    search_state_machine();

    CHECK_EQUAL(1, searchIsWallBlockingMock.getCount());
    CHECK_EQUAL(0, searchIsWallBlockingMock.getArg1());
    CHECK_EQUAL(10, searchIsWallBlockingMock.getArg2());
}

TEST(search_state_machine, WhenIsWallBlockingTrueAndSolveCenterThenSolverCenterSolveNextGetAndIsWallBlockingCalledAgain)
{
    SolverCalcPathMock solverCalcPathToCenterMock;
    SolverCellNextGetMock solverCellNextGetMock(10);
    SearchIsWallBlockingMock searchIsWallBlockingMock(true);

    solverCalcPathToCenterMockSet(&solverCalcPathToCenterMock);
    solverCellNextGetMockSet(&solverCellNextGetMock);
    searchIsWallBlockingMockSet(&searchIsWallBlockingMock);
    search_is_solver_center_set(true);

    search_state_machine();

    CHECK_EQUAL(2, solverCalcPathToCenterMock.getCount());
    CHECK_EQUAL(2, solverCellNextGetMock.getCount());
    CHECK_EQUAL(2, searchIsWallBlockingMock.getCount());
}

TEST(search_state_machine, WhenIsWallBlockingTrueAndSolveStartThenSolverStartSolveNextGetAndIsWallBlockingCalledAgain)
{
    SolverCalcPathMock solverCalcPathToStartMock;
    SolverCellNextGetMock solverCellNextGetMock(10);
    SearchIsWallBlockingMock searchIsWallBlockingMock(true);

    solverCalcPathToStartMockSet(&solverCalcPathToStartMock);
    solverCellNextGetMockSet(&solverCellNextGetMock);
    searchIsWallBlockingMockSet(&searchIsWallBlockingMock);
    search_is_solver_center_set(false);

    search_state_machine();

    CHECK_EQUAL(2, solverCalcPathToStartMock.getCount());
    CHECK_EQUAL(2, solverCellNextGetMock.getCount());
    CHECK_EQUAL(2, searchIsWallBlockingMock.getCount());
}

TEST(search_state_machine, NextMoveGetCalled)
{
    SolverCellNextGetMock solverCellNextGetMock(10);
    SearchNextMoveGetMock searchNextMoveGetMock;

    solverCellNextGetMockSet(&solverCellNextGetMock);
    searchNextMoveGetMockSet(&searchNextMoveGetMock);

    search_state_machine();

    CHECK_EQUAL(1, searchNextMoveGetMock.getCount());
    CHECK_EQUAL(0, searchNextMoveGetMock.getArg1());
    CHECK_EQUAL(10, searchNextMoveGetMock.getArg2());
}

TEST(search_state_machine, NextTurnLeftHandling)
{
    SearchNextMoveGetMock searchNextMoveGetMock(SEARCH_MOVE_TURN_LEFT);
    ProfileSearchTurnMoveMock profileSearchTurnLeftMock;

    searchNextMoveGetMockSet(&searchNextMoveGetMock);
    profileSearchTurnLeftMockSet(&profileSearchTurnLeftMock);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchTurnLeftMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_TURNING_LEFT, search_state_get());
}

TEST(search_state_machine, NextTurnRightHandling)
{
    SearchNextMoveGetMock searchNextMoveGetMock(SEARCH_MOVE_TURN_RIGHT);
    ProfileSearchTurnMoveMock profileSearchTurnRightMock;

    searchNextMoveGetMockSet(&searchNextMoveGetMock);
    profileSearchTurnRightMockSet(&profileSearchTurnRightMock);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchTurnRightMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_TURNING_RIGHT, search_state_get());
}

TEST(search_state_machine, NextTurnAroundHandling)
{
    SearchNextMoveGetMock searchNextMoveGetMock(SEARCH_MOVE_TURN_AROUND);
    ProfileSearchTurnMoveMock profileSearchTurnAroundMock;

    searchNextMoveGetMockSet(&searchNextMoveGetMock);
    profileSearchTurnAroundMockSet(&profileSearchTurnAroundMock);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchTurnAroundMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_TURNING_AROUND, search_state_get());
}

TEST(search_state_machine, NextMoveForwardHandling)
{
    SearchNextMoveGetMock searchNextMoveGetMock(SEARCH_MOVE_FORWARD);
    ProfileSearchTurnMoveMock profileSearchMoveForwardMock;

    searchNextMoveGetMockSet(&searchNextMoveGetMock);
    profileSearchMoveForwardMockSet(&profileSearchMoveForwardMock);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchMoveForwardMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_MOVING_FORWARD, search_state_get());
}

TEST(search_state_machine, StateTurningLeftDoesntChangeIfProfilerNotCompleted)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(false);

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    search_state_set(SEARCH_STATE_TURNING_LEFT);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_TURNING_LEFT, search_state_get());
}

TEST(search_state_machine, GivenStateTurningLeftWhenProfilerCompletedThenNextStateMovingForward)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(true);
    ProfileSearchTurnMoveMock profileSearchMoveForwardMock;

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    profileSearchMoveForwardMockSet(&profileSearchMoveForwardMock);
    search_state_set(SEARCH_STATE_TURNING_LEFT);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(1, profileSearchMoveForwardMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_MOVING_FORWARD, search_state_get());
}

TEST(search_state_machine, StateTurningRightDoesntChangeIfProfilerNotCompleted)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(false);

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    search_state_set(SEARCH_STATE_TURNING_RIGHT);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_TURNING_RIGHT, search_state_get());
}

TEST(search_state_machine, GivenStateTurningRightWhenProfilerCompletedThenNextStateMovingForward)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(true);
    ProfileSearchTurnMoveMock profileSearchMoveForwardMock;

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    profileSearchMoveForwardMockSet(&profileSearchMoveForwardMock);
    search_state_set(SEARCH_STATE_TURNING_RIGHT);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(1, profileSearchMoveForwardMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_MOVING_FORWARD, search_state_get());
}

TEST(search_state_machine, StateTurningAroundDoesntChangeIfProfilerNotCompleted)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(false);

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    search_state_set(SEARCH_STATE_TURNING_AROUND);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_TURNING_AROUND, search_state_get());
}

TEST(search_state_machine, GivenStateTurningAroundWhenProfilerCompletedThenNextStateMovingForward)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(true);
    ProfileSearchTurnMoveMock profileSearchMoveForwardMock;

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    profileSearchMoveForwardMockSet(&profileSearchMoveForwardMock);
    search_state_set(SEARCH_STATE_TURNING_AROUND);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(1, profileSearchMoveForwardMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_MOVING_FORWARD, search_state_get());
}

TEST(search_state_machine, StateMovingForwardDoesntChangeIfProfilerNotCompleted)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(false);

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    search_state_set(SEARCH_STATE_MOVING_FORWARD);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_MOVING_FORWARD, search_state_get());
}

TEST(search_state_machine, GivenStateMovingForwardWhenProfilerCompletedThenNextStateGetNextAndCellUpdated)
{
    ProfileSearchIsCompletedMock profileSearchIsCompletedMock(true);

    profileSearchIsCompletedMockSet(&profileSearchIsCompletedMock);
    search_state_set(SEARCH_STATE_MOVING_FORWARD);
    search_cell_id_current_set(5);
    search_cell_id_next_set(10);

    search_state_machine();

    CHECK_EQUAL(1, profileSearchIsCompletedMock.getCount());
    CHECK_EQUAL(SEARCH_STATE_GET_NEXT, search_state_get());
    CHECK_EQUAL(10, search_cell_id_current_get());
}

TEST(search_state_machine, IsFinished)
{
    search_state_set(SEARCH_STATE_MOVING_FORWARD);
    CHECK_FALSE(search_is_finished());

    search_state_set(SEARCH_STATE_FINISHED);
    CHECK_TRUE(search_is_finished());
}
