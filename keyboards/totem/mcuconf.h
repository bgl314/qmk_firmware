#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

#undef RP_PWM_USE_TIM1
#define RP_PWM_USE_TIM1 TRUE

#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 FALSE

#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 TRUE
