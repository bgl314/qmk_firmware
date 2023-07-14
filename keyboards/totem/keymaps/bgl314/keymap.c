/*
                                             ▀▀▀▀▀     ▀▀▀▀▀          ▀▀█▀▀
                                             ▄▀▀▀▄  ▄  ▄▀▀▀▄  ▄  ▄▀▀▀▄  █  ▄▀▀▀▄
                                             █   █  █  █   █  █  █   █  █  █   █
                                              ▀▀▀   █   ▀▀▀   █   ▀▀▀   ▀   ▀▀▀
                                                    █      ▄▄▄█▄▄▄    █   █
                                                    ▀      █  █  █     █▄█
                                                  ▀▀▀▀▀    █  █  █      ▀
                                                           ▀  ▀  ▀  D E F A U L T

▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "totem.h"
#include "print.h"


// get my qmk-config folder and put it in the same directory as qmk_firmware
#include "../qmk-config/common_keymap.h"





// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /*
   ┌─────────────────────────────────────────────────┐
   │ q w e r t y                                     │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡    Q    │    W    │    E    │    R    │    T    ││    Y    │    U    │    I    │    O    │    P    │
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │    A    │    S    │    D    │    F    │    G    ││    H    │    J    │    K    │    L    │    ;    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │    Q    │    Z    │    X    │    C    │    V    │    B    ││    N    │    M    │    ,    │    .    │    /    │    P    │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────
                                 │  CTRL   │  LOWER  │  SPACE  ││  ENTER  │  RAISE  │  BSPC   │
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘*/

      [_COLEMAK] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_Q,    KC_W,      KC_F,      KC_P,    KC_G,    KC_J,      KC_L,      KC_U,     KC_Y,    KC_QUOT,
                KC_A,    ALT_R,     CTL_S,     SHT_T,   KC_D,    KC_H,      SHT_N,     CTL_E,    ALT_I,   KC_O,
        KC_Z,   KC_Z,    KC_X,      KC_C,      KC_V,    KC_B,    KC_K,      KC_M,      KC_COMM,  KC_DOT,  KC_SLSH, KC_BSLS,
    MT(MOD_LGUI,KC_ESC),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC), LT(_NAV,KC_SPC),OSM(MOD_RSFT) , MO(_SYMBOLS)
    ),
    [_MOUSE] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                SCROLL,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,CPI_UP, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    _______,LCTL(KC_Z),LCTL(KC_X), LCTL(KC_C) ,LCTL(KC_V),CPI_DN,KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                                  KC_LALT,  KC_LSFT,  _______,  KC_NO,  KC_NO,  KC_NO
    ),
    [_GAMES] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______, _______,
                            MO(_GAMES_ALT),KC_TAB,    KC_SPC,       _______, _______, KC_RGUI
    ),
    [_GAMES_ALT] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_F9,    KC_F10,  KC_F11,   KC_F12,  KC_NO,      _______,  _______,  _______,  _______,  _______,
                KC_F5,    KC_F6,   KC_F7,   KC_F8,  KC_BSPC,      KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    _______,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_ESC,      _______,  _______,  _______,  _______,  _______,  _______,
                                    _______, _______, _______,   _______,  _______, _______
    ),
    [_SYMBOLS] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC,   KC_AMPR, KC_ASTR,   KC_LPRN, KC_RPRN,
                KC_TILDE, KC_GRV, KC_PIPE, KC_PLUS,  KC_EQL,    KC_LT,   SHT_LPRN,  CTL_LCBR,ALT_LBRC, KC_GT,
    _______,    KC_BSLS,  KC_NO, KC_UNDS, KC_MINUS,KC_NO ,          KC_NO,   KC_RPRN, KC_RCBR ,KC_RBRC, KC_BSLS,_______,
                                  KC_LALT,KC_LSFT,  _______,     _______,  _______,  _______
    ),
    [_NUMBERS] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_PSLS,   KC_7,    KC_8,    KC_9,    KC_MINUS,  KC_MINUS,  KC_7,       KC_8,    KC_9,    KC_PSLS,
                KC_PAST,   KC_4,    KC_5,  KC_6,    KC_PLUS,     KC_PLUS,   KC_4,       KC_5,    KC_6,    KC_PAST,
    _______,    TD(DOT_ENT), KC_1,  KC_2,   KC_3,   KC_0,     KC_EQL,   KC_1,     KC_2,     KC_3,   TD(DOT_ENT),_______,
                                  KC_SPC,    _______, KC_DEL,   KC_0, _______, _______
    ),
    [_NAV] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_PGUP  , KC_HOME, KC_UP,KC_END,  KC_NO ,       KC_NUM_LOCK,KC_PSCR,  KC_INS,    KC_NO,  SCLN_RET,
                KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_DEL,    QK_CAPS_WORD_TOGGLE,  KC_RSFT, KC_RCTL,  KC_RALT,  KC_ESC,
     _______,   LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V), KC_NO,      KC_CAPS,   TD(TD_PAREN),  TD(TD_CBRC),    TD(TD_BKT),  TD(TD_GTLT),_______,
                                  _______, MT(MOD_LSFT, KC_TAB) ,_______ ,    _______, KC_NO, KC_NO
    ),
#ifdef HAS_PASSWORDS
    [_ADJUST] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_MNXT , KC_F7, KC_F8, KC_F9,   KC_F10,      KC_NO, KC_NO,   KC_NO,    KC_NO, TG(_GAMES),
                KC_MPLY,KC_F4,KC_F5, KC_F6,       KC_F11,         OSL(_PWDS),  OSM(MOD_RSFT), OSM(MOD_RCTL),  OSM(MOD_RALT),  OSM(MOD_RGUI),
    _______,    KC_MSTP, KC_F1,   KC_F2,   KC_F3,   KC_F12,        KC_NO,KC_VOLU, KC_VOLD, KC_MUTE,   OSL(_PWDS),OSL(_PWDS),
                                 _______,   _______,    _______, _______,   _______,   _______
    ),
    [_PWDS] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_NO, KC_NO,    KC_NO,   KC_NO, PWD_G ,        KC_NO, PWD_L,   KC_NO,    KC_NO, KC_NO ,
                KC_NO, KC_NO,    PWD_S,   KC_NO,  PWD_D,         KC_NO,  PWD_N, KC_NO,  KC_NO,  KC_NO,
    _______,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,KC_NO, KC_NO, KC_NO,   KC_NO,KC_NO,
                                 _______,   _______,    _______, _______,   _______,   _______
    )
#else
[_ADJUST] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_MNXT , KC_F7, KC_F8, KC_F9,   KC_F10,      KC_NO, KC_NO,   KC_NO,    KC_NO, TG(_GAMES),
                KC_MPLY,KC_F4,KC_F5, KC_F6,       KC_F11,         KC_NO,  OSM(MOD_RSFT), OSM(MOD_RCTL),  OSM(MOD_RALT),  OSM(MOD_RGUI),
    _______,    KC_MSTP, KC_F1,   KC_F2,   KC_F3,   KC_F12,        KC_NO,KC_VOLU, KC_VOLD, KC_MUTE,   KC_NO,_______,
                                 _______,   _______,    _______, _______,   _______,   _______
    )
#endif
/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌─────────────────────────────────────────────────┐
   │ t e m p l a t e                                 │      ╭╮╭╮╭╮╭╮
   └─────────────────────────────────────────────────┘      │╰╯╰╯╰╯│
             ┌─────────┬─────────┬─────────┬─────────┬──────╨──┐┌──╨──────┬─────────┬─────────┬─────────┬─────────┐
     ╌┄┈┈───═╡         │         │         │         │         ││         │         │         │         │         │
             ├─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┤
             │         │         │         │         │         ││         │         │         │         │         │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │         │         │         │         │         ││         │         │         │         │         │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┤├─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │         ││         │         │         │
                                 └─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┘

   [_TEMPLATE] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______,
              _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______,
    _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______, _______,
                                  _______,  _______,   _______,  _______,  _______,  _______,
 ),
*/
};



/*
  ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸


                                                          ██████
                                                            ██  ▄▄▄▄
                                                            ██ ██▀▀██
                                                            ▀▀ ██▄▄██
                                                        ██████  ▀▀▀▀
                                                          ██ ▄▄▄▄▄▄
                                                          ██ ██▀▀▀▀
                                                          ██ ██████
                                                             ██▄▄▄▄
                                                             ▀▀▀▀▀▀
                                                           ████████
                                                           ██ ██ ██
                                                           ██ ██ ██
                                                           ▀▀ ▀▀ ▀▀
                                                          ████████

*/



