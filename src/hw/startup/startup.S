/*
 * File:    startup.S
 * Author:  GAndaLF
 * Brief:   Initial setup for Cortex-M4 core.
 */

.text
.balign 2
.syntax unified
.thumb
.thumb_func
.global Reset_Handler

Reset_Handler:

/*
 * Call init function low_level_init_0 that should be called before data and bss
 * are initialized.
 */
	ldr		r0, =low_level_init_0
	blx		r0

/*
 * Initialize ram with zeros.
 */
	movs	r0, #0
	ldr		r1, =__ram_start
	ldr		r2, =__ram_end

1:	cmp		r1, r2
	itt		lo
	strlo	r0, [r1], #4
	blo		1b

/*
 * Initialize .data section with initial values.
 */
	ldr		r1, =__data_init_start
    ldr		r2, =__data_start
    ldr		r3, =__data_end

1:	cmp		r2, r3
	ittt	lo
	ldrlo	r0, [r1], #4
	strlo	r0, [r2], #4
	blo		1b

/*
 * C++ constructors for global and static functions.
 */
#ifdef __USES_CXX
	ldr		r0, =__libc_init_array
	blx		r0
#endif

/*
 * Call init function low_level_init_1 that should be called after data and bss
 * are initialized.
 */
	ldr		r0, =low_level_init_1
	blx		r0

/*
 * Jump to the main application.
 */
	ldr		r0, =main
	blx		r0

/*
 * C++ destructors for global and static functions.
 */
#ifdef __USES_CXX
	ldr		r0, =__libc_fini_array
	blx		r0
#endif

/*
 * Infinite loop after reaching end of the program.
 */
	b		.

/*
 * __default_low_level_init() - replacement for undefined low_level_init_0()
 * and/or low_level_init_1(). This function just returns.
 */
.text
.balign 2
.syntax unified
.thumb
.thumb_func
.global __default_low_level_init

__default_low_level_init:
	bx		lr

.weak	low_level_init_0
.global	low_level_init_0
.set	low_level_init_0, __default_low_level_init

.weak	low_level_init_1
.global	low_level_init_1
.set	low_level_init_1, __default_low_level_init
