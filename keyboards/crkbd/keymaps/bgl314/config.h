/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */

#define EE_HANDS

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
//#define MASTER_LEFT
#define TAPPING_TERM 150
#define TAPPING_TOGGLE 2
#define RGBLIGHT_LAYERS
#define RGBLIGHT_SLEEP

#define BONGO_ENABLE
#define BONGO_ENABLE_MINIMAL
//#define BONGO_ENABLE_WPM
//#define MYOLED_ENABLE


// #define MASTER_RIGHT
// #define EE_HANDS

#ifdef RGB_MATRIX_ENABLE
#define RGBLIGHT_SLEEP
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGBLIGHT_LAYERS
#define RGBLIGHT_ANIMATIONS // run RGB animations
#define RGBLIGHT_HUE_STEP 12 // units to step when in/decreasing hue
#define RGBLIGHT_SAT_STEP 25 // units to step when in/decresing saturation
#define RGBLIGHT_VAL_STEP 12 // units to step when in/decreasing value (brightness)
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#define RGB_MATRIX_TYPING_HEATMAP_SLIM
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
