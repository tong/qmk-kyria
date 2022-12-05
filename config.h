#pragma once

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
//#define TAPPING_TERM 200
//#define IGNORE_MOD_TAP_INTERRUPT

#ifdef ENCODER_ENABLE
#define ENCODER_DIRECTION_FLIP
//#define ENCODER_RESOLUTION  2
#endif

#ifdef OLED_ENABLE
#define OLED_DISPLAY_128X64
#define OLED_BRIGHTNESS 255
#define OLED_TIMEOUT 60000
//#define OLED_FADE_OUT
//#define OLED_FADE_OUT_INTERVAL 0x0F
#define OLED_FONT_H "keyboards/splitkb/kyria/keymaps/tong/glcdfont.c"
#endif

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LIMIT_VAL 200
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SPLIT
#endif

