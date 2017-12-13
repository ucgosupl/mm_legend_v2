/*
 * file:	position.c
 * author:	GAndaLF
 * brief:	Position estimation task.
 */

#include "platform_specific.h"
#include <math.h>

#include "fixmatrix.h"
#include "imu/imu.h"
#include "motor/motor.h"

#include "position.h"

#define ROBOT_WIDTH     80.0f

#define deg2rad(deg) ((deg) * M_PI / 180.0)
#define rad2deg(rad) ((rad) * 180.0 / M_PI)

#define state_get_x(x)          ((x)->data[0][0])
#define state_get_y(x)          ((x)->data[1][0])
#define state_get_alpha(x)      ((x)->data[2][0])
#define state_get_v(x)          ((x)->data[3][0])
#define state_get_omega(x)      ((x)->data[4][0])

struct pos_state
{
    float x;
    float y;
    float alpha;
    float v;
    float omega;
};

static struct pos_state state;

#define dt                      0.01f

#define enc_sdev                1.0f
#define enc_ang_sdev            10.0f
#define gyro_sdev               2.0f

#define state_x_sdev            1.0f
#define state_y_sdev            1.0f
#define state_alpha_sdev        1.0f
#define state_v_sdev            50.0f
#define state_omega_sdev        50.0f

static const mf16 C = {3, 5, 0,
        {{0,    0,  0,  dt, 0},
         {0,    0,  0,  0,  dt},
         {0,    0,  0,  0,  1}}};

static const mf16 V = {5, 5, 0,
        {{state_x_sdev*state_x_sdev*dt,             0,  0,  0,  0},
         {0,    state_y_sdev*state_y_sdev*dt,           0,  0,  0},
         {0,    0,  state_alpha_sdev*state_alpha_sdev*dt,   0,  0},
         {0,    0,  0,  state_v_sdev*state_v_sdev*dt,           0},
         {0,    0,  0,  0,  state_omega_sdev*state_omega_sdev*dt}}};

static const mf16 W = {3, 3, 0,
        {{enc_sdev*enc_sdev*dt,             0,  0},
         {0,    enc_ang_sdev*enc_ang_sdev*dt,   0},
         {0,    0,  gyro_sdev*gyro_sdev}}};

static const mf16 X0 = {5, 1, 0,
        {{0.0f},
         {0.0f},
         {0.0f},
         {0},
         {0}}};

static const mf16 P0 = {5, 5, 0,
        {{1,    0,  0,  0,  0},
         {0,    1,  0,  0,  0},
         {0,    0,  1,  0,  0},
         {0,    0,  0,  5,  0},
         {0,    0,  0,  0,  5}}};

/**
 * Position estimation task handler.
 *
 * @param params        Task parameters - unused.
 */
static void position_task(void *params);

/**
 * Matrix A linearization.
 *
 * @param[out] A            Linearized A matrix.
 * @param[in] state         State vector.
 */
static void linearization(mf16 *A, mf16 *state);

/**
 * Invert matrix.
 *
 * @param[out] out          Inverted matrix.
 * @param[in] in            Matrix to invert
 */
static void invert(mf16 *out, mf16 *in);

/**
 * Create identity matrix.
 *
 * @param[out] matrix       Identity matrix.
 * @param size              Matrix size.
 */
static void eye(mf16 *matrix, int_fast8_t size);

/**
 * Matrix multiplication A*B*A'.
 *
 * @param[out] result       Result.
 * @param[in] a             Matrix A.
 * @param[in] b             Matrix B.
 */
static void mul_abat(mf16 *result, mf16 *a, mf16* b);

/**
 * Calculate state vector in next step.
 *
 * @param[out] after        State vector after calculation.
 * @param[in] before        State vector before calculation.
 */
static void state_step(mf16 *after, mf16 *before);

/**
 * Prepare measurement vector.
 *
 * @param[out] y            Measurement vector Y.
 */
static void collect_measrements(mf16 *y);

void position_task_init(void)
{
    rtos_task_create(position_task, "position", POSITION_STACKSIZE, POSITION_PRIORITY);
}

float position_x_get(void)
{
    return state.x;
}

float position_y_get(void)
{
    return state.y;
}

float position_alpha_get(void)
{
    return state.alpha;
}

float position_v_get(void)
{
    return state.v;
}

float position_omega_get(void)
{
    return state.omega;
}

static void position_task(void *params)
{
    (void) params;

    tick_t ticks, ticks2;

    mf16 Xpri, Xpost;
    mf16 Ppri, Ppost;
    mf16 A;
    mf16 e, Y;
    mf16 S, K;
    mf16 eye5, e5KC;
    mf16 tmp, tmp2;

    eye(&eye5, 5);
    Xpri = X0;
    Xpost = X0;
    Ppri = P0;
    Ppost = P0;

    while (1)
    {
        ticks = rtos_tick_count_get();

        /* xpri = f[xpost] */
        state_step(&Xpri, &Xpost);

        /* linearize A */
        linearization(&A, &Xpost);

        /* Ppri = A*Ppost*A' + V */
        mul_abat(&tmp, &A, &Ppost);
        mf16_add(&Ppri, &tmp, &V);

        /* Y - collect measurements */
        collect_measrements(&Y);

        /* e = Y - C*xpri */
        mf16_mul(&tmp, &C, &Xpri);
        mf16_sub(&e, &Y, &tmp);

        /* S = C*Ppri*C' + W */
        mul_abat(&tmp, &C, &Ppri);
        mf16_add(&S, &tmp, &W);

        /* K = Ppri*C'*S^-1 */
        mf16_mul_bt(&tmp, &Ppri, &C);
        invert(&tmp2, &S);
        mf16_mul(&K, &tmp, &tmp2);

        /* xpost = xpri + K*e */
        mf16_mul(&tmp, &K, &e);
        mf16_add(&Xpost, &Xpri, &tmp);

        /* e5KC = (eye5 - K*C) */
        mf16_mul(&tmp, &K, &C);
        mf16_sub(&e5KC, &eye5, &tmp);

        /* Ppost = e5KC*Ppri*e5KC' + K*W*K' */
        mul_abat(&tmp, &e5KC, &Ppri);
        mul_abat(&tmp2, &K, &W);
        mf16_add(&Ppost, &tmp, &tmp2);

        state.x = state_get_x(&Xpost);
        state.y = state_get_y(&Xpost);
        state.alpha = state_get_alpha(&Xpost);
        state.v = state_get_v(&Xpost);
        state.omega = state_get_omega(&Xpost);

        ticks2 = rtos_tick_count_get();

        rtos_delay_until(&ticks, 10);
    }
}

static void linearization(mf16 *A, mf16 *state)
{
    float alpha_rad;

    alpha_rad = deg2rad(state_get_alpha(state));

    eye(A, 5);

    A->data[0][3] = dt * fix16_cos(alpha_rad);
    A->data[1][3] = dt * fix16_sin(alpha_rad);
    A->data[2][4] = dt;
}

static void invert(mf16 *out, mf16 *in)
{
    mf16 q, r;
    mf16 eye_m;

    out->columns = in->columns;
    out->rows = in->rows;
    out->errors = 0;

    eye(&eye_m, in->columns);

    mf16_qr_decomposition(&q, &r, in, 1);
    mf16_solve(out, &q, &r, &eye_m);
}

static void eye(mf16 *matrix, int_fast8_t size)
{
    int32_t i;

    matrix->columns = size;
    matrix->rows = size;
    matrix->errors = 0;

    mf16_fill(matrix, 0);

    for (i = 0; i < size; i++)
    {
        matrix->data[i][i] = 1.0f;
    }

}

static void mul_abat(mf16 *result, mf16 *a, mf16* b)
{
    mf16 tmp1;

    mf16_mul(&tmp1, a, b);
    mf16_mul_bt(result, &tmp1, a);
}

static void state_step(mf16 *after, mf16 *before)
{
    float alpha_rad;

    alpha_rad = deg2rad(state_get_alpha(before));

    state_get_x(after) = state_get_x(before) + dt * state_get_v(before) * fix16_cos(alpha_rad);
    state_get_y(after) = state_get_y(before) + dt * state_get_v(before) * fix16_sin(alpha_rad);
    state_get_alpha(after) = state_get_alpha(before) + dt * state_get_omega(before);
    state_get_v(after) = state_get_v(before);
    state_get_omega(after) = state_get_omega(before);
}

static void collect_measrements(mf16 *y)
{
    float v_left, v_right, omega_gyro;

    y->columns = 1;
    y->rows = 3;
    y->errors = 0;

    v_left = motor_vleft_get();
    v_right = motor_vright_get();
    omega_gyro = -imu_gyro_z_get();

    y->data[0][0] = (v_left + v_right) / 2.0f;
    y->data[1][0] = rad2deg((v_right - v_left) / ROBOT_WIDTH);
    y->data[2][0] = omega_gyro;
}
