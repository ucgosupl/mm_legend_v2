/*
 * file:	libfixmatrix_test_task.c
 * author:	GAndaLF
 * brief:	Task for testing libfixmatrix library.
 */

#include "libfixmatrix_test_task.h"

#include <stdio.h>
#include "fixmatrix.h"
#include "fixstring.h"

#include "platform_specific.h"

#define LIBFIXMATRIX_TEST_TASK_STACKSIZE        (configMINIMAL_STACK_SIZE * 8)
#define LIBFIXMATRIX_TEST_TASK_PRIORITY         (tskIDLE_PRIORITY + 2)

static void libfixmatrix_test_task(void *params);

void libfixmatrix_test_task_init(void)
{
    rtos_task_create(libfixmatrix_test_task, "matrix",
            LIBFIXMATRIX_TEST_TASK_STACKSIZE, LIBFIXMATRIX_TEST_TASK_PRIORITY);
}

static void libfixmatrix_test_task(void *params)
{
    (void) params;

    mf16 a = {3, 3, 0,
        {{1, 5, 7},
         {5, 4, 2},
         {5, 8, 3}}};
    mf16 identity = {3, 3, 0,
    {{1.0f,0,0}, {0,1.0f,0}, {0,0,1.0f}}};
    mf16 r, q, inv_a;

    while (1)
    {
        printf("Matrix arithmetics:\n");

        printf("Transpose:\n");
        mf16_transpose(&r, &a);
        print_mf16(&r);

        printf("\nMultiply:\n");
        mf16_mul(&r, &a, &a);
        print_mf16(&r);

        printf("\nMultiply with transposed:\n");
        mf16_mul_at(&r, &a, &a);
        print_mf16(&r);

        printf("\nMultiply with scalar:\n");
        mf16_mul_s(&r, &a, 5);
        print_mf16(&r);

        printf("\nDivide with scalar:\n");
        mf16_div_s(&r, &a, 3);
        print_mf16(&r);

        printf("\nAdd:\n");
        mf16_add(&r, &a, &a);
        print_mf16(&r);

        printf("\nSubtract:\n");
        mf16_sub(&r, &a, &a);
        print_mf16(&r);

        printf("\nQR decomposition:\n");
        mf16_qr_decomposition(&q, &r, &a, 1);
        printf("Q:\n");
        print_mf16(&q);
        printf("R:\n");
        print_mf16(&r);

        printf("\nMultiply QR:\n");
        mf16_mul(&inv_a, &q, &r);
        print_mf16(&inv_a);

        printf("\nInversion after QR:\n");
        mf16_solve(&inv_a, &q, &r, &identity);
        print_mf16(&inv_a);

        printf("\nMultiply A with invA:\n");
        mf16_mul(&r, &a, &inv_a);
        print_mf16(&r);

        rtos_delay(5000);

    }
}
