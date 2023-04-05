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

#include QMK_KEYBOARD_H



#include "features/caps_word.h"
#ifdef RGBLIGHT_ENABLE
    #include "color.h"
#endif

#ifdef MYOLED_ENABLE
    #include "oled.h"

#endif

#ifdef BONGO_ENABLE
    #include "bongo.h"
#endif



#define _COLEMAK 0
#define _QWERTY 1
#define _SYMBOLS 2
#define _NUMBERS 3
#define _NAV 4
#define _ADJUST 5


enum td_keycodes {
    SHIFT_CAPS, // Our example key: `lshift` when held, `capslock` when tapped. Add additional keycodes for each tapdance.
    SCLN_ENT // tap ent, hold shift, doubletap semicolon enter
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;
// Create a global instance of the tapdance state type
static td_state_t td_state;

// Function to determine the current tapdance state
td_state_t cur_dance(qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void shift_ent_caps_finished(qk_tap_dance_state_t *state, void *user_data);
void shift_ent_caps_reset(qk_tap_dance_state_t *state, void *user_data);

void shift_ent_sent_finished(qk_tap_dance_state_t *state, void *user_data);
void shift_ent_sent_reset(qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,    TD(SCLN_ENT),  KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  TD(SHIFT_CAPS), KC_Z,  KC_X,  KC_C,  KC_V,    KC_B,                                 KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT,KC_ENT),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                        MT(MOD_LALT,KC_ENT),TT(_NUMBERS),MT(MOD_LGUI,KC_SPC) ,      LT(_NAV,KC_SPC),  MO(_SYMBOLS),MT(MOD_RALT,KC_RGUI)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_SPC,                    _______,  _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_TILD,  KC_GRV, KC_LCBR, KC_LPRN,  KC_LBRC,                            KC_RBRC, KC_RPRN,  KC_RCBR, KC_PIPE,KC_BSLS   , KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO, KC_LT,    KC_NO,    KC_UNDS, KC_MINUS,KC_NO ,                             KC_NO,  KC_PLUS, KC_EQL ,KC_NO,    KC_GT,   _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,_______,  _______,                    KC_NO, _______ ,  _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_NUMBERS] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //   KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC , KC_PSLS,KC_7,    KC_8,    KC_9,    KC_MINUS,                            KC_MINUS, KC_7,    KC_8,    KC_9,    KC_PSLS,   _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  KC_PAST,    KC_4,    KC_5,  KC_6,    KC_PLUS,                            KC_PLUS,    KC_4,    KC_5,  KC_6,    KC_PAST,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,    KC_DOT,   KC_1,  KC_2,   KC_3,   KC_0,                                   KC_0,   KC_1,     KC_2,     KC_3,   KC_DOT, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,    _______, KC_0,                    KC_0, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

   [_NAV] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC   , KC_PGUP, KC_HOME, KC_UP, KC_END,    KC_NO,                              KC_NO,    KC_PSCR,    KC_NO,    KC_NO,  KC_NO,  TT(_QWERTY),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,                            KC_NO,  KC_RSHIFT,KC_RCTL,  KC_INS,  KC_NO,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,    RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V),                         KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,    KC_ENT, _______,                   _______, KC_NO, KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_ADJUST] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO, KC_NO,    KC_NO,    KC_NO,   KC_NO, KC_F11 ,                              KC_F12,  KC_NO,   KC_NO,   KC_NO,   DEBUG,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_NO,   RGB_TOG, RGB_RMOD,RGB_MOD , KC_BRIGHTNESS_UP,KC_BRIGHTNESS_DOWN,             KC_VOLU,   KC_VOLD, KC_MUTE,   KC_MSTP,  KC_MPLY, 	KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      KC_NO,   KC_NO,  KC_NO,                      KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};
layer_state_t layer_state_set_user(layer_state_t state) {
     state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);

    //#ifdef RGBLIGHT_ENABLED
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(2, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(3, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUMBERS));
    rgblight_set_layer_state(5, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(6, layer_state_cmp(state, _ADJUST));
    //#endif
    return state;
}



bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_caps_word(keycode, record)) { return false; }
  // Your macros ...

  return true;
}

//tapdancestuff

// Determine the tapdance state to return
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}




// SHIFT-ENTER-CAPS
// Handle the possible states for each tapdance keycode you define:

void shift_ent_caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            // register_code16(KC_ENT);
            // break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSHIFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_CAPS);
            break;
        default:
            break;
    }
}

void shift_ent_caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
        case TD_SINGLE_HOLD:
        //     unregister_code16(KC_ENT);
        //     break;
        // case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSHIFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_CAPS);
            break;
        default:
            break;
    }
}

// END SHIFT-ENTER-CAPS


// SHIFT-ENTER-SEMICOLON/ENTER
// Handle the possible states for each tapdance keycode you define:

void scln_ent_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_SCLN);
            break;
        case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
            register_code16(KC_SCLN);
            register_code16(KC_ENT);
            break;
        default:
            break;
    }
}

void scln_ent_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_SCLN);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SCLN);
            unregister_code16(KC_ENT);
            break;
        default:
            break;
    }
}
// END SHIFT-ENTER-CAPS

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [SHIFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_ent_caps_finished, shift_ent_caps_reset),
    [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset)
};

#ifdef BONGO_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
   return OLED_ROTATION_0;
  //return OLED_ROTATION_270;
}
bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    if (!oled_task_needs_to_repaint()) {
        return false;
    }
    oled_clear();
    if (clock_set_mode) {
        draw_clock();
        return false;;
    }
    draw_bongo(false);

    return false;
}
#endif


#ifdef MYOLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
   return OLED_ROTATION_0;
  //return OLED_ROTATION_270;
}




void render_layer_symbol(void) {
    bool number = layer_state_is(_NUMBERS) & !layer_state_is(_ADJUST);
    bool symbol = layer_state_is(_SYMBOLS) & !layer_state_is(_ADJUST);
    bool nav = layer_state_is(_NAV);
    bool qwerty= layer_state_is(_QWERTY);
    bool adjust = layer_state_is(_ADJUST);

    if(number){
        //oled_write_P(PSTR("12345"), false);
        oled_write_raw_P(bitmapsflower, sizeof(bitmapsflower));
    } else if(symbol){
        //oled_write_P(PSTR("!@#$^"), false);
       oled_write_raw_P(bitmapspenta2, sizeof(bitmapspenta2));
    } else if(adjust){
        //oled_write_P(PSTR(" ADJ "), false);
        oled_write_raw_P(bitmapssepta, sizeof(bitmapssepta));
    } else if(nav){
        //oled_write_P(PSTR(" NAV "), false);
        oled_write_raw_P(bitmapspyramid, sizeof(bitmapspyramid));
    } else if(qwerty){
        //oled_write_P(PSTR("QWERTY"), false);
        oled_write_raw_P(bitmapspentagram, sizeof(bitmapspentagram));
    } else {
        //oled_write_P(PSTR("CLMAK"), false);
        oled_write_raw_P(bitmapstriangles, sizeof(bitmapstriangles));
    }

}

void render_layer_name(void) {

    bool number = layer_state_is(_NUMBERS) & !layer_state_is(_ADJUST);
    bool symbol = layer_state_is(_SYMBOLS) & !layer_state_is(_ADJUST);
    bool nav = layer_state_is(_NAV);
    bool qwerty= layer_state_is(_QWERTY);
    bool adjust = layer_state_is(_ADJUST);

    if(number){
        oled_write_P(PSTR("12345"), false);
    } else if(symbol){
        oled_write_P(PSTR("!@#$^"), false);
    } else if(adjust){
        oled_write_P(PSTR(" ADJ "), false);
    } else if(nav){
        oled_write_P(PSTR(" NAV "), false);
    } else if(qwerty){
        oled_write_P(PSTR("QWERTY"), false);
    } else {
        oled_write_P(PSTR("CLMAK"), false);
    }
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_layer_symbol();
        render_layer_name();
    } else {
        render_layer_symbol();
    }

    return false;
}


#endif // OLED_ENABLE

#ifdef RGBLIGHT_ENABLE
// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_RED}
);
const rgblight_segment_t PROGMEM my_default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 12, HSV_WHITE}       // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_PURPLE}       // Light 4 LEDs, starting with LED 12
);
const rgblight_segment_t PROGMEM my_number_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_GREEN}       // Light 4 LEDs, starting with LED 12
);
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 12, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, 12, HSV_MAGENTA}       // Light 4 LEDs, starting with LED 6
);

// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, 12, HSV_BLUE}       // Light 4 LEDs, starting with LED 6
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    my_default_layer,
    my_capslock_layer,
    my_qwerty_layer,    // Overrides caps lock layer
    my_symbol_layer,
    my_number_layer,    // Overrides other layers
    my_nav_layer,     // Overrides other layers
     my_adjust_layer
);


void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
    return state;
}


#endif
