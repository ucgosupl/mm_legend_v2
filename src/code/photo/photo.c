/*
 * file:	photo.c
 * author:	GAndaLF
 * brief:	Reading voltage from phototransistors.
 */

#include "platform_specific.h"

#include "adc/adc.h"

#include "photo.h"

void photo_init(void)
{

}

int32_t photo_side_l_get(void)
{
    return adc_val_get(ADC_PHOTO_SIDE_L);
}

int32_t photo_side_r_get(void)
{
    return adc_val_get(ADC_PHOTO_SIDE_R);
}

int32_t photo_diag_l_get(void)
{
    return adc_val_get(ADC_PHOTO_DIAG_L);
}

int32_t photo_diag_r_get(void)
{
    return adc_val_get(ADC_PHOTO_DIAG_R);
}

int32_t photo_front_l_get(void)
{
    return adc_val_get(ADC_PHOTO_FRONT_L);
}

int32_t photo_front_r_get(void)
{
    return adc_val_get(ADC_PHOTO_FRONT_R);
}

