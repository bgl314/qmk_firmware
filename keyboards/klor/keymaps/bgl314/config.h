#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define MASTER_LEFT
// #define MASTER_RIGHT


//#define TAPPING_TERM 170
#define TAPPING_TERM 170

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

#define TAPPING_TOGGLE 2

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

// Auto Shift
//#define NO_AUTO_SHIFT_ALPHA
//#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
//#define AUTO_SHIFT_NO_SETUP

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
//#define NO_ACTION_TAPPING
//#define NO_MUSIC_MODE



#define COMBO_COUNT 1

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD


#ifdef POINTING_DEVICE_ENABLE
//#    define POINTING_DEVICE_ROTATION_90
#    define SPLIT_POINTING_ENABLE
#    define POINTING_DEVICE_RIGHT
#    define POINTING_DEVICE_ROTATION_270
#endif

// RGB matrix support
#ifdef RGB_MATRIX_ENABLE

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP

#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#define RGB_MATRIX_TYPING_HEATMAP_SLIM
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_HEATMAP

#endif


