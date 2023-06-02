#pragma once
// disable this define to build, or make your own qmk-config/passwords.h
#define HAS_PASSWORDS

#include "../qmk-config/common_config.h"

#define BILATERAL_COMBINATIONS 250
#define BILATERAL_COMBINATIONS_EXCEPTION_ROW 3

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE


#ifdef POINTING_DEVICE_ENABLE
//#    define POINTING_DEVICE_ROTATION_90
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 300
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT

#define POINTING_DEVICE_TASK_THROTTLE_MS 10


// Configure for the Cirque model used on the Dilemma.
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define CIRQUE_PINNACLE_CURVED_OVERLAY
//#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll.
#endif
