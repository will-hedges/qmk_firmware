#include QMK_KEYBOARD_H

#define _QWER 0
#define _WORK 1
#define _FN1 2

#define FN1_CAPS LT(_FN1, KC_CAPS)

#include "g60ble_macros.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWER] = LAYOUT_60_ansi(
        QK_GESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
        FN1_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT,
        KC_LCTL,  KC_LGUI, KC_LALT,                  KC_SPC,                                      KC_RALT, KC_APP,  MO(_FN1), KC_RCTL
    ),

    [_WORK] = LAYOUT_60_ansi(
        QK_GESC,  N1_F1,   N2_F2,   N3_F3,  N4_F4,   N5_F5,   N6_F6,   N7_F7,   N8_F8,   N9_F9,   N0_F10,  MIN_F11, EQL_F12,  KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
        FN1_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
        KC_LSFT,           KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT,
        KC_LCTL,  KC_LGUI, KC_LALT,                  KC_SPC,                                      KC_RALT, KC_APP,  MO(_FN1), KC_RCTL
    ),

    [_FN1] = LAYOUT_60_ansi(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_DEL,
        _______, _______, KC_PGUP, _______, QK_BOOT, _______, _______, _______, KC_UP,   _______, _______, _______,   _______, _______,
        _______, KC_HOME, KC_PGDN, KC_END,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,            _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______,
        _______, _______, _______,                   _______,                                     _______, DF(_WORK), _______, DF(_QWER)
    )

};
