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
// get my qmk-config folder and put it in the same directory as qmk_firmware
#include "../qmk-config/common_keymap.h"



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
   ┌───────────────────────────────────────────────────────────┐
   │ c o l e m a k                                             │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    Q    │    W    │    F    │    P    │    G    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    J    │    L    │    U    │    Y    │    ;    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   TAB   │    A    │    R    │    S    │    T    │    D    ├─╯                ╰─┤    H    │    N    │    E    │    I    │    O    │    "    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │   DEL   │    Z    │    X    │    C    │    V    │    B    ││ SHIFT  ││PLY/PSE ││    K    │    M    │    ,    │    .    │    /    │  SHIFT  │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │  CTRL   │  LOWER  │  SPACE  │   ALT   ││ CMD/WIN │  ENTER  │  RAISE  │  BSPCE  │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

    [_COLEMAK] = LAYOUT_ortho_2x2u(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
       KC_NO,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,      KC_NO,      KC_NO,   KC_6,      KC_7,    KC_8,      KC_9,       KC_0,   KC_NO,
        KC_NO,  KC_Q,    KC_W,     KC_F,    KC_P,    KC_G,      KC_NO,      KC_NO,   KC_J,      KC_L,    KC_U,      KC_Y,       KC_QUOT,KC_NO,
        KC_NO,  KC_A,   ALT_R,    CTL_S,   SHT_T,   KC_D,      KC_NO,      KC_NO,   KC_H,      SHT_N,   CTL_E,     ALT_I,      KC_O,  KC_NO,
        KC_NO,  KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,       KC_NO,       KC_NO,   KC_K,      KC_M,    KC_COMM,   KC_DOT,     KC_SLSH,KC_NO,
    KC_NO,KC_NO,KC_NO, MT(MOD_LALT,KC_ESC),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC), LT(_NAV,KC_SPC),OSM(MOD_RSFT) , MO(_SYMBOLS),KC_NO,KC_NO,  KC_NO
    ),

    [_GAMES] = LAYOUT_ortho_2x2u(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,    KC_A,     KC_R,     KC_S,     KC_T,     KC_D,    _______,   _______,   KC_H,     KC_N,     KC_E,     KC_I,     KC_O,   _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,  _______,  _______,KC_TAB, MO(_GAMES_ALT),   KC_SPC,                  _______,   _______,   KC_RGUI,  _______, _______,_______
    ),
    [_GAMES_ALT] = LAYOUT_ortho_2x2u(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,  KC_F9,    KC_F10,  KC_F11,   KC_F12,  KC_NO,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,  KC_F5,    KC_F6,   KC_F7,   KC_F8,  KC_BSPC,     _______,   _______,   _______,     _______,     _______,     _______,     _______,   _______,
    _______,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_ESC,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,  _______,  _______,KC_TAB, MO(_GAMES_ALT),   KC_SPC,                  _______,   _______,   _______,  _______, _______,_______
    ),
    [_REAPER] = LAYOUT_ortho_2x2u(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______, _______,  _______, _______,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______,  _______,  _______, _______, TD(P_SPACE), _______, _______,    _______,  _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______,  _______, TD(S_ALT_S), TD(T_TAKE), _______,  _______,_______,    _______,  _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
_______, _______,  _______,  _______,_______,_______ ,                             _______ ,_______,  _______,_______, _______,  _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),
    [_SYMBOLS] = LAYOUT_ortho_2x2u(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       _______,    _______,KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,_______,
    _______,KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN,    KC_LT,     _______,    _______,KC_GT,  KC_RPRN,  KC_RCBR,KC_RBRC, KC_BSLS,_______,
    _______,KC_TILDE,  KC_PIPE  , KC_UNDS, KC_MINUS,KC_PLUS ,   KC_MUTE,   KC_MPLY,  KC_NO,  KC_EQL, KC_LT ,KC_GT, KC_SLSH,_______,
    _______,_______,_______,    KC_LALT,KC_LSFT,  _______,                    _______,  _______,  _______,_______,_______,_______
    ),
    [_NUMBERS] = LAYOUT_ortho_2x2u(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,  KC_PSLS,KC_7,    KC_8,    KC_9,    KC_MINUS,    _______, _______,   KC_MINUS, KC_7,    KC_8,    KC_9,    KC_PSLS,_______,
    _______,KC_PAST,    KC_4,    KC_5,  KC_6,    KC_PLUS,  _______,    _______,     KC_PLUS,    KC_4,    KC_5,  KC_6,    KC_PAST,_______,
    _______,TD(DOT_ENT), KC_1,  KC_2,   KC_3,   KC_SPC,    KC_MPLY,        KC_MPLY,  KC_EQL,   KC_1,     KC_2,     KC_3,   TD(DOT_ENT),_______,
    _______,_______,_______,KC_0,    _______, KC_DEL,    KC_0, _______, _______,_______,_______,_______
    ),
    [_NAV] = LAYOUT_ortho_2x2u(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______,KC_PGUP  , KC_HOME, KC_UP,KC_END,  KC_NO ,_______,  _______,          KC_NO,KC_PSCR,  KC_INS,    KC_NO,  KC_NO,_______,
    _______,KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_DEL,_______,  _______,        QK_CAPS_WORD_TOGGLE,  KC_RSFT, KC_RCTL,  KC_RALT,  KC_ESC,_______,
    _______,LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V), KC_NO, KC_MUTE,   KC_MPLY,   KC_CAPS,   KC_NO,   KC_NO,    KC_NO,  KC_ENT,_______,
    _______,_______,_______,        KC_ESC,  KC_TAB,_______ ,       _______, KC_NO, KC_NO,_______,_______,_______
    ),
    [_ADJUST] = LAYOUT_ortho_2x2u(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______, _______,  _______,
    _______, KC_F9, KC_F10,    KC_F11,   KC_F12, KC_NUM_LOCK ,      _______,  _______,  RGB_TOG, _______,   _______,    TG(_REAPER), TG(_GAMES),_______,
    _______,KC_F5, KC_F6,    KC_F7,   KC_F8,  KC_VOLU,          _______,  _______,  RGB_MOD,  SHT_MPLY, CTL_MSTP, ALT_MPRV,  GUI_MNXT,_______,
    _______,KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_VOLD,           KC_MUTE, KC_MPLY,    RGB_RMOD,KC_VOLU, KC_VOLD, KC_MUTE,   _______,_______,
    _______,_______,_______,    _______,   _______,  _______,     _______,   _______, _______,   _______,   _______,_______
    )

};


// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED},
    {6, 2, HSV_RED},

    {13, 1, HSV_RED}          // Light 4 LEDs, starting with LED 12
);
const rgblight_segment_t PROGMEM my_default_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 14, HSV_PURPLE  }     // Light 4 LEDs, starting with LED 12
);

const rgblight_segment_t PROGMEM my_games_layer[] = RGBLIGHT_LAYER_SEGMENTS(
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
    my_games_layer,
    my_reaper_layer,
    my_capslock_layer, // mouse layer
    my_symbol_layer,
    my_number_layer,
    my_nav_layer,
    my_adjust_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}


void caps_word_set_user(bool active) {
    if (active) {
        rgblight_set_layer_state(_MOUSE, true);
    } else {
        rgblight_set_layer_state(_COLEMAK, layer_state_is( _COLEMAK));
        rgblight_set_layer_state(_GAMES, layer_state_is( _GAMES));
        rgblight_set_layer_state(_REAPER, layer_state_is( _REAPER));
        rgblight_set_layer_state(_SYMBOLS, layer_state_is( _SYMBOLS));
        rgblight_set_layer_state(_NUMBERS, layer_state_is( _NUMBERS));
        rgblight_set_layer_state(_NAV, layer_state_is( _NAV));
        rgblight_set_layer_state(_ADJUST, layer_state_is( _ADJUST));
    }
}


bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        rgblight_set_layer_state(_MOUSE, true);
    } else {
        rgblight_set_layer_state(_COLEMAK, layer_state_is( _COLEMAK));
        rgblight_set_layer_state(_GAMES, layer_state_is( _GAMES));
        rgblight_set_layer_state(_REAPER, layer_state_is( _REAPER));
        rgblight_set_layer_state(_SYMBOLS, layer_state_is( _SYMBOLS));
        rgblight_set_layer_state(_NUMBERS, layer_state_is( _NUMBERS));
        rgblight_set_layer_state(_NAV, layer_state_is( _NAV));
        rgblight_set_layer_state(_ADJUST, layer_state_is( _ADJUST));
    }
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(_COLEMAK, layer_state_is( _COLEMAK));
    rgblight_set_layer_state(_REAPER, layer_state_is( _REAPER));
    rgblight_set_layer_state(_SYMBOLS, layer_state_is( _SYMBOLS));
    rgblight_set_layer_state(_NUMBERS, layer_state_is( _NUMBERS));
    rgblight_set_layer_state(_NAV, layer_state_is( _NAV));
    rgblight_set_layer_state(_ADJUST, layer_state_is( _ADJUST));
    return state;
}
