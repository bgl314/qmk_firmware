#include QMK_KEYBOARD_H
#include "color.h"


#define _COLEMAK 0
#define _QWERTY 1
#define _SYMBOLS 2
#define _NUMBERS 3
#define _NAV 4
#define _ADJUST 5





enum td_keycodes {
    SCLN_ENT, // tap ent, hold shift, doubletap semicolon enter
    ESC_QWERTY // tap backspace, doubletap qwerty
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

    [_COLEMAK] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     TD(ESC_QWERTY),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_PSCR,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,    TD(SCLN_ENT),  KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  MT(MOD_LSFT,KC_CAPS), KC_Z,  KC_X,  KC_C,  KC_V,    KC_B,   KC_DEL,             KC_BSPC,  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT,KC_ENT),
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                        MT(MOD_LALT,KC_ENT),TT(_NUMBERS),MT(MOD_LCTL,KC_BSPC) ,      LT(_NAV,KC_SPC),  MO(_SYMBOLS),MT(MOD_RALT,KC_INS)
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_QWERTY] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LCTL,          _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, KC_SPC,                    _______,  _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYMBOLS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  KC_TILD,  KC_GRV, KC_LCBR, KC_LPRN,  KC_LBRC,                            KC_RBRC, KC_RPRN,  KC_RCBR, KC_PIPE,KC_BSLS   , KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LT,    KC_NO,    KC_UNDS, KC_MINUS,KC_NO , _______,             _______, KC_NO,  KC_PLUS, KC_EQL ,KC_NO,    KC_GT,   _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______,  _______,                    KC_NO, _______ ,  _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_NUMBERS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC , KC_PSLS,KC_7,    KC_8,    KC_9,    KC_MINUS,                            KC_MINUS, KC_7,    KC_8,    KC_9,    KC_PSLS,   _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  KC_PAST,    KC_4,    KC_5,  KC_6,    KC_PLUS,                            KC_PLUS,    KC_4,    KC_5,  KC_6,    KC_PAST,  KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_SPC,    KC_DOT,   KC_1,  KC_2,   KC_3,   KC_0, _______,           _______,     KC_0,   KC_1,     KC_2,     KC_3,   KC_DOT, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,    _______, KC_0,                    KC_0, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

   [_NAV] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                               KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSPC   , KC_PGUP, KC_HOME, KC_UP, KC_END,    KC_NO,                              KC_NO,    KC_PSCR,    KC_NO,    KC_NO,  KC_NO,  _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_NO,                            KC_NO,  KC_RSFT,KC_RCTL,  KC_INS,  KC_NO,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,    RCTL(KC_Z),RCTL(KC_X),RCTL(KC_C),RCTL(KC_V),  _______,   _______,            KC_NO,  KC_NO,  KC_NO,    KC_NO,    KC_NO,  KC_NO,  _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______,    KC_ENT, _______,                   _______, KC_NO, KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),


  [_ADJUST] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,    KC_NO,    KC_NO, KC_NO,     KC_NO, KC_NO,                                KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   TT(_QWERTY),
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO,  KC_NO,   KC_NO,    KC_NO,   KC_PSCR, KC_F11 ,                            KC_F12,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
	   KC_NO,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       KC_NO,   RGB_TOG, RGB_RMOD,RGB_MOD , KC_BRIGHTNESS_UP,KC_BRIGHTNESS_DOWN,KC_NO,KC_NO,    KC_VOLU,   KC_VOLD, KC_MUTE,   KC_MSTP,  KC_MPLY, 	KC_NO,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      KC_NO,   _______,  KC_NO,                      KC_NO,   _______,   KC_NO
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )
};


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
}


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


RGB rgbP1 = {RGB_BLUE};//{186,89,100};
RGB rgbP2 = {RGB_PURPLE};//{130,53,92};
RGB rgbP3 = {RGB_SPRINGGREEN};//{67, 90, 100};
RGB rgbP4 = {RGB_CHARTREUSE};//{42,91,91};
RGB rgbP5 = {RGB_ORANGE};//{17,92,100};



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
                        rgb = rgbMAGENTA;
                    else
                        rgb = rgbRED;
                    break;
                case _COLEMAK:
                    if(caps)
                        rgb = rgbMAGENTA;
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
// SHIFT-ENTER-SEMICOLON/ENTER

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
    //[SHIFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_ent_caps_finished, shift_ent_caps_reset),
    [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset),
    [ESC_QWERTY] =ACTION_TAP_DANCE_LAYER_TOGGLE(KC_ESC,_QWERTY)
};


