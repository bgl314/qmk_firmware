#pragma once
#define HAS_PASSWORDS
// get my qmk-config folder and put it in the same directory as qmk_firmware
#include "../qmk-config/common_config.h"
/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/
//#define EE_HANDS
#define MASTER_LEFT
//#define MASTER_RIGHT


#ifdef HAPTIC_ENABLE
#define SPLIT_HAPTIC_ENABLE
#define DRV2605L_GREETING 120
#endif


#ifdef POINTING_DEVICE_ENABLE
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_TIME 200
#define SPLIT_POINTING_ENABLE
// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT

// Limits the frequency that the sensor is polled for motion.
#define POINTING_DEVICE_TASK_THROTTLE_MS 10

// Adjust trackpad rotation.
#define POINTING_DEVICE_ROTATION_270

// Configure for the Cirque model used on the Dilemma.
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define CIRQUE_PINNACLE_CURVED_OVERLAY
//#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_RELATIVE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE
#define CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll.
#endif

// RGB matrix support
#ifdef RGB_MATRIX_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_SPLASH
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 30
#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 15
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 30

#define RGB_MATRIX_DEFAULT_HUE 127
#define RGB_MATRIX_DEFAULT_SAT 127
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS


//#define RGB_MATRIX_TYPING_HEATMAP_SLIM
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_HEATMAP



#endif

#define BILATERAL_COMBINATIONS 250
#define BILATERAL_COMBINATIONS_EXCEPTION_ROW 3
