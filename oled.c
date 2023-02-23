/**/
#ifdef OLED_ENABLE
// #include "keylogger.h"
#include "gfx/ftl.h"
#include "kyria.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifdef ENCODER_ENABLE
#include "encoder.h"
#endif
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

#ifdef WPM_ENABLE
uint16_t wpm;
char wpm_str[4];
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// void oled_render_keylog(void) {
//     //oled_write(keylog_str, false);
//     oled_write(read_keylog(), false);
// }

static void oled_render_status_layer(void) {
    //oled_write_P(PSTR("L"), false);
    uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
    case 0:
        oled_write_P(PSTR("0"), false);
        break;
    case 1:
        oled_write_P(PSTR("1"), false);
        break;
    case 2:
        oled_write_P(PSTR("2"), false);
        break;
    case 3:
        oled_write_P(PSTR("3"), false);
        break;
    case 4:
        oled_write_P(PSTR("4"), false);
        break;
    case 5:
        oled_write_P(PSTR("5"), false);
        break;
    }
}

static void oled_render_status_lock(void) {
    led_t led_usb_state = host_keyboard_led_state();
    // oled_write_P(PSTR("CAPLCK"), led_usb_state.caps_lock);
    // oled_write_P(PSTR("NUMLCK"), led_usb_state.num_lock);
    // oled_write_P(PSTR("SCRLCK"), led_usb_state.scroll_lock);
    if (led_usb_state.caps_lock) {
        oled_write_P(PSTR("CAP"), true);
    }
    if (led_usb_state.num_lock) {
        oled_write_P(PSTR("NUM"), true);
    }
    if (led_usb_state.scroll_lock) {
        oled_write_P(PSTR("SCR"), true);
    }
}

static void oled_render_status_mod(void) {
    uint8_t mods = get_mods() | get_weak_mods();
    oled_write_P(PSTR("CTRL"), (mods & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("SHIFT"), (mods & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("ALT"), (mods & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("GUI"), (mods & MOD_MASK_GUI));
    oled_write_P(PSTR(" "), false);
}

#ifdef ENCODER_ENABLE
static void oled_render_status_encoder(const char *prefix, encoder_mode_t mode) {
    oled_write(prefix, false);
    switch (mode) {
    case ENC_MODE_VOLUME:
        oled_write_P(PSTR("VOL"), false);
        break;
    case ENC_MODE_WORD_NAV:
        oled_write_P(PSTR("WORD"), false);
        break;
    case ENC_MODE_LEFT_RIGHT:
        oled_write_P(PSTR("L/R"), false);
        break;
    case ENC_MODE_UP_DOWN:
        oled_write_P(PSTR("U/D"), false);
        break;
    case ENC_MODE_PAGING:
        oled_write_P(PSTR("PGUP/PGDN"), false);
        break;
    case ENC_MODE_BRIGHTNESS:
        oled_write_P(PSTR("BRUP/BRDN"), false);
        break;
    default:
        oled_write_P(PSTR("?"), false);
    }
}
#endif

#ifdef WPM_ENABLE
static void wpm_update(void) {
    wpm = get_current_wpm();
    wpm_str[3] = '\0';
    wpm_str[2] = '0' + wpm % 10;
    wpm_str[1] = (wpm /= 10) % 10  ? '0' + (wpm) % 10 : (wpm / 10) % 10 ? '0' : ' ';
    wpm_str[0] = wpm / 10 ? '0' + wpm / 10 : ' ';
}
#endif

bool oled_task_user(void) {
    led_t led_usb_state = host_keyboard_led_state();
    if (is_keyboard_master()) {
        oled_invert(led_usb_state.caps_lock);
        oled_render_status_layer();
        oled_write_P(PSTR(" "), false);
        oled_render_status_encoder("EL ", encoder_left_mode);
        oled_render_status_encoder("ER ", encoder_right_mode);
        oled_write_P(PSTR("\n"), false);
        oled_render_status_mod();
        oled_write_P(PSTR("\n"), false);
        oled_render_status_lock();
        oled_write_P(PSTR("\n"), false);
        // oled_write(read_keylogs(), false);
        // oled_write_P(PSTR("\n"), false);
        // oled_write(read_keylog(), false);
        #ifdef WPM_ENABLE
        wpm_update();
        oled_write_P(PSTR("\n"), false);
        oled_write(wpm_str, false);
        #endif
        /*
        for (int ix = 0; ix < 128; ix++) {
            for (int iy = 0; iy < 64; iy++) {
                oled_write_pixel(ix, iy, true);
            }
        }
        */
    } else {
        oled_invert(led_usb_state.caps_lock);
        //oled_render_logo();
        gfx_render_ftl();
        // oled_render_logo();
        //  #ifdef OLED_DRIVER_ENABLE
        //  wpm_update();
        //  oled_render_animation();
        //  #endif
    }
    return false;
}

#endif
