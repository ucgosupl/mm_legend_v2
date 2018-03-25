/**
 * @file:	platform_specific.h
 * @author  GAndaLF
 * @brief:	Symbol overrides used for PC tests.
 */

#ifndef PLATFORM_SPECIFIC_H_
#define PLATFORM_SPECIFIC_H_

#include <stdint.h>
#include <stdbool.h>
#include "../../../src/utils/priority.h"

#define PRIVATE

typedef uint32_t tick_t;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    tick_t rtos_tick_count_get_mock(void);
    void rtos_delay_until_mock(tick_t *last_ptr, tick_t ms);
    void rtos_critical_section_enter_mock(void);
    void rtos_critical_section_exit_mock(void);

    void test_endless_loop(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#define tskIDLE_PRIORITY                0
#define configMINIMAL_STACK_SIZE        1

#define rtos_task_create(fun, name, stack, prio)
#define rtos_tick_count_get()           rtos_tick_count_get_mock()
#define rtos_delay_until(last_ptr, ms)  rtos_delay_until_mock(last_ptr, ms)
#define rtos_critical_section_enter()   rtos_critical_section_enter_mock()
#define rtos_critical_section_exit()    rtos_critical_section_exit_mock()

//#define rtos_task_create(a,b,c,d)      (void)a
//#define rtos_delay(a)

#define TEST_ENDLESS_LOOP()     test_endless_loop()

#endif /* PLATFORM_SPECIFIC_H_ */
