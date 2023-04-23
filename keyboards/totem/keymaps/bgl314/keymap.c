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

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ T R A C K P A D                                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘
#ifdef POINTING_DEVICE_ENABLE

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);  // always required before the auto mouse feature will work
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
//     #ifdef CONSOLE_ENABLE
//     uprintf("mouse col: %u, row: %u\n",mouse_report.h, mouse_report.v);
// #endif
    if (vscrolling_mode) {
        // only vertical scrolling.
        mouse_report.h = 0;//mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }else if (scrolling_mode) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}
/*
void i2c_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;
        // Try releasing special pins for a short time
        palSetLineMode(I2C1_SCL_PIN, PAL_MODE_INPUT);
        palSetLineMode(I2C1_SDA_PIN, PAL_MODE_INPUT);
        chThdSleepMilliseconds(10);
        palSetLineMode(I2C1_SCL_PIN, PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_SLEWFAST | PAL_RP_PAD_DRIVE4);
        palSetLineMode(I2C1_SDA_PIN, PAL_MODE_ALTERNATE_I2C | PAL_RP_PAD_SLEWFAST | PAL_RP_PAD_DRIVE4);
    }
}
*/
#endif //POINTING_DEVICE_ENABLE




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
        KC_Z,   KC_Z,    KC_X,      KC_C,      KC_V,    KC_B,    KC_K,      KC_M,      KC_COMM,  KC_DOT,  KC_SLSH, KC_SLSH,
    MT(MOD_LALT,KC_ESC),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC), LT(_NAV,KC_SPC),OSM(MOD_RSFT) , MO(_SYMBOLS)
    ),
    [_MOUSE] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                SCROLL,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,
                VSCROLL,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,CPI_UP, _______,  _______,  _______,  _______,  _______,
    _______,LCTL(KC_Z),LCTL(KC_X), LCTL(KC_C) ,LCTL(KC_V),CPI_DN,_______,  _______,  _______,  _______,  _______,  _______,
                                  KC_LALT,  KC_LSFT,  MT(MOD_LCTL,TG(_MOUSE)),  _______,  _______,  _______
    ),
    [_GAMES] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                KC_A,     KC_R,     KC_S,     KC_T,     KC_D,     KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,   _______, _______,
                            KC_TAB, MO(_GAMES_ALT),   KC_SPC,       _______, _______, KC_RGUI
    ),
    [_GAMES_ALT] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_F9,    KC_F10,  KC_F11,   KC_F12,  KC_NO,      _______,  _______,  _______,  _______,  _______,
                KC_F5,    KC_F6,   KC_F7,   KC_F8,  KC_BSPC,      KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    _______,    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_ESC,      _______,  _______,  _______,  _______,  _______,  _______,
                                    _______, _______, _______,   _______,  _______, _______
    ),
    [_REAPER] = LAYOUT(
  //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                _______,  _______, _______, TD(P_SPACE), _______, _______, _______, _______, _______, _______,
                _______,  _______, TD(S_ALT_S), TD(T_TAKE), _______,   _______, _______, _______, _______, _______,
     _______,   _______, _______, _______, _______,   _______,     _______, _______,  _______, _______, _______, _______,
                                     _______,_______,_______, _______ ,  _______ ,_______
    ),
    [_SYMBOLS] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC,   KC_AMPR, KC_ASTR,   KC_LPRN, KC_RPRN,
                KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN,    KC_LT,    KC_GT,     KC_RPRN,  KC_RCBR,  KC_RBRC, KC_BSLS,
    _______,    KC_TILDE,  KC_PIPE, KC_UNDS, KC_MINUS,KC_PLUS,   KC_NO,     KC_EQL, KC_LT ,     KC_GT,   KC_SLSH,_______,
                                  KC_LALT,KC_LSFT,  _______,     _______,  _______,  _______
    ),
    [_NUMBERS] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_PSLS,   KC_7,    KC_8,    KC_9,    KC_MINUS,  KC_MINUS,  KC_7,       KC_8,    KC_9,    KC_PSLS,
                KC_PAST,   KC_4,    KC_5,  KC_6,    KC_PLUS,     KC_PLUS,   KC_4,       KC_5,    KC_6,    KC_PAST,
    _______,    TD(DOT_ENT), KC_1,  KC_2,   KC_3,   KC_SPC,     KC_EQL,   KC_1,     KC_2,     KC_3,   TD(DOT_ENT),_______,
                                  KC_0,    _______, KC_DEL,   KC_0, _______, _______
    ),
    [_NAV] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_PGUP  , KC_HOME, KC_UP,KC_END,  KC_NO ,       KC_NUM_LOCK,KC_PSCR,  KC_INS,    KC_NO,  KC_NO,
                KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_DEL,    QK_CAPS_WORD_TOGGLE,  KC_RSFT, KC_RCTL,  KC_RALT,  KC_ESC,
     _______,   LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V), KC_NO,      KC_CAPS,   KC_RGUI,   KC_NO,    KC_NO,  KC_ENT,_______,
                                  KC_ESC,  KC_TAB,_______ ,    _______, KC_NO, KC_NO
    ),
    [_ADJUST] = LAYOUT(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_F9, KC_F10,    KC_F11,   KC_F12, KC_NO ,      KC_NO, KC_NO,   KC_NO,    TG(_REAPER), TG(_GAMES),
                KC_F5, KC_F6,    KC_F7,   KC_F8,  KC_VOLU,         KC_NO,  SHT_MPLY, CTL_MSTP, ALT_MPRV,  GUI_MNXT,
    _______,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_VOLD,       KC_NO,KC_VOLU, KC_VOLD, KC_MUTE,   _______,_______,
                                 _______,   _______,    _______, _______,   _______,   _______
    )
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



