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


#ifdef RGBLIGHT_ENABLE
    #include "color.h"
#endif

#ifdef MYOLED_ENABLE
    #include "oled.h"

#endif

#include "bongo.h"




#define _COLEMAK 0
#define _QWERTY 1
#define _SYMBOLS 2
#define _NUMBERS 3
#define _NAV 4
#define _ADJUST 5


// enum td_keycodes {
//     SHIFT_CAPS, // Our example key: `lshift` when held, `capslock` when tapped. Add additional keycodes for each tapdance.
//     SCLN_ENT // tap ent, hold shift, doubletap semicolon enter
// };

// // Define a type containing as many tapdance states as you need
// typedef enum {
//     TD_NONE,
//     TD_UNKNOWN,
//     TD_SINGLE_TAP,
//     TD_SINGLE_HOLD,
//     TD_DOUBLE_SINGLE_TAP
// } td_state_t;
// // Create a global instance of the tapdance state type
// static td_state_t td_state;

// // Function to determine the current tapdance state
// td_state_t cur_dance(qk_tap_dance_state_t *state);

// // `finished` and `reset` functions for each tapdance keycode
// void shift_ent_caps_finished(qk_tap_dance_state_t *state, void *user_data);
// void shift_ent_caps_reset(qk_tap_dance_state_t *state, void *user_data);

// void shift_ent_sent_finished(qk_tap_dance_state_t *state, void *user_data);
// void shift_ent_sent_reset(qk_tap_dance_state_t *state, void *user_data);

//TD(SHIFT_CAPS)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,  KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
 MT(MOD_LSFT,KC_CAPS), KC_Z,  KC_X,  KC_C,  KC_V,    KC_B,                                 KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT,KC_ENT),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                        MT(MOD_LALT,KC_ENT),TT(_NUMBERS),MT(MOD_LCTL,KC_BSPC) ,      LT(_NAV,KC_SPC),  MO(_SYMBOLS),MT(MOD_RALT,KC_RGUI)
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
     _______, KC_LT,    KC_NO,    KC_UNDS, KC_MINUS,KC_NO ,                             KC_NO,  KC_PLUS, KC_EQL ,KC_NO,    KC_GT,   _______,
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
     KC_DEL,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,                            KC_NO,  KC_RSFT,KC_RCTL,  KC_INS,  KC_NO,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,    RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V),                         KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,    KC_ENT, _______,                   _______, KC_NO, KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_ADJUST] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO, KC_NO,    KC_NO,    KC_NO,   KC_PSCR, KC_F11 ,                              KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   QK_REBOOT,
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

    #ifdef RGBLIGHT_ENABLED
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
    rgblight_set_layer_state(2, layer_state_cmp(state, _QWERTY));
    rgblight_set_layer_state(3, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUMBERS));
    rgblight_set_layer_state(5, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(6, layer_state_cmp(state, _ADJUST));
    #endif
    return state;
}


// //tapdancestuff

// // Determine the tapdance state to return
// td_state_t cur_dance(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
//         else return TD_SINGLE_HOLD;
//     }

//     if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
//     else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
// }




// // SHIFT-ENTER-CAPS
// // Handle the possible states for each tapdance keycode you define:

// void shift_ent_caps_finished(qk_tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP:
//             // register_code16(KC_ENT);
//             // break;
//         case TD_SINGLE_HOLD:
//             register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
//             break;
//         case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
//             register_code16(KC_CAPS);
//             break;
//         default:
//             break;
//     }
// }

// void shift_ent_caps_reset(qk_tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP:
//         case TD_SINGLE_HOLD:
//         //     unregister_code16(KC_ENT);
//         //     break;
//         // case TD_SINGLE_HOLD:
//             unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
//             break;
//         case TD_DOUBLE_SINGLE_TAP:
//             unregister_code16(KC_CAPS);
//             break;
//         default:
//             break;
//     }
// }

// // END SHIFT-ENTER-CAPS


// // SHIFT-ENTER-SEMICOLON/ENTER
// // Handle the possible states for each tapdance keycode you define:

// void scln_ent_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
//     td_state = cur_dance(state);
//     switch (td_state) {
//         case TD_SINGLE_TAP:
//             register_code16(KC_SCLN);
//             break;
//         case TD_DOUBLE_SINGLE_TAP: // Allow nesting of 2 parens `((` within tapping term
//             register_code16(KC_SCLN);
//             register_code16(KC_ENT);
//             break;
//         default:
//             break;
//     }
// }

// void scln_ent_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
//     switch (td_state) {
//         case TD_SINGLE_TAP:
//             unregister_code16(KC_SCLN);
//             break;
//         case TD_DOUBLE_SINGLE_TAP:
//             unregister_code16(KC_SCLN);
//             unregister_code16(KC_ENT);
//             break;
//         default:
//             break;
//     }
// }
// // END SHIFT-ENTER-CAPS

// // Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     [SHIFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_ent_caps_finished, shift_ent_caps_reset),
//     [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset)
// };





#define CUSTOM_OLED_TIMEOUT 10000
void draw_default(void);


 bool oled_repaint_requested=true;
 bool oled_wakeup_requested= true;

uint32_t oled_sleep_timer;



// Request a repaint of the OLED image without resetting the OLED sleep timer.
// Used for things like clock updates that should not keep the OLED turned on
// if there is no other activity.
void oled_request_repaint(void) {
    if (is_oled_on()) {
        oled_repaint_requested = true;
    }
}

// Request a repaint of the OLED image and reset the OLED sleep timer.
// Needs to be called after any activity that should keep the OLED turned on.
void oled_request_wakeup(void) {
    oled_wakeup_requested = true;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    oled_request_wakeup();
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

        oled_request_wakeup();

    return true;
}


// Check whether oled_task_user() needs to repaint the OLED image.  This
// function should be called at the start of oled_task_user(); it also handles
// the OLED sleep timer and the OLED_OFF mode.
bool oled_task_needs_to_repaint(void) {


    // If OLED wakeup was requested, reset the sleep timer and do a repaint.
    if (oled_wakeup_requested) {
        oled_wakeup_requested = false;
        oled_repaint_requested = false;
        oled_sleep_timer = timer_read32() + CUSTOM_OLED_TIMEOUT;
        oled_on();
        return true;
    }

    // If OLED repaint was requested, just do a repaint without touching the
    // sleep timer.
    if (oled_repaint_requested) {
        oled_repaint_requested = false;
        return true;
    }

    // If the OLED is currently off, skip the repaint (which would turn the
    // OLED on if the image is changed in any way).
    if (!is_oled_on()) {
        return false;
    }

    // If the sleep timer has expired while the OLED was on, turn the OLED off.
    if (timer_expired32(timer_read32(), oled_sleep_timer)) {
        oled_off();
        return false;
    }

    // Always perform a repaint if the OLED is currently on.  (This can
    // potentially be optimized to avoid unneeded repaints if all possible
    // state changes are covered by oled_request_repaint() or
    // oled_request_wakeup(), but then any missed calls to these functions
    // would result in displaying a stale image.)
    return true;
}

void render_layer_name(void) {

    bool number = layer_state_is(_NUMBERS) & !layer_state_is(_ADJUST);
    bool symbol = layer_state_is(_SYMBOLS) & !layer_state_is(_ADJUST);
    bool nav = layer_state_is(_NAV);
    bool qwerty= layer_state_is(_QWERTY);
    bool adjust = layer_state_is(_ADJUST);
    oled_set_cursor(0, 0);
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
        oled_write_P(PSTR("COLMAK"), false);
    }
}

//char wpm[42];

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}


bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }

    if (!oled_task_needs_to_repaint()) {
            return false;
    }
    if (is_keyboard_master()) {
        draw_bongo();
        render_layer_name();
    }else{
    }

    return false;
}



#ifdef MYOLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
   return OLED_ROTATION_0;
  //return OLED_ROTATION_270;
}


void render_layer_name(void) {

    bool number = layer_state_is(_NUMBERS) & !layer_state_is(_ADJUST);
    bool symbol = layer_state_is(_SYMBOLS) & !layer_state_is(_ADJUST);
    bool nav = layer_state_is(_NAV);
    bool qwerty= layer_state_is(_QWERTY);
    bool adjust = layer_state_is(_ADJUST);
 oled_set_cursor(0, 0);
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
        oled_write_P(PSTR("COLEMAK"), false);
    }
}


void render_layer_symbol(int wpmval) {


    if(wpmval < 10){
        //oled_write_P(PSTR("12345"), false);
        oled_write_raw_P(bitmapsflower, sizeof(bitmapsflower));
    } else if(wpmval < 30){
         oled_write_raw_P(bitmapspyramid, sizeof(bitmapspyramid));
    } else if(wpmval < 60){
       oled_write_raw_P(bitmapstriangles, sizeof(bitmapstriangles));
    }

}


// void render_layer_symbol(int wpmval) {
//     bool number = layer_state_is(_NUMBERS) & !layer_state_is(_ADJUST);
//     bool symbol = layer_state_is(_SYMBOLS) & !layer_state_is(_ADJUST);
//     bool nav = layer_state_is(_NAV);
//     bool qwerty= layer_state_is(_QWERTY);
//     bool adjust = layer_state_is(_ADJUST);

//     if(number){
//         //oled_write_P(PSTR("12345"), false);
//         oled_write_raw_P(bitmapsflower, sizeof(bitmapsflower));
//     } else if(symbol){
//         //oled_write_P(PSTR("!@#$^"), false);
//        oled_write_raw_P(bitmapspenta2, sizeof(bitmapspenta2));
//     } else if(adjust){
//         //oled_write_P(PSTR(" ADJ "), false);
//         oled_write_raw_P(bitmapssepta, sizeof(bitmapssepta));
//     } else if(nav){
//         //oled_write_P(PSTR(" NAV "), false);
//         oled_write_raw_P(bitmapspyramid, sizeof(bitmapspyramid));
//     } else if(qwerty){
//         //oled_write_P(PSTR("QWERTY"), false);
//         oled_write_raw_P(bitmapspentagram, sizeof(bitmapspentagram));
//     } else {
//         //oled_write_P(PSTR("CLMAK"), false);
//         oled_write_raw_P(bitmapstriangles, sizeof(bitmapstriangles));
//     }

// }


char wpm[42];
bool oled_task_user(void) {
    int wpmval=get_current_wpm();
    if (is_keyboard_master()) {

        render_layer_symbol(wpmval);
        render_layer_name();
        oled_set_cursor(0, 1);
        sprintf(wpm, "WPM:%03d", wpmval);

        oled_write(wpm, false);
    } else {
        render_layer_symbol(wpmval);
    }

    return false;
}



#endif // OLED_ENABLE

#ifdef RGB_MATRIX_ENABLE


bool caps = false;

void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        caps = true;
    } else {
        caps = false;
    }
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
}

RGB rgbDEF = {-1,-1,-1};
RGB rgbOFF ={RGB_OFF};
RGB rgbRED ={RGB_RED};
RGB rgbMAGENTA ={RGB_MAGENTA};


RGB rgbP1 = {RGB_CYAN};//{186,89,100};
RGB rgbP2 = {RGB_PURPLE};//{130,53,92};
RGB rgbP3 = {RGB_BLUE};//{67, 90, 100};
RGB rgbP4 = {RGB_GREEN};//{42,91,91};
RGB rgbP5 = {RGB_MAGENTA};//{17,92,100};



void set_rgb(uint8_t index, RGB rgb){
    #if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
        rgb_matrix_set_color(index, rgb.g, rgb.r, rgb.b);
    #elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
       rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
    #elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
       rgb_matrix_set_color(index, rgb.b, rgb.g, rgb.r);
    #endif
}

uint8_t mSize = MATRIX_ROWS * MATRIX_COLS + 12;


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    //rgb_matrix_enable_noeeprom();
    uint8_t layer = get_highest_layer(layer_state);
    for(uint8_t index = 0; index < led_max ; ++index )
    {
        //if( HAS_FLAGS(g_led_config.flags[index],LED_FLAG_UNDERGLOW ))  {
        if( g_led_config.flags[index]==LED_FLAG_UNDERGLOW )  {
            RGB rgb = rgbDEF;
            switch(layer){
                case _QWERTY:
                    if(caps)
                        rgb = rgbRED;
                    else
                        rgb = rgbP2;
                    break;
                case _COLEMAK:
                    if(caps)
                        rgb = rgbRED;
                    break;
                case _ADJUST:
                    rgb = rgbP1;
                    break;
                case _NAV:
                    rgb = rgbP5;
                    break;
                case _SYMBOLS:
                    rgb = rgbP3;
                    break;
                case _NUMBERS:
                    rgb = rgbP4;
                    break;
                default:
                    break;
            }
            //#ifdef CONSOLE_ENABLE
            //    uprintf("index %u layer %u r %u g %u b %u\n",index, layer, rgb.r, rgb.g, rgb.b);
            //#endif

            if(!(rgb.r  == rgbDEF.r && rgb.g==rgbDEF.g && rgb.b==rgbDEF.b)){
                set_rgb(index, rgb);
            }else{
                rgb_matrix_set_color(index, rgbOFF.r, rgbOFF.g, rgbOFF.b);
            }

        }

    }
    return true;
}
#endif

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
