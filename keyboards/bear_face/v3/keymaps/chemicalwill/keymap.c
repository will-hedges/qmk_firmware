/* Copyright 2024 will-hedges */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

enum layers {
    _QWER,
    _FN1
};

// Tap Dance enum
enum {
    MUTE_F1,
    VOLD_F2,
    VOLU_F3,
    MPRV_F4,
    MPLY_F5,
    MNXT_F6
};

#define FN1_CAPS LT(_FN1, KC_CAPS)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWER] = LAYOUT_83_ansi(
        KC_ESC,   TD(MUTE_F1), TD(VOLD_F2), TD(VOLU_F3), TD(MPRV_F4), TD(MPLY_F5), TD(MNXT_F6), KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_DEL,
        KC_GRV,   KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,   KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_Y,        KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
        FN1_CAPS, KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_H,        KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT,  KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_N,        KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL,  KC_LGUI,     KC_LALT,                               KC_SPC,                                     KC_RALT, MO(_FN1), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN1] = LAYOUT_83_ansi(
        _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CALC, _______,
        _______, _______, _______, _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, KC_APP,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),
};

/*
    [_BLANK] = LAYOUT_83_ansi(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______, _______, _______
    ),
*/


// TAP DANCE tap-vs-hold
// https://docs.qmk.fm/#/feature_tap_dance?id=example-3
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        // list all tap dance keycodes with tap-hold configurations
        case TD(MUTE_F1): case TD(VOLD_F2): case TD(VOLU_F3): case TD(MPRV_F4): case TD(MPLY_F5): case TD(MNXT_F6):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [MUTE_F1] = ACTION_TAP_DANCE_TAP_HOLD(KC_MUTE, KC_F1),
    [VOLD_F2] = ACTION_TAP_DANCE_TAP_HOLD(KC_VOLD, KC_F2),
    [VOLU_F3] = ACTION_TAP_DANCE_TAP_HOLD(KC_VOLU, KC_F3),
    [MPRV_F4] = ACTION_TAP_DANCE_TAP_HOLD(KC_MPRV, KC_F4),
    [MPLY_F5] = ACTION_TAP_DANCE_TAP_HOLD(KC_MPLY, KC_F5),
    [MNXT_F6] = ACTION_TAP_DANCE_TAP_HOLD(KC_MNXT, KC_F6)
};
