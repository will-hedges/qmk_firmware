/* Copyright 2023 Will Hedges (@will-hedges)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include QMK_KEYBOARD_H

enum layers {
    _WORK,
    _QWER,
    _LOWER,
    _RAISE,
    _FN,
    _META
};

enum custom_keycodes {
    BASE_QWER = SAFE_RANGE,
    BASE_WORK,
    ENT_TGMETA
};

// tap dance enum
enum {
    I_F8,
    Q_F10,
    F_F11,
    J_F12,
    G_END,
    H_HOME,
    MINS_SLSH,
    PLUS_ASTR
};

// mod-taps
#define LS_CAPS LSFT_T(KC_CAPS)
#define RS_ENT RSFT_T(KC_ENT)

// layer-taps
#define FN_F9 LT(_FN, KC_F9)
#define RAISE_PGUP LT(_RAISE, KC_PGUP)
#define LOWER_PGDN LT(_LOWER, KC_PGDN)
#define GUI_META LT(_META, KC_LGUI)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WORK] = LAYOUT_ortho_4x12(
        KC_MUTE, TD(Q_F10), KC_W,    KC_E,  KC_R,       KC_T,      KC_Y,       KC_U,       TD(I_F8), KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,      KC_S,    KC_D,  TD(F_F11),  TD(G_END), TD(H_HOME), TD(J_F12),  KC_K,     KC_L,    KC_SCLN, KC_QUOT,
        LS_CAPS, KC_Z,      KC_X,    KC_C,  KC_V,       KC_B,      KC_N,       KC_M,       KC_COMM,  KC_DOT,  KC_UP,   RS_ENT,
        KC_LCTL, GUI_META,  KC_LALT, FN_F9, LOWER_PGDN, KC_SPC,    KC_SPC,     RAISE_PGUP, KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_QWER] = LAYOUT_ortho_4x12(
        KC_MUTE, KC_Q,     KC_W,    KC_E,    KC_R,       KC_T,    KC_Y,    KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,     KC_S,    KC_D,    KC_F,       KC_G,    KC_H,    KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LS_CAPS, KC_Z,     KC_X,    KC_C,    KC_V,       KC_B,    KC_N,    KC_M,       KC_COMM, KC_DOT,  KC_UP,   RS_ENT,
        KC_LCTL, GUI_META, KC_LALT, MO(_FN), MO(_LOWER), KC_SPC,  KC_SPC,  MO(_RAISE), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LOWER] = LAYOUT_ortho_4x12(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_ESC,  KC_GRV,  _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLSH, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_RAISE] = LAYOUT_ortho_4x12(
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        _______, KC_TILD, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUES, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_FN] = LAYOUT_ortho_4x12(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_F11,  KC_F12,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, _______,
        _______, RESET,   _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [_META] = LAYOUT_ortho_4x12(
        _______,   _______,   _______,   _______, _______, KC_7,   KC_8,   KC_9,   TD(MINS_SLSH), _______, _______, KC_BSPC,
        KC_TAB,    _______,   _______,   _______, _______, KC_4,   KC_5,   KC_6,   TD(PLUS_ASTR), _______, _______, KC_DEL,
        _______,   _______,   _______,   _______, _______, KC_1,   KC_2,   KC_3,   KC_ENT,        _______, KC_UP,   ENT_TGMETA,
        BASE_QWER, TG(_META), BASE_WORK, _______, _______, KC_0,   KC_0,   KC_DOT, KC_ENT,        KC_LEFT, KC_DOWN, KC_RGHT
    ),
};


// TAPPING_TERM_PER_KEY docs @ https://docs.qmk.fm/#/tap_hold?id=tapping-term
//  I like shorter for layer + mod taps
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LS_CAPS: case RS_ENT: case FN_F9: case LOWER_PGDN: case RAISE_PGUP: case GUI_META:
            return 150;
        default:
            return TAPPING_TERM;
    }
}


// tap dance tap vs. hold docs @ https://docs.qmk.fm/#/feature_tap_dance?id=example-3
//  macros are also used with process_record_user @ https://docs.qmk.fm/#/feature_macros?id=using-macros-in-c-keymaps
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        // MACROS
        case BASE_QWER:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWER);
            }
            break;

        case BASE_WORK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WORK);
            }
            break;

        case ENT_TGMETA:
            if (record->event.pressed) {
                tap_code(KC_ENTER);
                layer_invert(_META);
            } else {
            }
            break;

        // TAP DANCES
        case TD(I_F8):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(Q_F10):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(F_F11):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(J_F12):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(G_END):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(H_HOME):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(MINS_SLSH):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;

        case TD(PLUS_ASTR):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            break;
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
    [I_F8] = ACTION_TAP_DANCE_TAP_HOLD(KC_I, KC_F8),
    [Q_F10] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_F10),
    [F_F11] = ACTION_TAP_DANCE_TAP_HOLD(KC_F, KC_F11),
    [J_F12] = ACTION_TAP_DANCE_TAP_HOLD(KC_J, KC_F12),
    [G_END] = ACTION_TAP_DANCE_TAP_HOLD(KC_G, KC_END),
    [H_HOME] = ACTION_TAP_DANCE_TAP_HOLD(KC_H, KC_HOME),
    [MINS_SLSH] = ACTION_TAP_DANCE_TAP_HOLD(KC_MINS, KC_SLSH),
    [PLUS_ASTR] = ACTION_TAP_DANCE_TAP_HOLD(KC_PLUS, KC_ASTR)
};


// ROTARY ENCODER
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool encoder_update_user(uint8_t index, bool clockwise) {

    switch(get_highest_layer(layer_state | default_layer_state)) {

        case _WORK:
            if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    }
                    alt_tab_timer = timer_read();
                    tap_code(KC_TAB);
            } else {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            }
            if (is_alt_tab_active) { // check the time elapsed
                if (timer_elapsed(alt_tab_timer) > 750) {
                    unregister_code(KC_LALT);
                    is_alt_tab_active = false;
                }
            }
            break;

        case _RAISE:
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(C(S(KC_TAB)));
            }
            break;

        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
    return false;
};

// timer function
void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 750) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
};
