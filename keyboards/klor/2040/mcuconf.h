#pragma once

#include_next <mcuconf.h>



//#undef RP_I2C_USE_I2C1
//#define RP_I2C_USE_I2C1 TRUE

// #ifdef BLOK_MCU
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE
// #endif

#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

#undef RP_PWM_USE_TIM1
#define RP_PWM_USE_TIM1 TRUE
