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
#ifdef HAPTIC_ENABLE
#include "drivers/haptic/DRV2605L.h"
#endif //HAPTIC ENABLE
#ifdef AUDIO_ENABLE
#include "lib/klounds.h"
#endif //AUDIO ENABLE
#ifdef OLED_ENABLE
    #include "bongo.h"
    void oled_request_wakeup(void);
#endif
// get my qmk-config folder and put it in the same directory as qmk_firmware

#include "../qmk-config/common_keymap.h"
#include <stdio.h>
#include <string.h>
#include "klor.h"
#include "print.h"



// ┌───────────────────────────────────────────────────────────┐
// │ c a p s  w o r d                                          │
// └───────────────────────────────────────────────────────────┘
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

bool wasAdjustLayer=false;
bool wasGameLayer=false;
bool wasMouseLayer=false;



// ┌───────────────────────────────────────────────────────────┐
// │ l a y e r   s w i t c h i n g                             │
// └───────────────────────────────────────────────────────────┘
layer_state_t layer_state_set_user(layer_state_t state) {
     //state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
     {
        #ifdef HAPTIC_ENABLE
        switch (get_highest_layer(state)) {
            case _GAMES:
            if(wasAdjustLayer)
                DRV_pulse(soft_bump);
            break;
            case _COLEMAK:
            if(wasGameLayer )
                DRV_pulse(soft_bump);
            break;
            default: //  for any other layers, or the default layer
                break;
        }
        #endif // HAPTIC_ENABLE
        #ifdef AUDIO_ENABLE
            switch (get_highest_layer(state)) {
                case _GAMES:
                if(wasAdjustLayer)
                    PLAY_SONG(mac_song);
                break;
                default: //  for any other layers, or the default layer
                    break;
        }
        #endif // AUDIO_ENABLE
     }



    wasAdjustLayer=layer_state_cmp(state,_ADJUST);
    wasGameLayer=layer_state_cmp(state,_GAMES);
    wasMouseLayer=layer_state_cmp(state, _MOUSE);

    return state;
}




#ifdef RGB_MATRIX_ENABLE
#include "color.h"
#endif
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
            rgb_matrix_set_color(i, RGB_MAGENTA);
        }
    }
#ifdef HAS_PASSWORDS
    else if (get_highest_layer(layer_state) ==_PWDS) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }
#endif
    // else
    //  if (IS_LAYER_ON(_MOUSE)) {
    //     for (uint8_t i = led_min; i <= led_max; i++) {
    //         rgb_matrix_set_color(i, RGB_WHITE);
    //     }
    // }
    return true;
}

#endif




// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ H A P T I C   F E E D B A C K                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

void keyboard_post_init_user(void) {
  // Call the post init code.
  #if HAPTIC_ENABLE
    haptic_disable(); // disables per key haptic feedback by default
  #endif //HAPTIC ENABLE

  #if RGB_MATRIX_ENABLE
    rgblight_enable_noeeprom();
    //rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    //rgblight_sethsv_noeeprom(35, 255, 255); // set default RGB color to yellow
  #endif //RGB_MATRIX_ENABLE
  //debug_enable=true;
  //debug_mouse=true;
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
    bool qwerty= layer_state_is(_GAMES);
    bool qwerty_alt= layer_state_is(_GAMES_ALT);
    bool adjust = layer_state_is(_ADJUST);
    bool capsword=is_caps_word_on();

    oled_set_cursor(0, 0);
    if(number){
        oled_write_P(PSTR("12345"), led_state.caps_lock ||capsword);
    } else if(symbol){
        oled_write_P(PSTR("!@#$^"), led_state.caps_lock||capsword);
    } else if(mouse){
        oled_write_P(PSTR("MOUSE"), led_state.caps_lock||capsword);
    } else if(adjust){
        oled_write_P(PSTR(" ADJ "), led_state.caps_lock||capsword);
    } else if(nav){
        oled_write_P(PSTR(" NAV "), led_state.caps_lock||capsword);
    }  else if(qwerty_alt){
        oled_write_P(PSTR("GMS_ALT"), led_state.caps_lock||capsword);
    }  else if(qwerty){
        oled_write_P(PSTR("GAMES"), led_state.caps_lock||capsword);
    } else {
        oled_write_P(PSTR("COLMAK"), led_state.caps_lock||capsword);
    }

    oled_set_cursor(0, 1);

    uint8_t mod_state = get_mods();
    if(mod_state & MOD_MASK_SHIFT)
        oled_write("shift", false);

    oled_set_cursor(6, 1);
    if(mod_state & MOD_MASK_CTRL)
        oled_write("ctrl", false);
    oled_set_cursor(0, 2);
    if(mod_state & MOD_MASK_ALT)
        oled_write("alt", false);
    oled_set_cursor(4, 2);
    if(mod_state & MOD_MASK_GUI)
        oled_write("gui", false);

    oled_set_cursor(0, 3);
    led_t led_usb_state = host_keyboard_led_state();

    if (led_usb_state.num_lock) {
        oled_write_P(n_lock, false); // ──── NUMLOCK
    } else {
        oled_write_P(b_lock, false);
    }

    if (led_usb_state.caps_lock) {
        oled_write_P(c_lock, false); // ─── CAPSLOCK
    } else {
        if(capsword){
            oled_write_P(c_lock, false);
        }else{
            oled_write_P(b_lock, false);
        }
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
    #endif // AUDIO ENABL

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
             tap_code(KC_MPRV);
          } else {
             tap_code(KC_MNXT);

          }
      }else {
            if (clockwise) {
             tap_code(KC_VOLD);
          } else {
             tap_code(KC_VOLU);

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

    [_COLEMAK] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_Q,    KC_W,      KC_F,      KC_P,    KC_G,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
                KC_A,    ALT_R,     CTL_S,    SHT_T,    KC_D,                            KC_H,    SHT_N,    CTL_E,    ALT_I,    KC_O,
            KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,       KC_NO,   KC_NO,          KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,
         MT(MOD_LGUI,KC_ESC),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC),     LT(_NAV,KC_SPC),OSM(MOD_RSFT) , MO(_SYMBOLS)
    ),
    [_MOUSE] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                       KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    SCROLL,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,CPI_UP,                      KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
    LCTL(KC_Z),LCTL(KC_X), LCTL(KC_C) ,LCTL(KC_V), CPI_DN ,  KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
                        KC_LALT,  KC_LSFT,  MT(MOD_LCTL,TG(_MOUSE)),    KC_NO,  KC_NO,  KC_NO
    ),
    [_GAMES] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    KC_A,     KC_R,     KC_S,     KC_T,     KC_D,                          KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    _______,  _______,  _______,  _______,  _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        MO(_GAMES_ALT),KC_TAB,    KC_SPC,     _______, _______, _______
    ),
    [_GAMES_ALT] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    KC_F9, KC_F10,    KC_F11,   KC_F12, KC_NO,                       _______,  _______,  _______,  _______,  _______,
    KC_F5, KC_F6,    KC_F7,   KC_F8,  KC_BSPC,                          KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_ESC,    _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        _______, _______, _______,      _______,  _______, _______
    ),
    [_SYMBOLS] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
            KC_TILDE, KC_GRV, KC_PIPE, KC_PLUS,    KC_EQL,                         KC_NO,  KC_LPRN,  KC_LCBR,KC_LBRC, KC_LT,
            KC_BSLS,  KC_NO, KC_UNDS, KC_MINUS,KC_NO ,   KC_MUTE,         KC_MPLY,  KC_NO,  KC_RPRN, KC_RCBR ,KC_RBRC, KC_GT,
                                  KC_LALT,KC_LSFT,  _______,      _______,  _______,  _______
    ),
    [_NUMBERS] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_PSLS,KC_7,    KC_8,    KC_9,    KC_MINUS,                            KC_MINUS, KC_7,    KC_8,    KC_9,    KC_PSLS,
            KC_PAST,    KC_4,    KC_5,  KC_6,    KC_PLUS,                            KC_PLUS,    KC_4,    KC_5,  KC_6,    KC_PAST,
            TD(DOT_ENT), KC_1,  KC_2,   KC_3,   KC_0,    KC_MPLY,        KC_MPLY,  KC_EQL,   KC_1,     KC_2,     KC_3,   TD(DOT_ENT),
                                KC_SPC,    _______, KC_DEL,     KC_0, _______, _______
    ),
    [_NAV] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
           KC_PGUP  , KC_HOME, KC_UP,KC_END,  KC_NO ,                            KC_NUM_LOCK,KC_PSCR,  KC_INS,    KC_NO,  KC_NO,
           KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_DEL,                       QK_CAPS_WORD_TOGGLE,  KC_RSFT, KC_RCTL,  KC_RALT,  KC_ESC,
        LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V), KC_NO, KC_MUTE,   KC_MPLY,  KC_CAPS,   TD(TD_PAREN),  TD(TD_CBRC),    TD(TD_BKT),  TD(TD_GTLT),
                                  KC_ESC,  KC_TAB,_______ ,       _______, KC_NO, KC_NO
    )
#ifdef HAS_PASSWORDS
    ,
    [_ADJUST] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
            KC_MNXT , KC_F7, KC_F8, KC_F9,   KC_F10,                     RGB_TOG, AU_TOGG,   QK_HAPTIC_TOGGLE,    KC_NO , TG(_GAMES),
            KC_MPLY,KC_F4,KC_F5, KC_F6,       KC_F11,                              RGB_MOD,  OSM(MOD_RSFT), OSM(MOD_RCTL),  OSM(MOD_RALT),  OSM(MOD_RGUI),
            KC_MSTP, KC_F1,   KC_F2,   KC_F3,   KC_F12,           KC_MUTE, KC_MPLY,    RGB_RMOD,KC_VOLU, KC_VOLD, KC_MUTE,   OSL(_PWDS),
                                 _______,   _______,    _______, _______,   _______,   _______
    ),
    [_PWDS] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
             KC_NO, KC_NO,    KC_NO,   KC_NO, PWD_G ,               KC_NO, PWD_L,   KC_NO,    KC_NO, KC_NO ,
                KC_NO, KC_NO,    PWD_S,   KC_NO,  PWD_D,         _______,  PWD_N, KC_NO,  KC_NO,  KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  _______,   _______,     KC_NO,KC_NO, KC_NO, KC_NO,   _______,
                                 _______,   _______,     _______, _______,   _______,   _______
    )
#else
 ,
    [_ADJUST] = LAYOUT_saegewerk(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
            KC_MNXT , KC_F7, KC_F8, KC_F9,   KC_F10,                       RGB_TOG, AU_TOGG,   QK_HAPTIC_TOGGLE,    KC_NO , TG(_GAMES),
            KC_MPLY,KC_F4,KC_F5, KC_F6,       KC_F11,                                RGB_MOD,  OSM(MOD_RSFT), OSM(MOD_RCTL),  OSM(MOD_RALT),  OSM(MOD_RGUI),
            KC_MSTP, KC_F1,   KC_F2,   KC_F3,   KC_F12,             KC_MUTE, KC_MPLY,    RGB_RMOD,KC_VOLU, KC_VOLD, KC_MUTE,   KC_NO,
                                 _______,   _______,  _______,      _______,   _______,   _______
    )
#endif

};


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



