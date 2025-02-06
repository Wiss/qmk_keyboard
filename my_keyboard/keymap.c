#include <stdio.h>
#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#if __has_include("keymap.h")
#    include "keymap.h"
#endif

enum custom_keycodes {
    CUSTOM_PIPE = SAFE_RANGE,
    CUSTOM_GT,
    CUSTOM_TILDE,
    CUSTOM_DASH,
    CUSTOM_SCLN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case RGB_TOG:
                rgblight_toggle();
                break;
            case RGB_MOD:
                rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
                break;

            case CUSTOM_PIPE:
                if (get_mods() & MOD_MASK_SHIFT) {
                    unregister_mods(MOD_MASK_SHIFT);
                    register_mods(MOD_BIT(KC_RALT));
                    tap_code(KC_1);
                    unregister_mods(MOD_BIT(KC_RALT));
                } else {
                    tap_code16(KC_ESC); // esq
                }
                return false;

            //case CUSTOM_GT:
            //    if (get_mods() & MOD_MASK_SHIFT) {
            //        unregister_mods(MOD_MASK_SHIFT);
            //        tap_code16(KC_GT);
            //        register_mods(MOD_MASK_SHIFT);
            //    } else {
            //        tap_code16(KC_LT);
            //    }
            //    return false;

            //case CUSTOM_SCLN:
            //    if (get_mods() & MOD_MASK_ALT) {
            //        unregister_mods(MOD_MASK_ALT);
            //        tap_code16(KC_TILD);
            //        register_mods(MOD_MASK_ALT);
            //    } else {
            //        tap_code16(KC_SCLN);
            //    }
            //    return false;

            case CUSTOM_DASH:
                if (get_mods() & MOD_MASK_SHIFT) {
                    unregister_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_SLSH);
                } else {
                    register_mods(MOD_MASK_SHIFT);
                    tap_code16(KC_SLSH);
                    unregister_mods(MOD_MASK_SHIFT);
                }
                return false;
        }
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        CUSTOM_PIPE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_EQL,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, MS_WHLD, KC_N, KC_M, KC_COMM, KC_DOT, CUSTOM_DASH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(1), KC_SPC, KC_ENT, MO(2), KC_RALT, KC_PSCR, KC_RCTL
    ),

    [1] = LAYOUT(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV,
        KC_ESC, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSPC,
        KC_TAB, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_NO, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LGUI, KC_LALT, KC_LCTL, KC_TRNS, KC_ENT, KC_SPC, TL_UPPR, KC_RCTL, KC_RALT, KC_RGUI
    ),

    [2] = LAYOUT(
        KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F12,
        KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        KC_NO, KC_EQL, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, KC_TRNS,
        RGB_TOG, RGB_RMOD, RGB_MOD, RGB_M_P, KC_TRNS, KC_TRNS, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN
    ),

    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_INS, KC_PSCR, KC_APP, KC_NO, KC_NO, KC_PGUP, LCTL(KC_LEFT), KC_UP, LCTL(KC_RGHT), LCTL(KC_BSPC), KC_BSPC,
                 KC_TRNS, KC_LALT, KC_LCTL, KC_LSFT, KC_NO, KC_CAPS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_BSPC,
                 KC_TRNS, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_HOME, KC_NO, KC_END, KC_NO, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [4] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        QK_BOOT, KC_NO, PDF(0), PDF(1), CG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, CG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, KC_NO,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#ifdef OTHER_KEYMAP_C
#    include OTHER_KEYMAP_C
#endif
