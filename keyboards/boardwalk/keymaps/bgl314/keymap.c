/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "color.h"


// Layer shorthand
enum layer_names {
    _COLEMAK,
    _QWERTY,
      _REAPER,
    _SYMBOLS,
     _NUMBERS,
      _NAV,
      _ADJUST
};

#define SHT_O MT(MOD_RSFT, KC_O)
#define SHT_GRV MT(MOD_LSFT, KC_GRV)
#define SHT_BSLS MT(MOD_RSFT, KC_BSLS)
#define SHT_A MT(MOD_LSFT, KC_A)
#define SHT_B MT(MOD_LSFT, KC_B)
#define SHT_A MT(MOD_LSFT, KC_A)
#define ALT_D MT(MOD_LALT, KC_D)
#define ALT_H MT(MOD_RALT, KC_H)
#define CTL_N MT(MOD_RCTL, KC_N)
#define CTRL_T MT(MOD_LCTL, KC_T)
#define CTL_MPLY MT(MOD_RCTL, KC_MPLY)
#define SHT_MNXT MT(MOD_RSFT, KC_MNXT)

enum td_keycodes {
    DOT_ENT,
    Q_ESC,
    D_DELETE,
    P_SPACE,
    S_ALT_S,
    T_TAKE,
    SLASH_ENT,
    Z_ENT,
    SCLN_ENT // tap ent, hold shift, doubletap semicolon enter
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | '      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | CAP LK | A      | S      | D      | F      | G      | HOME   | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LSHIFT | Z      | X      | C      | V      | B      | END    | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * | LCTRL  | LGUI   | FN     | LALT   | RAISE  |      SPACE      |      SPACE      | LEFT   | DOWN   | UP     | RIGHT  | RCTRL  |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_COLEMAK] = LAYOUT_ortho_2x2u(
       KC_NO,             KC_1,    KC_2,     KC_3,    KC_4,    KC_5,   KC_NO,  KC_NO,      KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_NO,
        KC_NO,  TD(Q_ESC),    KC_W,     KC_F,    KC_P,    KC_G,   KC_NO,  KC_NO,      KC_J,   KC_L,    KC_U,    KC_Y,  KC_QUOT  , KC_NO,
        KC_NO,   SHT_A,    KC_R,    KC_S,    CTRL_T,    ALT_D,    KC_NO  ,  KC_NO,      ALT_H,    CTL_N,    KC_E,    KC_I,    SHT_O,    KC_NO,
       KC_NO,   TD(Z_ENT),    KC_X,   KC_C,    KC_V,    SHT_B,   KC_NO, KC_NO,     KC_K,     KC_M,    KC_COMM, KC_DOT, TD(SLASH_ENT), KC_NO,
      KC_NO,KC_NO,  KC_NO,MT(MOD_LALT,KC_ESC),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC), LT(_NAV,KC_SPC),MO(_SYMBOLS),MT(MOD_RALT,KC_RGUI),KC_NO, KC_NO,  KC_NO

    ),
    /* Function Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | DEL    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        | MENU   |        |        |        |        |        |        |        |        |        | PRT SC |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        | RESET  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |                 |                 |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_ortho_2x2u(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  _______, _______,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  _______, _______,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  _______, _______,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENTER,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  _______, _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, _______, _______, KC_LALT, TT(_NUMBERS), KC_SPC,                 KC_SPC, _______,   KC_RALT, _______,_______, _______
    ),

    /* Raise Layer
     * .-----------------------------------------------------------------------------------------------------------------------------.
     * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | DEL    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * |        |        | MENU   |        |        |        |        |        |        |        |        |        | PRT SC |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        | RESET  |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
     * |        |        |        |        |        |                 |                 |        |        |        |        |        |
     * '-----------------------------------------------------------------------------------------------------------------------------'
     */
    [_SYMBOLS] = LAYOUT_ortho_2x2u(
        _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
        _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO, KC_NO,KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  _______,
         KC_NO,  SHT_GRV,  KC_LBRC, KC_LCBR, KC_LPRN,    KC_LT,   KC_NO, KC_NO,KC_GT,  KC_RPRN,  KC_RCBR,KC_RBRC, TD(SCLN_ENT) , KC_NO,
        KC_NO, KC_TILDE,  KC_PIPE  , KC_UNDS, KC_MINUS,KC_BSLS ,  _______, _______, KC_NO, KC_PLUS, KC_EQL ,RSFT(KC_SCLN), KC_SLSH,KC_NO,
        _______, _______, _______, _______, _______,     _______,          KC_NO,     _______, _______, _______, _______, _______
    ),
    [_NUMBERS] = LAYOUT_ortho_2x2u(
        KC_NO, KC_F1,  KC_F2,  KC_F3,  KC_F4,   KC_F5,   KC_F11,   KC_F12,     KC_F6,   KC_F7, KC_F8,  KC_F9,   KC_F10,  KC_NO,
        KC_NO, KC_PSLS,  KC_7,   KC_8,   KC_9,    KC_MINS,   KC_NO,    KC_NO,      KC_MINS,   KC_7,  KC_8,   KC_9,    KC_PSLS,   KC_NO,
        KC_NO, KC_PAST,KC_4,   KC_5,   KC_6,    KC_PLUS, KC_NO,    KC_NO,    KC_PLUS, KC_4,  KC_5,   KC_6,    KC_PAST, KC_NO,
        KC_NO, TD(DOT_ENT),  KC_1,   KC_2,   KC_3,    KC_DEL, KC_NO,    KC_NO,    KC_EQL, KC_1,  KC_2,   KC_3,    TD(DOT_ENT), KC_NO,
        KC_NO,    KC_NO,   KC_NO, KC_0,  _______, _______,   KC_0,     _______,    _______, KC_NO, KC_NO, KC_NO
    )
,
    [_NAV] = LAYOUT_ortho_2x2u(
        KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,       KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,
       KC_NO   , KC_PGUP, KC_HOME, KC_UP, KC_END,    KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_PSCR,    KC_NO,    KC_NO,  KC_NO,  _______,
       KC_NO,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_DEL,   KC_NO,  KC_NO,  KC_RALT,  KC_RCTL, KC_RSFT,  KC_INS,  KC_RSFT,  KC_NO,
      KC_NO,    RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V),  KC_DEL,   _______,            KC_NO, KC_NO,  KC_NO,    KC_NO,    KC_NO,  _______,  _______,
        KC_NO, KC_NO, KC_NO, _______,    _______, _______,            _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
    ),
     [_ADJUST] = LAYOUT_ortho_2x2u(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO,  KC_F9, KC_F10,    KC_F11,   KC_F12, KC_NO ,  KC_NO, KC_NO,              RGB_TOG,  KC_BRIGHTNESS_UP,   KC_BRIGHTNESS_DOWN,   TG(_REAPER), TG(_QWERTY),   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	    KC_NO,  KC_F5, KC_F6,    KC_F7,   KC_F8,  KC_NO,     KC_NO, KC_NO,             KC_RALT,  CTL_MPLY, KC_MSTP, KC_MPRV,  SHT_MNXT,KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,   KC_NO,             KC_NO,    KC_NO,KC_VOLU, KC_VOLD, KC_MUTE,   KC_CAPS, KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
        KC_NO, KC_NO,  KC_NO,          _______,   _______,  _______,                       _______,   _______,  _______,  KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),
     [_REAPER] = LAYOUT_ortho_2x2u(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   _______, _______,  _______, _______, TD(P_SPACE), _______, KC_NO ,  KC_NO, _______, _______, _______, _______, _______,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   _______, _______,  _______, TD(S_ALT_S), TD(T_TAKE), TD(D_DELETE),     KC_NO, KC_NO,     _______,        _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______,_______, _______, _______ , _______,_______,_______,    _______, _______, _______,  _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
        KC_NO, KC_NO,  KC_NO,                              _______,   _______,  _______,                      _______,   _______,   _______,  KC_NO,   KC_NO,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
          case SHT_O:
         case SHT_A:
         case SHT_B:
         case ALT_D:
         case ALT_H:
         case CTL_N:
         case CTRL_T:
            return 50;
        default:
            return TAPPING_TERM;
    }
}

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED},
    {6, 2, HSV_RED},

    {13, 1, HSV_RED}          // Light 4 LEDs, starting with LED 12
);
const rgblight_segment_t PROGMEM my_default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 14, HSV_PURPLE  }     // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t PROGMEM my_qwerty_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_WHITE}       // Light 4 LEDs, starting with LED 12
);
const rgblight_segment_t PROGMEM my_number_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_GREEN}       // Light 4 LEDs, starting with LED 12
);
const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_reaper_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM my_nav_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, 14, HSV_MAGENTA}       // Light 4 LEDs, starting with LED 6
);

// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_symbol_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, 14, HSV_BLUE}       // Light 4 LEDs, starting with LED 6
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    my_default_layer,

    my_qwerty_layer,    // Overrides caps lock layer
    my_capslock_layer,
    my_reaper_layer,

    my_symbol_layer,
    my_number_layer,    // Overrides other layers
    my_nav_layer,     // Overrides other layers
     my_adjust_layer,
     my_reaper_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}


void caps_word_set_user(bool active) {
    if (active) {
        rgblight_set_layer_state(2, true);
    } else {
       rgblight_set_layer_state(0, layer_state_is( _COLEMAK));
       rgblight_set_layer_state(1, layer_state_is( _QWERTY));
       rgblight_set_layer_state(2, false);
        rgblight_set_layer_state(3, layer_state_is( _REAPER));
       rgblight_set_layer_state(4, layer_state_is( _SYMBOLS));
       rgblight_set_layer_state(5, layer_state_is( _NUMBERS));
       rgblight_set_layer_state(6, layer_state_is( _NAV));
       rgblight_set_layer_state(7, layer_state_is( _ADJUST));


    }
}
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

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_set_layer_state(2, true);
    } else {
       rgblight_set_layer_state(0, layer_state_is( _COLEMAK));
       rgblight_set_layer_state(1, layer_state_is( _QWERTY));
       rgblight_set_layer_state(2, false);
        rgblight_set_layer_state(3, layer_state_is( _REAPER));
       rgblight_set_layer_state(4, layer_state_is( _SYMBOLS));
       rgblight_set_layer_state(5, layer_state_is( _NUMBERS));
       rgblight_set_layer_state(6, layer_state_is( _NAV));
       rgblight_set_layer_state(7, layer_state_is( _ADJUST));


    }
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
         rgblight_set_layer_state(0, layer_state_is( _COLEMAK));


        rgblight_set_layer_state(3, layer_state_is( _REAPER));
       rgblight_set_layer_state(4, layer_state_is( _SYMBOLS));
       rgblight_set_layer_state(5, layer_state_is( _NUMBERS));
       rgblight_set_layer_state(6, layer_state_is( _NAV));
       rgblight_set_layer_state(7, layer_state_is( _ADJUST));
    return state;
}


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
    [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset)
};
