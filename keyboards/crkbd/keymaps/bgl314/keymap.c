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

#ifdef OLED_ENABLE
#include "bongo.h"
#endif

#define _COLEMAK 0
#define _QWERTY 1
#define _REAPER 2
#define _SYMBOLS 3
#define _NUMBERS 4
#define _NAV 5
#define _ADJUST 6



#define SHT_O MT(MOD_RSFT, KC_O)
#define SHT_GRV MT(MOD_LSFT, KC_GRV)
#define SHT_A MT(MOD_LSFT, KC_A)
#define SHT_B MT(MOD_LSFT, KC_B)
#define ALT_D MT(MOD_LALT, KC_D)
#define ALT_H MT(MOD_RALT, KC_H)
#define CTL_N MT(MOD_RCTL, KC_N)
#define CTRL_T MT(MOD_LCTL, KC_T)
#define CTL_MPLY MT(MOD_RCTL, KC_MPLY)
#define SHT_MNXT MT(MOD_RSFT, KC_MNXT)

enum td_keycodes {
    DOT_ENT,
    Q_ESC,
    Z_ENT,
    D_DELETE,
    P_SPACE,
    S_ALT_S,
    T_TAKE,
    SLASH_ENT,
    DBL_PAREN,
    DBL_BRACKET,
    DBL_BRACE,
    DBL_GT,
    SCLN_ENT // tap ent, hold shift, doubletap semicolon enter
};

// Define a type containing as many tapdance states as you need


//TD(SHIFT_CAPS)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO, TD(Q_ESC),    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   SHT_A,    KC_R,    KC_S,    CTRL_T,    ALT_D,                              ALT_H,    CTL_N,    KC_E,    KC_I,  SHT_O,    KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO, TD(Z_ENT),KC_X,   KC_C,    KC_V,    KC_B,                       KC_K, KC_M,    KC_COMM, KC_DOT, TD(SLASH_ENT), TD(SCLN_ENT),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                MT(MOD_LALT,KC_LGUI),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC) , LT(_NAV,KC_SPC),  MO(_SYMBOLS),MT(MOD_RALT,KC_RGUI)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT(KC_ENT),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LALT, _______, KC_LCTL,                    _______,  _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
   [_REAPER] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______,  _______, _______, TD(P_SPACE), _______,                            _______, _______, _______, _______, _______,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,  _______, TD(S_ALT_S), TD(T_TAKE), TD(D_DELETE),                            _______, _______, _______, _______, _______,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,  _______, _______, _______, _______,                           _______, _______,  _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     _______,_______,_______ ,                    _______,  _______,_______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO, SHT_GRV,TD(DBL_BRACKET),TD(DBL_BRACE), TD(DBL_PAREN), TD(DBL_GT),          KC_GT,  KC_RPRN,  KC_RCBR,KC_RBRC, TD(SCLN_ENT) , KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO, KC_TILDE,  KC_PIPE  , KC_UNDS, KC_MINUS,KC_BSLS ,                          KC_NO,  KC_PLUS, KC_EQL ,RSFT(KC_SCLN), KC_SLSH, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,_______,  _______,                    _______, _______ ,  _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_NUMBERS] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //   KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO , KC_PSLS,KC_7,    KC_8,    KC_9,    KC_MINUS,                            KC_MINUS, KC_7,    KC_8,    KC_9,    KC_PSLS,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,  KC_PAST,    KC_4,    KC_5,  KC_6,    KC_PLUS,                            KC_PLUS,    KC_4,    KC_5,  KC_6,    KC_PAST,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO, TD(DOT_ENT), KC_1,  KC_2,   KC_3,   KC_SPC,                               KC_EQL,   KC_1,     KC_2,     KC_3,   TD(DOT_ENT), KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_0,    _______, _______,                    KC_0, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

   [_NAV] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______   , KC_PGUP, KC_HOME, KC_UP, KC_END,    KC_NO,                              KC_NO,    KC_PSCR,    KC_NO,    KC_NO,  KC_NO,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,                            KC_RALT,  KC_RCTL, KC_RSFT,  KC_INS,  KC_RSFT,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,    RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V),KC_DEL,                     KC_NO,  KC_NO,    KC_NO,    KC_NO,  _______,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,  _______, _______,                   _______, KC_NO, KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_ADJUST] = LAYOUT_split_3x6_3(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼──────
      KC_NO,  KC_F9, KC_F10,    KC_F11,   KC_F12, KC_NO ,                             RGB_TOG,  KC_BRIGHTNESS_UP,   KC_BRIGHTNESS_DOWN,   TG(_REAPER), TG(_QWERTY),   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO,  KC_F5, KC_F6,    KC_F7,   KC_F8,  KC_NO,                               KC_RALT,  CTL_MPLY, KC_MSTP, KC_MPRV,  SHT_MNXT,KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,                             KC_NO,KC_VOLU, KC_VOLD, KC_MUTE,   KC_CAPS, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______,   _______,  _______,                      _______,   _______,   _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SHT_O:
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
    }
}


layer_state_t layer_state_set_user(layer_state_t state) {
     state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
    return state;
}


// SHIFT-ENTER-SEMICOLON/ENTER
// Handle the possible states for each tapdance keycode you define:
void scln_ent_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        register_code16(KC_SCLN);

     }else {
        register_code16(KC_SCLN);
        register_code16(KC_ENT);
     }

}

void scln_ent_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
         unregister_code16(KC_SCLN);

     }else {
            unregister_code16(KC_SCLN);
             unregister_code16(KC_ENT);
     }

}
// END SHIFT-ENTER-CAPS
void dbl_paren_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        register_code16(KC_LPRN);
     }else {
        register_code16(KC_LPRN);
        register_code16(KC_RPRN);
        register_code16(KC_LEFT);
     }
}

void dbl_paren_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        unregister_code16(KC_LPRN);
     }else {
        unregister_code16(KC_LPRN);
        unregister_code16(KC_RPRN);
        unregister_code16(KC_LEFT);
     }
}

void dbl_brace_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        register_code16(KC_LCBR);
     }else {
        register_code16(KC_LCBR);
        register_code16(KC_RCBR);
        register_code16(KC_LEFT);
     }
}

void dbl_brace_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        unregister_code16(KC_LCBR);
     }else {
        unregister_code16(KC_LCBR);
        unregister_code16(KC_RCBR);
        unregister_code16(KC_LEFT);
     }
}


void dbl_bracket_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        register_code16(KC_LBRC);
     }else {
        register_code16(KC_LBRC);
        register_code16(KC_RBRC);
        register_code16(KC_LEFT);
     }
}

void dbl_bracket_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        unregister_code16(KC_LBRC);
     }else {
        unregister_code16(KC_LBRC);
        unregister_code16(KC_RBRC);
        unregister_code16(KC_LEFT);
     }
}

void dbl_gt_sent_finished(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        register_code16(KC_LT);
     }else {
        register_code16(KC_LT);
        register_code16(KC_GT);
        register_code16(KC_LEFT);
     }
}

void dbl_gt_sent_reset(qk_tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        unregister_code16(KC_LT);
     }else {
        unregister_code16(KC_LT);
        unregister_code16(KC_GT);
        unregister_code16(KC_LEFT);
     }
}
// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [Q_ESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC),
     [DOT_ENT]= ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),
    [SLASH_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_ENT),
     [Z_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_ENT),
    [D_DELETE] = ACTION_TAP_DANCE_DOUBLE(KC_D, KC_DEL),
    [P_SPACE] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_SPACE),
    [S_ALT_S] = ACTION_TAP_DANCE_DOUBLE(KC_S, LALT(KC_S)),
    [T_TAKE] = ACTION_TAP_DANCE_DOUBLE(KC_T, LALT(LSFT(KC_T))),
    [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset),
    [DBL_PAREN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dbl_paren_sent_finished, dbl_paren_sent_reset),
    [DBL_BRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dbl_bracket_sent_finished, dbl_bracket_sent_reset),
    [DBL_BRACE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dbl_brace_sent_finished, dbl_brace_sent_reset),
    [DBL_GT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dbl_gt_sent_finished, dbl_gt_sent_reset)
};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;
        case TD(Q_ESC):
        case TD(Z_ENT):
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}


#ifdef OLED_ENABLE
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
    led_t led_state = host_keyboard_led_state();
    bool number = layer_state_is(_NUMBERS) & !layer_state_is(_ADJUST);
    bool symbol = layer_state_is(_SYMBOLS) & !layer_state_is(_ADJUST);
    bool nav = layer_state_is(_NAV);
    bool qwerty= layer_state_is(_QWERTY);
    bool reaper= layer_state_is(_REAPER);
    bool adjust = layer_state_is(_ADJUST);
    oled_set_cursor(0, 0);
    if(number){
        oled_write_P(PSTR("12345"), led_state.caps_lock );
    } else if(symbol){
        oled_write_P(PSTR("!@#$^"), led_state.caps_lock);
    } else if(adjust){
        oled_write_P(PSTR(" ADJ "), led_state.caps_lock);
    } else if(nav){
        oled_write_P(PSTR(" NAV "), led_state.caps_lock);
    } else if(qwerty){
        oled_write_P(PSTR("QWERTY"), led_state.caps_lock);
    } else if(reaper){
        oled_write_P(PSTR("REAPER"), led_state.caps_lock);
    } else {
        oled_write_P(PSTR("COLMAK"), led_state.caps_lock);
    }

    oled_set_cursor(0, 1);
    uint8_t mod_state = get_mods();
    if(mod_state & MOD_MASK_SHIFT)
        oled_write("shift", false);

    oled_set_cursor(0, 2);
    if(mod_state & MOD_MASK_CTRL)
        oled_write("ctrl", false);

    oled_set_cursor(0, 3);
    if(mod_state & MOD_MASK_ALT)
        oled_write("alt", false);
    else{
        // // tapping term
        // char snum[5];
        // itoa(TAPPING_TERM , snum,10);
        // oled_write(snum, false);
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

#endif



#ifdef RGB_MATRIX_ENABLE


bool caps = false;
enum rgb_matrix_effects priormode= RGB_MATRIX_TYPING_HEATMAP;

// void led_set_kb(uint8_t usb_led) {
//     if(usb_led & (1<<USB_LED_CAPS_LOCK)){
//         priormode=rgb_matrix_get_mode();
//         rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR );
//     }else{
//         rgb_matrix_mode_noeeprom(priormode);
//     }
//     caps=usb_led & (1<<USB_LED_CAPS_LOCK);
// }

void keyboard_post_init_user(void) {
    priormode=RGB_MATRIX_TYPING_HEATMAP;
    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
}


void caps_word_set_user(bool active) {
    if(active){
        priormode=rgb_matrix_get_mode();
        // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR );
    }else if(!caps){
        // rgb_matrix_mode_noeeprom(priormode);
    }
}

bool led_update_user(led_t led_state) {
    if(led_state.caps_lock){
        priormode=rgb_matrix_get_mode();
        // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR );

    }else if(!is_caps_word_on()){
        // rgb_matrix_mode_noeeprom(priormode);
    }
    caps=led_state.caps_lock;
    return true;
}
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_caps_word_on() || caps) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (!(g_led_config.flags[i] & LED_FLAG_KEYLIGHT) && g_led_config.flags[i]!=LED_FLAG_UNDERGLOW) {
                rgb_matrix_set_color(i, RGB_MAGENTA);
            }else{
                // rgb_matrix_set_color(i, 0,0,0);
            }
        }
    }
    return true;
}

#endif

