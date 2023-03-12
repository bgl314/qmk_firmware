OLED_ENABLE = yes
OLED_DRIVER = SSD1306
ENCODER_ENABLE = yes
EXTRAKEY_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
CONSOLE_ENABLE = no

#HAPTIC FEEBACK
HAPTIC_ENABLE = yes
HAPTIC_DRIVER += DRV2605L

#PER KEY RGB
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix (do not use together with RGBLIGHT_ENABLE)

#AUDIO
AUDIO_ENABLE = yes
MUSIC_ENABLE = yes

# TRACKPAD
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
MOUSEKEY_ENABLE = yes

# need the below in your own rules.mk
TAP_DANCE_ENABLE = yes
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes






