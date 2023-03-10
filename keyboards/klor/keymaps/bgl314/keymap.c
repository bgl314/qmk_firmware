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
    _GAMES,
    _REAPER,
    _MOUSE,
    _SYMBOLS,
    _NUMBERS,
    _NAV,
    _ADJUST,
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   h o m e r o w   m o d s                     │
// └───────────────────────────────────────────────────────────┘
#define GUI_A MT(MOD_LGUI, KC_A)
#define SHT_T MT(MOD_LSFT, KC_T)
#define CTL_S MT(MOD_LCTL, KC_S)
#define ALT_R MT(MOD_LALT, KC_R)
#define SHT_N MT(MOD_LSFT, KC_N)
#define CTL_E MT(MOD_RCTL, KC_E)
#define ALT_I MT(MOD_RALT, KC_I)
#define GUI_O MT(MOD_RGUI, KC_O)

#define SHT_LPRN MT(MOD_LSFT, LSFT(KC_9))
#define CTL_LCBR MT(MOD_LCTL, LSFT(KC_LBRC))
#define ALT_LBRC MT(MOD_LALT, KC_LBRC)

#define SHT_RPRN MT(MOD_RSFT, RSFT(KC_0))
#define CTL_RCBR MT(MOD_RCTL, RSFT(KC_RBRC))
#define ALT_RBRC MT(MOD_RALT, KC_RBRC)

#define SHT_MPLY MT(MOD_RSFT, KC_MPLY)
#define CTL_MSTP MT(MOD_RCTL, KC_MSTP)
#define ALT_MPRV MT(MOD_RALT, KC_MPRV)

#define CTL_MPLY MT(MOD_RCTL, KC_MPLY)
#define GUI_MNXT MT(MOD_RGUI, KC_MNXT)

enum custom_keycodes{
    SCROLL,
    DOT_ENT,
    Z_ENT,
    D_DELETE,
    P_SPACE,
    S_ALT_S,
    T_TAKE,
    SLASH_ENT,
    SCLN_ENT // tap ent, hold shift, doubletap semicolon enter
};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   o v e r r i d e s                           │
// └───────────────────────────────────────────────────────────┘
const key_override_t cw_override = ko_make_basic(MOD_MASK_SHIFT, OSM(MOD_RSFT), QK_CAPS_WORD_TOGGLE);

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   c o m b o s                                 │
// └───────────────────────────────────────────────────────────┘
const uint16_t PROGMEM slash_nav_combo[] = {KC_SLSH, LT(_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM o_nav_combo[] = {GUI_O, LT(_NAV,KC_SPC), COMBO_END};
const uint16_t PROGMEM a_bksp_combo[] = {MT(MOD_LCTL,KC_BSPC), GUI_A, COMBO_END};
const uint16_t PROGMEM rh_combo[] = {LT(_NAV,KC_SPC),OSM(MOD_RSFT), COMBO_END};

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   t a p d a n c e                             │
// └───────────────────────────────────────────────────────────┘
void scln_ent_sent_finished(tap_dance_state_t *state, void *user_data);
void scln_ent_sent_reset(tap_dance_state_t *state, void *user_data);
tap_dance_action_t tap_dance_actions[] = {
    [DOT_ENT]= ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_ENT),
    [SLASH_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_ENT),
    [Z_ENT] = ACTION_TAP_DANCE_DOUBLE(KC_Z, KC_ENT),
    [D_DELETE] = ACTION_TAP_DANCE_DOUBLE(KC_D, KC_DEL),
    [P_SPACE] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_SPACE),
    [S_ALT_S] = ACTION_TAP_DANCE_DOUBLE(KC_S, LALT(KC_S)),
    [T_TAKE] = ACTION_TAP_DANCE_DOUBLE(KC_T, LALT(LSFT(KC_T))),
    [SCLN_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scln_ent_sent_finished, scln_ent_sent_reset)
};


// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ B E H A V I O U R S                                                                                                            │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘
// ┌───────────────────────────────────────────────────────────┐
// │ t a p d a n c e                                           │
// └───────────────────────────────────────────────────────────┘
// SHIFT-ENTER-SEMICOLON/ENTER
// Handle the possible states for each tapdance keycode you define:
void scln_ent_sent_finished(tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
        register_code16(KC_SCLN);
     }else {
        register_code16(KC_SCLN);
        register_code16(KC_ENT);
     }
}
void scln_ent_sent_reset(tap_dance_state_t *state, void *user_data) {
     if(state->count == 1){
         unregister_code16(KC_SCLN);
     }else {
            unregister_code16(KC_SCLN);
             unregister_code16(KC_ENT);
     }
}
// ┌───────────────────────────────────────────────────────────┐
// │ c o m b o s                                               │
// └───────────────────────────────────────────────────────────┘
combo_t key_combos[COMBO_COUNT] = {
    COMBO(slash_nav_combo, KC_ENT),
    COMBO(o_nav_combo, KC_ENT),
    COMBO(rh_combo, MO(_ADJUST)),
    COMBO(a_bksp_combo, KC_ENT)
};
// ┌───────────────────────────────────────────────────────────┐
// │ o v e r r i d e s                                         │
// └───────────────────────────────────────────────────────────┘
// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &cw_override,
    NULL // Null terminate the array of overrides!
};

// ┌───────────────────────────────────────────────────────────┐
// │ c a p s w o r d                                           │
// └───────────────────────────────────────────────────────────┘
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
        case TD(Z_ENT):
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        default:
            return false;  // Deactivate Caps Word.
    }
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
// ┌───────────────────────────────────────────────────────────┐
// │ l a y e r   s w i t c h i n g                             │
// └───────────────────────────────────────────────────────────┘
layer_state_t layer_state_set_user(layer_state_t state) {
     //state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _ADJUST);
      #ifdef HAPTIC_ENABLE
     switch (get_highest_layer(state)) {
        case _REAPER:
           DRV_pulse(transition_hum);
            break;
        case _GAMES:
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
            case _GAMES:
            PLAY_SONG(mac_song);
                break;
            default: //  for any other layers, or the default layer
                break;
    }
    #endif // AUDIO_ENABLE
    return state;
}

// ┌───────────────────────────────────────────────────────────┐
// │ p e r - k e y  a c t i o n s                              │
// └───────────────────────────────────────────────────────────┘
uint8_t mod_state;
static bool scrolling_mode = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    if(record->event.key.col!=0 ||record->event.key.row !=0)
        uprintf("KL: kc: 0x%04X, col: %u, row: %u, time: %u,  count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.time, record->tap.count);
    #endif

    #ifdef OLED_ENABLE
        oled_request_wakeup();
    #endif
    mod_state = get_mods();
    switch (keycode) {
    #ifdef POINTING_DEVICE_ENABLE
// ┌─────────────────────────────────────────────────┐
// │ m o u s e   s c r o l l   l o c k               │
// └─────────────────────────────────────────────────┘
     case SCROLL:
        if (record->event.pressed) {
            scrolling_mode = true;
            pointing_device_set_cpi(50);
            #ifdef HAPTIC_ENABLE
            DRV_pulse(sharp_click);
            #endif // HAPTIC
        } else {
            scrolling_mode = false;
            pointing_device_set_cpi(500);
            #ifdef HAPTIC_ENABLE
            DRV_pulse(sharp_click);
            #endif // HAPTIC
        }
        return false;
    #endif
// ┌─────────────────────────────────────────────────┐
// │ m o d   m o r p h s                             │
// └─────────────────────────────────────────────────┘
    case KC_COMMA:
         if ((get_mods() & MOD_MASK_SHIFT) ) {
            // shift is already pressed
            if (record->event.pressed) {
                register_code(KC_SEMICOLON);
            } else {
                unregister_code(KC_SEMICOLON);
            }
            // Do not let QMK process the keycode further
            return false;
         }
         break;
    case KC_DOT:
         if ((get_mods() & MOD_MASK_SHIFT) ) {
            if (record->event.pressed) {
                del_mods(MOD_MASK_SHIFT);
                register_code(KC_SEMICOLON);
                set_mods(mod_state);
            } else {
                unregister_code(KC_SEMICOLON);
            }
            // Do not let QMK process the keycode further
            return false;
         }
         break;
// ┌─────────────────────────────────────────────────┐
// │ a u d i o / h a p t i c                         │
// └─────────────────────────────────────────────────┘
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
    if (scrolling_mode) {
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
    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
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
    } else if(qwerty){
        oled_write_P(PSTR("GAMES"), led_state.caps_lock||capsword);
    } else {
        oled_write_P(PSTR("COLMAK"), led_state.caps_lock||capsword);
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

    [_COLEMAK] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
                KC_Q,    KC_W,      KC_F,      KC_P,    KC_G,                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
                GUI_A,    ALT_R,     CTL_S,    SHT_T,    KC_D,                            KC_H,    SHT_N,    CTL_E,    ALT_I,    GUI_O,
            TD(Z_ENT),    KC_X,   KC_C,    KC_V,    KC_B,       KC_NO,   KC_NO,          KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,
         MT(MOD_LALT,KC_ESC),LT(_NUMBERS, KC_TAB),MT(MOD_LCTL,KC_BSPC),   KC_NO,    KC_NO,  LT(_NAV,KC_SPC),OSM(MOD_RSFT) , MO(_SYMBOLS)
    ),
    [_MOUSE] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    SCROLL,KC_MS_BTN2,KC_MS_BTN3,KC_MS_BTN1,_______,                      _______,  _______,  _______,  _______,  _______,
    LCTL(KC_Z),LCTL(KC_X), LCTL(KC_C) ,LCTL(KC_V), _______ ,  _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        KC_RALT,  KC_RSFT,  _______,  _______,   _______,  _______,  _______,  _______
    ),
    [_GAMES] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
    _______,  _______,  _______,  _______,  _______,                       _______,  _______,  _______,  _______,  _______,
    KC_A,     KC_R,     KC_S,     KC_T,     KC_D,                          KC_H,     KC_N,     KC_E,     KC_I,     KC_O,
    _______,  _______,  _______,  _______,  _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,
                        KC_LALT, _______, KC_LCTL,   _______,   _______,   _______,  _______, _______
    ),
    [_REAPER] = LAYOUT_yubitsume(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐

  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______,  _______, _______, TD(P_SPACE), _______,                            _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  _______, TD(S_ALT_S), TD(T_TAKE), TD(D_DELETE),                         _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______,  _______, _______, _______, _______,   _______,                   _______, _______,  _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                     KC_SPC,_______,_______ , _______ ,          _______ ,_______,  _______,_______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
    ),
    [_SYMBOLS] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
            KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
            KC_GRV,  KC_LBRC, KC_LCBR, KC_LPRN,    KC_LT,                         KC_GT,  KC_RPRN,  KC_RCBR,KC_RBRC, KC_BSLS,
            KC_TILDE,  KC_PIPE  , KC_UNDS, KC_MINUS,KC_PLUS ,   KC_MUTE,   KC_MPLY,  KC_NO,  KC_EQL, RSFT(KC_SCLN) ,TD(SCLN_ENT), KC_SLSH,
                                  _______,KC_LALT,  _______,    _______,   _______,  _______,  _______,  _______
    ),
    [_NUMBERS] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_PSLS,KC_7,    KC_8,    KC_9,    KC_MINUS,                            KC_MINUS, KC_7,    KC_8,    KC_9,    KC_PSLS,
            KC_PAST,    KC_4,    KC_5,  KC_6,    KC_PLUS,                            KC_PLUS,    KC_4,    KC_5,  KC_6,    KC_PAST,
            TD(DOT_ENT), KC_1,  KC_2,   KC_3,   KC_SPC,    KC_MPLY,        KC_MPLY,  KC_EQL,   KC_1,     KC_2,     KC_3,   TD(DOT_ENT),
                                  KC_0,    _______, KC_DEL,   _______,   _______,  KC_0, _______, _______
    ),
    [_NAV] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
           KC_PGUP  , KC_HOME, KC_UP,KC_END,  KC_NO ,                            KC_NO,KC_PSCR,  KC_INS,    KC_NO,  KC_NO,
           KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,   KC_DEL,                       QK_CAPS_WORD_TOGGLE,  KC_RSFT, KC_RCTL,  KC_RALT,  KC_ESC,
        LCTL(KC_Z),LCTL(KC_X),LCTL(KC_C),LCTL(KC_V), KC_NO, KC_MUTE,   KC_MPLY,   KC_CAPS,   KC_NO,   KC_NO,    KC_NO,  KC_ENT,
                                  _______,  KC_TAB,_______ ,    _______,   _______,   _______, KC_NO, KC_NO
    ),
    [_ADJUST] = LAYOUT_yubitsume(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
             KC_F9, KC_F10,    KC_F11,   KC_F12, RGB_TOG ,                            RGB_TOG, AU_TOGG,   HF_TOGG,    TG(_REAPER), TG(_GAMES),
            KC_F5, KC_F6,    KC_F7,   KC_F8,  RGB_MOD,                              KC_RALT,  SHT_MPLY, CTL_MSTP, ALT_MPRV,  GUI_MNXT,
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   RGB_RMOD,           KC_MUTE, KC_MPLY,    KC_NO,KC_VOLU, KC_VOLD, KC_MUTE,   _______,
                                 _______,   _______,  _______,     _______,   _______, _______,   _______,   _______
    )

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



