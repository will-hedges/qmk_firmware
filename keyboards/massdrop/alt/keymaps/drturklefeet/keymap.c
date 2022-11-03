#include QMK_KEYBOARD_H

enum layers {
    _QWER,
    _FN1,
    _META
};

#include "macros.c"

#define FN1_CAPS LT(_FN1, KC_CAPS)

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWER] = LAYOUT_65_ansi_blocker(
        KC_ESC,   KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,     KC_8,     KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
        KC_TAB,   KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,     KC_I,     KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, KC_HOME, \
        FN1_CAPS, KC_A,      KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,  KC_PGUP, \
        KC_LSFT,  KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL,  MO(_META), KC_LALT,                            KC_SPC,                               MO(_FN1), KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [_FN1] = LAYOUT_65_ansi_blocker(
        KC_GRV,   KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,  KC_F12,  _______, KC_MUTE, \
        _______,  RGB_SPD,   RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO, U_T_AGCR, _______, KC_PSCR,  KC_SLCK, KC_PAUS, _______, KC_END,  \
        _______,  RGB_RMOD,  RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______,  _______,  _______, _______,  _______,          _______, KC_VOLU, \
        _______,  RGB_TOG,   _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG,  _______,  _______, _______,  _______,          KC_PGUP, KC_VOLD, \
        _______, _______,    RESET,                              _______,                              _______,  _______, KC_HOME, KC_PGDN, KC_END   \
    ),
    [_META] = LAYOUT_65_ansi_blocker(
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______, \
        _______,  _______,   _______, _______, PAP,     _______, _______, COMP_P,   COMP,     COMP_C,  PC_XFER,  _______, _______, _______, _______, \
        _______,  NARR,      _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______,          _______, _______, \
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______,          _______, _______, \
        _______,  _______,   _______,                            _______,                              _______,  _______, _______, _______, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______, \
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, _______, \
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______,          _______, _______, \
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______,          _______, _______, \
        _______,  _______,   _______,                            _______,                              _______,  _______, _______, _______, _______  \
    ),
    */
};
