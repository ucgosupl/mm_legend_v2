#include "platform_specific.h"

#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "adc/adc.h"
    #include "led/led.h"
}

#include "mocks/rtos_mocks.hpp"
#include "mocks/adc_mocks.hpp"
#include "mocks/led_mocks.hpp"
#include "mocks/motor_mocks.hpp"
#include "mocks/endless_loop_mocks.hpp"

extern "C" void vbat_task(void *params);

static void run_vbat_task_and_exit_on_delay_until();

TEST_GROUP(vbat_task_fun)
{
    void setup()
    {
    }

    void teardown()
    {
        rtosTickCountMockSet(nullptr);
        rtosDelayUntilMockSet(nullptr);
        rtosCriticalSectionEnterMockSet(nullptr);
        adcValGetMockSet(nullptr);
        ledOnMockSet(nullptr);
        ledOffMockSet(nullptr);
        ledAllOffMockSet(nullptr);
        motorAllOffMockSet(nullptr);
        endlessLoopMockSet(nullptr);
    }
};

TEST(vbat_task_fun, DelayUntil100ms)
{
    RtosTickCountMock rtosTickCntMock(5);
    RtosDelayUntilMock delayUntilMock;

    rtosTickCountMockSet(&rtosTickCntMock);
    rtosDelayUntilMockSet(&delayUntilMock);

    run_vbat_task_and_exit_on_delay_until();

    CHECK_EQUAL(1, rtosTickCntMock.getCount());
    CHECK_EQUAL(1, delayUntilMock.getCount());
    CHECK_EQUAL(5, delayUntilMock.getArg1());
    CHECK_EQUAL(100, delayUntilMock.getArg2());
}

TEST(vbat_task_fun, AdcCalled)
{
    AdcValGetMock adcValGetMock;

    adcValGetMockSet(&adcValGetMock);

    run_vbat_task_and_exit_on_delay_until();

    CHECK_EQUAL(1, adcValGetMock.getCount());
    CHECK_EQUAL(ADC_VBAT, adcValGetMock.getArg1());
}

TEST(vbat_task_fun, LedOnWhenAboveThreshold)
{
    AdcValGetMock adcValGetMock(ADC_VAL_MIN_ABOVE_THRESHOLD);
    LedOnOffMock ledOnMock;
    LedOnOffMock ledOffMock;

    adcValGetMockSet(&adcValGetMock);
    ledOnMockSet(&ledOnMock);
    ledOffMockSet(&ledOffMock);

    run_vbat_task_and_exit_on_delay_until();

    CHECK_EQUAL(0, ledOffMock.getCount());
    CHECK_EQUAL(1, ledOnMock.getCount());
    CHECK_EQUAL(LED_VBAT, ledOnMock.getArg1());
}

TEST(vbat_task_fun, LedOnWhenBelowThreshold)
{
    AdcValGetMock adcValGetMock(ADC_VAL_MAX_BELOW_THRESHOLD);
    LedOnOffMock ledOnMock;
    LedOnOffMock ledOffMock;

    adcValGetMockSet(&adcValGetMock);
    ledOnMockSet(&ledOnMock);
    ledOffMockSet(&ledOffMock);

    run_vbat_task_and_exit_on_delay_until();

    CHECK_EQUAL(0, ledOnMock.getCount());
    CHECK_EQUAL(1, ledOffMock.getCount());
    CHECK_EQUAL(LED_VBAT, ledOffMock.getArg1());
}

TEST(vbat_task_fun, SafeStateWhenBelowThresholdFor5Iters)
{
    AdcValGetMock adcValGetMock(ADC_VAL_MAX_BELOW_THRESHOLD);
    RtosCriticalSectionMock criticalEnterMock;
    MotorAllOffMock motorAllOffMock;
    LedAllOffMock ledAllOffMock;
    EndlessLoopMock endlessLoopMock(10);
    RtosDelayUntilMock delayUntilMock(5);

    adcValGetMockSet(&adcValGetMock);
    rtosCriticalSectionEnterMockSet(&criticalEnterMock);
    motorAllOffMockSet(&motorAllOffMock);
    ledAllOffMockSet(&ledAllOffMock);
    endlessLoopMockSet(&endlessLoopMock);
    rtosDelayUntilMockSet(&delayUntilMock);

    try
    {
        vbat_task(NULL);
    }
    catch (uint32_t e)
    {
        if (ENDLESS_LOOP_REACHED != e)
        {
            FAIL("Wrong exception caught!");
        }
    }

    CHECK_EQUAL(1, criticalEnterMock.getCount());
    CHECK_EQUAL(1, motorAllOffMock.getCount());
    CHECK_EQUAL(1, ledAllOffMock.getCount());
    CHECK(endlessLoopMock.isReached());
    CHECK_FALSE(delayUntilMock.isMaxItersReached());

}

TEST(vbat_task_fun, NoSafeStateWhenBelowThresholdFor4Iters)
{
    AdcValGetMock adcValGetMock(ADC_VAL_MAX_BELOW_THRESHOLD);
    EndlessLoopMock endlessLoopMock(10);
    RtosDelayUntilMock delayUntilMock(4);

    adcValGetMockSet(&adcValGetMock);
    endlessLoopMockSet(&endlessLoopMock);
    rtosDelayUntilMockSet(&delayUntilMock);

    run_vbat_task_and_exit_on_delay_until();

    CHECK_FALSE(endlessLoopMock.isReached());
    CHECK(delayUntilMock.isMaxItersReached());
}

TEST(vbat_task_fun, NoSafeStateWhenBelowThresholdFor4ItersThenAboveThenBelowAgain)
{
    AdcValGetMock adcValGetMock(ADC_VAL_MAX_BELOW_THRESHOLD, 5, ADC_VAL_MIN_ABOVE_THRESHOLD);
    EndlessLoopMock endlessLoopMock(10);
    RtosDelayUntilMock delayUntilMock(6);

    adcValGetMockSet(&adcValGetMock);
    endlessLoopMockSet(&endlessLoopMock);
    rtosDelayUntilMockSet(&delayUntilMock);

    run_vbat_task_and_exit_on_delay_until();

    CHECK_FALSE(endlessLoopMock.isReached());
    CHECK(delayUntilMock.isMaxItersReached());
}

static void run_vbat_task_and_exit_on_delay_until()
{
    try
    {
        vbat_task(NULL);
    }
    catch (uint32_t e)
    {
        if (RTOS_DELAY_UNTIL_MAX_ITERS_REACHED != e)
        {
            FAIL("Wrong exception caught!");
        }
    }
}
