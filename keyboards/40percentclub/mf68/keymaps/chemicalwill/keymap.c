
#include QMK_KEYBOARD_H

#define _QWER 0
#define _GAME 1
#define _FN1 2

#define FN1_CAPS LT(_FN1, KC_CAPS)

#include "mf68_tap_dances.c"
#include "mf68_macros.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWER] = LAYOUT_68_ansi(
        QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,          NO_INS,  PGUP_HOME,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,  PGDN_END,
        FN1_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,          KC_UP,
        KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, MO(_FN1), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_GAME] = LAYOUT_68_ansi(
        GRV_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC,          KC_INS,  KC_VOLU,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS,          _______, KC_VOLD,
        FN1_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,          _______,
        KC_LCTL,  KC_LGUI, KC_LALT,                   KC_SPC,                                      KC_RALT, MO(_FN1), KC_RCTL,          _______, _______, KC_RGHT
    ),

    [_FN1] = LAYOUT_68_ansi(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_BSPC,          _______, _______,
        _______,  _______, KC_MUTE, _______, _______, _______, _______, _______, KC_UP,   _______,  _______, _______, _______, _______,          _______, _______,
        _______,  KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,          _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,                   _______,          KC_MUTE,
        _______,  _______, _______,                            _______,                             BASE_GM, _______, BASE_QW,          KC_MPRV, KC_MPLY, KC_MNXT
    ),

/*
    [_BLANK] = LAYOUT_68_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______,          _______, _______, _______
    ),
*/
};
