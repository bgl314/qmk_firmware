/*

                                        █         █    █            ▄▄▄▀▀▀▀▀▀▄▄▄        █▀▀▀▀▀▀▀▀▀▀█
                                        █        █     █          ▄▀            ▀▄      █          █
                                        █       █      █        ▄▀                ▀▄    █          █
                                        █      █       █        █                  █    █          █
                                        █     █        █       █                    █   █          █
                                        █    █         █       █                    █   █▄▄▄▄▄▄▄▄▄▄█
                                        █   █ █        █       █                    █   █      █
                                        █  █   █       █        █                  █    █       █
                                        █ █     █      █        ▀▄                ▄▀    █        █
                                        ██       █     █          ▀▄            ▄▀      █         █
                                        █         █    █▄▄▄▄▄▄▄▄    ▀▀▀▄▄▄▄▄▄▀▀▀        █          █

                                        ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
                                        ┌─┐┌─╴╷┌──┬─
                                        │ ┐├─╴│└─┐│
                                        └─┘└─╴╵╶─┘╵
*/
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "klor.h"
#include "print.h"
#ifdef HAPTIC_ENABLE
#include "drivers/haptic/DRV2605L.h"
#endif //HAPTIC ENABLE
#ifdef OLED_ENABLE
    #include "bongo.h"
    void oled_request_wakeup(void);
#endif

#ifdef AUDIO_ENABLE
#include "lib/klounds.h"
#endif //AUDIO ENABLE

#ifdef RGB_MATRIX_ENABLE
#include "color.h"
#endif



// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                                      │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                                 │
// └───────────────────────────────────────────────────────────┘

enum klor_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _COLEMAK,
    _MOUSE,
    _QWERTY,
    _REAPER,
    _SYMBOLS,
    _NUMBERS,
    _NAV,
    _ADJUST,
};


#define SHT_O MT(MOD_RSFT, KC_O)
#define SHT_GRV MT(MOD_LSFT, KC_GRV)
#define SHT_BSLS MT(MOD_RSFT, KC_BSLS)
#define SHT_A MT(MOD_LSFT, KC_A)
#define CTL_N MT(MOD_RCTL, KC_N)
#define CTRL_T MT(MOD_LCTL, KC_T)
#define CTL_MPLY MT(MOD_RCTL, KC_MPLY)
#define SHT_MNXT MT(MOD_RSFT, KC_MNXT)

enum td_keycodes {
    SCROLL,
    DOT_ENT,
    Q_ESC,
    Z_ENT,
    D_DELETE,
    P_SPACE,
    S_ALT_S,
    T_TAKE,
    SLASH_ENT,
    SCLN_ENT // tap ent, hold shift, doubletap semicolon enter
};


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



// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

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

   [_COLEMAK] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              TD(Q_ESC),    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
    KC_NO,   SHT_A,    KC_R,    KC_S,    CTRL_T,    KC_D,                            KC_H,    CTL_N,    KC_E,    KC_I,    SHT_O,    KC_NO,
     KC_NO, TD(Z_ENT),    KC_X,   KC_C,    KC_V,    KC_B,       KC_NO,   KC_NO,      KC_K, KC_M,    KC_COMM, KC_DOT, TD(SLASH_ENT), TD(SCLN_ENT),
         MT(MOD_LALT,KC_ESC),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC),   KC_NO,    KC_NO,  LT(_NAV,KC_SPC),  MO(_SYMBOLS),MT(MOD_RALT,KC_RGUI)
 ),
   [_MOUSE] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,_______,                      _______,  _______,  _______,  _______,  _______,
    _______,  _______,  SCROLL,   _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ q w e r t y                                               │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    Q    │    W    │    E    │    R    │    T    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    Y    │    U    │    I    │    O    │    P    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   TAB   │    A    │    S    │    D    │    F    │    G    ├─╯                ╰─┤    H    │    J    │    K    │    L    │    ;    │    "    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │   DEL   │    Z    │    X    │    C    │    V    │    B    ││ SHIFT  ││PLY/PSE ││    N    │    M    │    ,    │    .    │    /    │  SHIFT  │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │  CTRL   │  LOWER  │  SPACE  │   ALT   ││ CMD/WIN │  ENTER  │  RAISE  │ BSPACE  │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_QWERTY] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                          KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                          KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  _______,
    KC_DEL,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LSFT,   KC_MPLY,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  _______,
                                  KC_LALT, _______, KC_LCTL,   KC_LALT,   KC_LGUI,   _______,  _______, _______
 ),

   [_REAPER] = LAYOUT_polydactyl(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
               _______,  _______, _______, TD(P_SPACE), _______,                            _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,  _______, TD(S_ALT_S), TD(T_TAKE), TD(D_DELETE),                            _______, _______, _______, _______, _______,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______,  _______, _______, _______, _______,   _______, _______,        _______, _______,  _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_SPC,_______,_______ , _______ ,          _______ ,_______,  _______,_______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ l o w e r                                                 │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │ CAPSLCK │ NUMLCK  │    ↑    │    =    │    {    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    }    │    7    │    8    │    9    │    +    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   ESC   │  HOME   │    ←    │    ↓    │    →    │    [    ├─╯                ╰─┤    ]    │    4    │    5    │    6    │    -    │    '    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │ SCRNSHT │   END   │   PG↑   │  SAVE   │   PG↓   │    (    ││  MUTE  ││PLY/PSE ││    )    │    1    │    2    │    3    │    *    │    ▼    │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │ ADJUST  │    0    │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_SYMBOLS] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_NO,  SHT_GRV,  KC_LBRC, KC_LCBR, KC_LPRN,    KC_LT,                           KC_GT,  KC_RPRN,  KC_RCBR,KC_RBRC, TD(SCLN_ENT) , KC_NO,
    KC_NO, KC_TILDE,  KC_PIPE  , KC_UNDS, KC_MINUS,KC_BSLS ,   KC_MUTE,   KC_MPLY,  KC_NO,  KC_PLUS, KC_EQL ,RSFT(KC_SCLN), KC_SLSH, KC_NO,
                                  _______,_______,  _______,    _______,   _______,  _______,  _______,  _______
 ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ r a i s e                                                 │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    !    │    @    │    #    │    $    │    %    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    ^    │    &    │    Ü    │    °    │    /    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   GMX   │    Ä    │    è    │    SZ   │    é    │         ├─╯                ╰─┤         │    ¥    │    €    │    £    │    Ö    │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │   WEB   │    `    │    ~    │   CUE   │         │         ││  MUTE  ││PLY/PSE ││         │         │         │ DM REC1 │ DM STOP │ DM PLY1 │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │  GIPHY  │ ADJUST  │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │    ▼    │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_NUMBERS] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_PSLS,KC_7,    KC_8,    KC_9,    KC_MINUS,                            KC_MINUS, KC_7,    KC_8,    KC_9,    KC_PSLS,
    KC_NO,  KC_PAST,    KC_4,    KC_5,  KC_6,    KC_PLUS,                            KC_PLUS,    KC_4,    KC_5,  KC_6,    KC_PAST,  KC_NO,
    KC_NO, TD(DOT_ENT), KC_1,  KC_2,   KC_3,   KC_SPC,    KC_MPLY,        KC_MPLY,  KC_EQL,   KC_1,     KC_2,     KC_3,   TD(DOT_ENT), KC_NO,
                                  KC_0,    _______, KC_DEL,   _______,   _______,  KC_0, _______, _______
 ),
  /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ r a i s e                                                 │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    !    │    @    │    #    │    $    │    %    │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │    ^    │    &    │    Ü    │    °    │    /    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   GMX   │    Ä    │    è    │    SZ   │    é    │         ├─╯                ╰─┤         │    ¥    │    €    │    £    │    Ö    │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │   WEB   │    `    │    ~    │   CUE   │         │         ││  MUTE  ││PLY/PSE ││         │         │         │ DM REC1 │ DM STOP │ DM PLY1 │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │  GIPHY  │ ADJUST  │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │    ▼    │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_NAV] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
             KC_PGUP, KC_HOME, KC_UP, KC_END,    KC_NO,                              KC_NO,    KC_PSCR,    KC_NO,    KC_NO,  KC_NO,
    KC_NO,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,                            KC_RALT,  KC_RCTL, KC_RSFT,  KC_INS,  KC_RSFT,  KC_NO,
    KC_NO,    RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V),KC_NO,  KC_MUTE,   KC_MPLY,    KC_NO,  KC_NO,    KC_NO,    KC_NO,  _______,  _______,
                                  _______,  _______, KC_DEL,    RGB_MOD,   RGB_MOD,   _______, KC_NO, KC_NO
 ),
 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ a d j u s t                                               │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │ AUDIO   │ HAPTIC  │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │   F7    │   F8    │   F9    │   F14   │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │  RESET  │ DEBUG   │ QWERTY  │         │         │         ├─╯                ╰─┤         │   F4    │   F5    │   F6    │   F12   │   F13   │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │  MAKE   │ OS SWAP │ COLEMAK │         │         │         ││  MUTE  ││PLY/PSE ││         │   F1    │   F2    │   F3    │   F10   │   F11   │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │    ▼    │    ▼    │    ▼    │    ▼    ││    ▼    │    ▼    │    ▼    │    ▼    │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_ADJUST] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
             KC_F9, KC_F10,    KC_F11,   KC_F12, RGB_TOG ,                            RGB_TOG, AU_TOG,   HPT_TOG,    TG(_REAPER), TG(_QWERTY),
     KC_NO,  KC_F5, KC_F6,    KC_F7,   KC_F8,  RGB_MOD,                              KC_RALT,  CTL_MPLY, KC_MSTP, KC_MPRV,  SHT_MNXT,KC_NO,
   KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   RGB_RMOD,           KC_MUTE, KC_MPLY,    KC_NO,KC_VOLU, KC_VOLD, KC_MUTE,   KC_CAPS, KC_NO,
                                 _______,   _______,  _______,     _______,   _______, _______,   _______,   _______
 )

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ t e m p l a t e                                           │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐                    ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │         │         │         │         │         │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │         │         │         │         │         │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │         │         │         │         │         │         ├─╯                ╰─┤         │         │         │         │         │         │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤╭────────╮╭────────╮├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │         │         │         │         │         │         ││        ││        ││         │         │         │         │         │         │
   └─────────┴─────────┴─────────┼─────────┼─────────┼─────────┼╰────────╯╰────────╯┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                 │         │         │         │         ││         │         │         │         │
                                 └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘

   [_TEMPLATE] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______
 )*/
};

layer_state_t layer_state_set_user(layer_state_t state) {
     state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
      #ifdef HAPTIC_ENABLE
     switch (get_highest_layer(state)) {

        case _REAPER:
           DRV_pulse(transition_hum);
            break;
        default: //  for any other layers, or the default layer
            //DRV_pulse(transition_hum);
            break;
    }
    #endif // HAPTIC_ENABLE
    #ifdef AUDIO_ENABLE
        switch (get_highest_layer(state)) {
            case _REAPER:
            PLAY_SONG(mac_song);
                break;
            default: //  for any other layers, or the default layer
                break;
    }
    #endif // AUDIO_ENABLE

    return state;
}

bool caps = false;

void caps_word_set_user(bool active) {
    if(active){
         #ifdef HAPTIC_ENABLE
           DRV_pulse(sharp_click);
        #endif // HAPTIC_ENABLE
    }else if(!caps){
        #ifdef HAPTIC_ENABLE
           DRV_pulse(soft_bump);
        #endif // HAPTIC_ENABLE
    }
}

#ifdef RGB_MATRIX_ENABLE


enum rgb_matrix_effects priormode= RGB_MATRIX_TYPING_HEATMAP;

bool led_update_user(led_t led_state) {
    if(led_state.caps_lock){
        priormode=rgb_matrix_get_mode();

    }else if(!is_caps_word_on()){

    }
    caps=led_state.caps_lock;
    return true;
}
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_caps_word_on() || caps) {
        for (uint8_t i = led_min; i <= led_max; i++) {
    //if (!(g_led_config.flags[i] & LED_FLAG_KEYLIGHT) && g_led_config.flags[i]!=LED_FLAG_UNDERGLOW) {
                rgb_matrix_set_color(i, RGB_MAGENTA);
     //       }else{
                // rgb_matrix_set_color(i, 0,0,0);
      //      }
        }
    }
    return true;
}

#endif

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ T R A C K B A L L                                                                                                                          │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef POINTING_DEVICE_ENABLE
static bool scrolling_mode = false;
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);  // always required before the auto mouse feature will work
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
//     #ifdef CONSOLE_ENABLE
//     uprintf("mouse col: %u, row: %u\n",mouse_report.h, mouse_report.v);
// #endif
    if (scrolling_mode) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

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

#endif //POINTING_DEVICE_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    if(record->event.key.col!=0 ||record->event.key.row !=0)
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, time: %u,  count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.time, record->tap.count);
#endif

    #ifdef OLED_ENABLE
        oled_request_wakeup();
    #endif

    switch (keycode) {
// ┌─────────────────────────────────────────────────┐
// │ m o u s e                                       │
// └─────────────────────────────────────────────────┘

     case SCROLL:
        #ifdef HAPTIC_ENABLE
            DRV_pulse(transition_hum);
        #endif // HAPTIC
        if (record->event.pressed) {
            scrolling_mode = true;
            pointing_device_set_cpi(50);
        } else {
            scrolling_mode = false;
            pointing_device_set_cpi(500);
        }
        return false;
      case KC_MPLY:
        if (record->event.pressed) {
          #ifdef HAPTIC_ENABLE
                  DRV_pulse(sharp_click);
          #endif // HAPTIC_ENABLE
        }
        break;

      case KC_CAPS:
        if (record->event.pressed) {
          #ifdef HAPTIC_ENABLE
                  DRV_pulse(medium_click1);
          #endif // HAPTIC_ENABLE
          #ifdef AUDIO_ENABLE
              led_t led_usb_state = host_keyboard_led_state();
              if (led_usb_state.caps_lock) {
                  PLAY_SONG(capson_song);
              }
              else {
                  PLAY_SONG(capsoff_song);
              }
          #endif // AUDIO_ENABLE
        }
        break;

    }

    return true;
}


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ H A P T I C   F E E D B A C K                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

void keyboard_post_init_user(void) {
  // Call the post init code.
//   #if HAPTIC_ENABLE
//     haptic_disable(); // disables per key haptic feedback by default
//   #endif //HAPTIC ENABLE

  #if RGB_MATRIX_ENABLE
    rgblight_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    //rgblight_sethsv_noeeprom(35, 255, 255); // set default RGB color to yellow
  #endif //RGB_MATRIX_ENABLE
  debug_enable=true;
  debug_mouse=true;
  uprintf("keeb init");
}

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ O L E D                                                                                                                                    │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

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
    static const char PROGMEM n_lock[] = {0x91, 0x92, 0};
    static const char PROGMEM c_lock[] = {0x93, 0x94, 0};
    static const char PROGMEM b_lock[] = {0xE1, 0xE1, 0};
    static const char PROGMEM sep_h2[] = {0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0xE1, 0};

    #ifdef AUDIO_ENABLE
      static const char PROGMEM aud_en[] = {0xAF, 0xB0, 0};
      static const char PROGMEM aud_di[] = {0xCF, 0xD0, 0};
    #endif
    #ifdef HAPTIC_ENABLE
      static const char PROGMEM hap_en[] = {0xB1, 0xB2, 0};
    #endif
    led_t led_state = host_keyboard_led_state();
    bool number = layer_state_is(_NUMBERS) & !layer_state_is(_ADJUST);
    bool symbol = layer_state_is(_SYMBOLS) & !layer_state_is(_ADJUST);
    bool mouse = layer_state_is(_MOUSE);
    bool nav = layer_state_is(_NAV);
    bool qwerty= layer_state_is(_QWERTY);
    bool adjust = layer_state_is(_ADJUST);
    oled_set_cursor(0, 0);
    if(number){
        oled_write_P(PSTR("12345"), led_state.caps_lock );
    } else if(symbol){
        oled_write_P(PSTR("!@#$^"), led_state.caps_lock);
    } else if(mouse){
        oled_write_P(PSTR("MOUSE"), led_state.caps_lock);
    } else if(adjust){
        oled_write_P(PSTR(" ADJ "), led_state.caps_lock);
    } else if(nav){
        oled_write_P(PSTR(" NAV "), led_state.caps_lock);
    } else if(qwerty){
        oled_write_P(PSTR("QWERTY"), led_state.caps_lock);
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

    led_t led_usb_state = host_keyboard_led_state();

    if (led_usb_state.num_lock) {
        oled_write_P(n_lock, false); // ──── NUMLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    if (led_usb_state.caps_lock) {
        oled_write_P(c_lock, false); // ─── CAPSLOCK
    } else {
        oled_write_P(b_lock, false);
    }
    oled_write_P(sep_h2, false);

    #ifndef AUDIO_ENABLE
        oled_write_P(b_lock, false);
    #endif
    #ifndef HAPTIC_ENABLE
        oled_write_P(b_lock, false);
    #endif

    #ifdef AUDIO_ENABLE // ────────────────── AUDIO
        if (is_audio_on()) {
          oled_write_P(aud_en, false);
        } else {
          oled_write_P(aud_di, false);
        }
    #endif // AUDIO ENABLE

     #ifdef HAPTIC_ENABLE // ─────────────── HAPTIC
        oled_write_P(hap_en, false);
     #endif // HAPTIC ENABLE

}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }

    if (!oled_task_needs_to_repaint()) {
            return false;
    }
   // if (is_keyboard_master()) {
        draw_bongo();
        render_layer_name();
    //}else{
    //}

    return false;
}



#endif // OLED_ENABLE




// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ E N C O D E R                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

#ifdef ENCODER_ENABLE

// ┌───────────────────────────────────────────────────────────┐
// │ e n c o d e r  L                                          │
// └───────────────────────────────────────────────────────────┘

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
       if(IS_LAYER_ON(_NAV)){
          if (clockwise) {
              tap_code(KC_MNXT);
          } else {
              tap_code(KC_MPRV);
          }
      }else {
            if (clockwise) {
              tap_code(KC_VOLU);
          } else {
              tap_code(KC_VOLD);
          }
      }

// ┌───────────────────────────────────────────────────────────┐
// │ e n c o d e r  R                                          │
// └───────────────────────────────────────────────────────────┘

    } else if (index == 1) {

    }
    return true;
}

#endif // ENCODER_ENABLE




/*

                                                       ▐█    ▟▛ ▐█     ▄▆▀▀▀▀▀▀▆▄  ▐█▀▀▀▀▀█▌
                                                       ▐█   ▟▛  ▐█    ▟▛        ▜▙ ▐█     █▌
                                                       ▐█  ▟▛   ▐█   ▐█          █▋▐█     █▌
                                                       ▐█ ▟█▙   ▐█   ▐█          █▋▐█▀▀▜█▀▀▘
                                                       ▐█▟▛ ▜▙  ▐█    ▜▙        ▟▛ ▐█   ▜▙
                                                       ▐█▛   ▜▙ ▐█▄▄▄▄ ▀▜▆▄▄▄▄▆▛▀  ▐█    ▜▙

                                                                 ▄██████████████▄
                                                                 ████████████████
                                                            ▄██████▀  ▀████▀  ▀██████▄
                                                            ███████▄  ▄████▄  ▄███████
                                                            ███████████▀▀▀▀███████████
                                                            ▀█████████▀ ▄▄ ▀█████████▀
                                                                 ████▀ ▄██▄ ▀████
                                                                 ████▄▄████▄▄████

*/



