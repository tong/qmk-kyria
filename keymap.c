#include <stdint.h>
#include QMK_KEYBOARD_H
#include <keymap_german.h>
#include <stdio.h>
#include <string.h>
#include "keylogger.h"
#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif
#ifdef OLED_ENABLE
#    include "oled.h"
#endif
#ifdef RAW_ENABLE
#    include "raw_hid.h"
#    define RAW_EPSIZE 32
#endif
// #ifdef CONSOLE_ENABLE
//     #include "print.h"
// #endif

/* void keyboard_post_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    debug_mouse=true;
} */

uint8_t mod_state;
// uint16_t copy_paste_timer;

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE,
    ENC_MODE_L,
    ENC_MODE_R,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT_split_3x6_5(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_LSFT, LALT_T(KC_A), LSFT_T(KC_S), LCTL_T(KC_D), LGUI_T(KC_F), KC_G, KC_H, RGUI_T(KC_J), RCTL_T(KC_K), RSFT_T(KC_L), RALT_T(KC_SCLN), RSFT_T(KC_QUOT), LCTL_T(KC_ESC), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ESC, ENC_MODE_L, KC_LGUI, LT(1, KC_ESC), KC_SPC, KC_LALT, MO(1), KC_ENT, MO(2), KC_RALT, ENC_MODE_R),
                                                              [1] = LAYOUT_split_3x6_5(KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_RSFT, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_TRNS, KC_TRNS, ENC_MODE_L, KC_TRNS, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_BSPC, MO(3), KC_TRNS, KC_TRNS),
                                                              [2] = LAYOUT_split_3x6_5(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL, KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS, KC_PIPE, KC_BSLS, KC_UNDS, KC_MINS, KC_QUOT, KC_DQUO, KC_NO, KC_NO, KC_NO, KC_NO, KC_GRV, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_QUES, ENC_MODE_L, KC_LALT, KC_NO, KC_BSPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS),
                                                              [3] = LAYOUT_split_3x6_5(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_TRNS, KC_NO, KC_NO, KC_DEL, KC_INS, KC_HOME, KC_NO, KC_INS, KC_DEL, KC_NO, KC_NO, KC_F12, KC_TRNS, KC_TRNS, KC_END, KC_PGUP, KC_PGDN, KC_HOME, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, KC_ESC, KC_TRNS, KC_LGUI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS)};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

};
#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
/*
#ifdef LEADER_ENABLE
//LEADER_EXTERNS();

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
    */
/*
LEADER_DICTIONARY() {
    leading = false;
    leader_end();
    SEQ_ONE_KEY(KC_F) {
        SEND_STRING("QMK is awesome.");
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
        register_code(KC_LGUI);
        register_code(KC_S);
        unregister_code(KC_S);
        unregister_code(KC_LGUI);
    }
}
}
#endif
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
#ifdef OLED_ENABLE
/*
if (record->event.pressed) {
    set_keylog(keycode, record);
}
*/
#endif
    switch (keycode) {
        case KC_BSPC: {
            static bool delkey_registered;
            if (record->event.pressed) {
                if (mod_state & MOD_MASK_SHIFT) {
                    del_mods(MOD_MASK_SHIFT);
                    register_code(KC_DEL);
                    delkey_registered = true;
                    set_mods(mod_state);
                    break;
                }
            } else {
                if (delkey_registered) {
                    unregister_code(KC_DEL);
                    delkey_registered = false;
                    break;
                }
            }
        }
        /*
        case KC_CCCV:  { // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            return true;
            //break;
        }
        */
#ifdef ENCODER_ENABLE
        /*
        case ENC_MODE_L:
            if (record->event.pressed)
                encoder_cycle_mode(true, (mod_state & MOD_MASK_SHIFT));
            break;
        */
        case ENC_MODE_R:
            if (record->event.pressed) encoder_cycle_mode(false, (mod_state & MOD_MASK_SHIFT));
            break;
            return true;
#endif
    }
    return true;
}
