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

//#define EE_HANDS

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define MASTER_LEFT

#define TAPPING_TERM 170

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TOGGLE 2

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
//#define SPLIT_MODS_ENABLE
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_OLED_ENABLE



#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
#define RGB_MATRIX_TYPING_HEATMAP_SLIM
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
