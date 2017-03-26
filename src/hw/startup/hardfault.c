/*
 * File:    hardfault.c
 * Author:  GAndaLF
 * Brief:   Hardfault handler including core register dump.
 */

#include "stm32f4xx.h"
#include "platform_specific.h"

/**
 * @brief Hardfault handler written in assembler.
 *
 * Program jumps here in a case of error. This function dumps core registers
 * and passes them to @HardFault_HandlerC so they could be seen in debugger.
 */
/* Use naked attribute so stack can be handled manually, not by the compiler. */
void __attribute__((naked)) HardFault_Handler(void)
{
    /*
     * Read correct stack pointer depending on core mode of operation. Then
     * is passed to the main hardfault handling function.
     */
    __asm volatile
    (
            " tst lr, #4                                                \n"
            " ite eq                                                    \n"
            " mrseq r0, msp                                             \n"
            " mrsne r0, psp                                             \n"
            " ldr r1, [r0, #24]                                         \n"
            " ldr r2, handler2_address_const                            \n"
            " bx r2                                                     \n"
            " handler2_address_const: .word HardFault_HandlerC			\n"
    );
}

/**
 * @brief Function reading dumped core registers.
 *
 * Function reads CPU registers from the stack dumped by the assembler function.
 *
 * @param hardfault_args    Core registers passed by assembler function.
 */
void HardFault_HandlerC(unsigned long *hardfault_args)
{
    __attribute__((unused)) volatile unsigned long stacked_r0;
    __attribute__((unused)) volatile unsigned long stacked_r1;
    __attribute__((unused)) volatile unsigned long stacked_r2;
    __attribute__((unused)) volatile unsigned long stacked_r3;
    __attribute__((unused)) volatile unsigned long stacked_r12;
    __attribute__((unused)) volatile unsigned long stacked_lr;
    __attribute__((unused)) volatile unsigned long stacked_pc;
    __attribute__((unused)) volatile unsigned long stacked_psr;
    __attribute__((unused)) volatile unsigned long _CFSR;
    __attribute__((unused)) volatile unsigned long _HFSR;
    __attribute__((unused)) volatile unsigned long _AFSR;
    __attribute__((unused)) volatile unsigned long _BFAR;
    __attribute__((unused)) volatile unsigned long _MMAR;

    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);
    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr = ((unsigned long) hardfault_args[5]);
    stacked_pc = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);

    _CFSR = (*((volatile unsigned long *) (0xE000ED28)));
    _HFSR = (*((volatile unsigned long *) (0xE000ED2C)));
    _AFSR = (*((volatile unsigned long *) (0xE000ED3C)));
    _MMAR = (*((volatile unsigned long *) (0xE000ED34)));
    _BFAR = (*((volatile unsigned long *) (0xE000ED38)));

    /* todo: check if program reaches hardfault during OpenOCD start. */
    NVIC_SystemReset();
}
