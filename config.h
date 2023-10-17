/**/
#pragma once

#define TAPPING_TERM 200
#define TAP_CODE_DELAY 10

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250

#define EE_HANDS

//#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 3000

#ifdef ENCODER_ENABLE
#    define ENCODER_DIRECTION_FLIP
// #define ENCODER_RESOLUTION  2
#endif

#ifdef OLED_ENABLE
#   define OLED_DISPLAY_128X64
#   define OLED_BRIGHTNESS 255
#   define OLED_TIMEOUT 30000
#   define OLED_FONT_H "keyboards/splitkb/kyria/keymaps/tong/glcdfont.c"
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_LIMIT_VAL 200
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_SPLIT
#endif

// #define MIDI_BASIC
