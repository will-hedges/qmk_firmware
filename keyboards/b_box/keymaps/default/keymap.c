// Copyright 2023 chemicalwill (@will-hedges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _SPOTIFY,
    _UGPRO,
    _YOUTUBE
};


// Quad Function Tap-Dance
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    SPOTIFY_L,
    SPOTIFY_R,
    UGPRO_L,
    UGPRO_R,
    YOUTUBE_L,
    YOUTUBE_R
};

td_state_t cur_dance(tap_dance_state_t *state);

void spotify_left_finished(tap_dance_state_t *state, void *user_data);
void spotify_left_reset(tap_dance_state_t *state, void *user_data);
void spotify_right_finished(tap_dance_state_t *state, void *user_data);
void spotify_right_reset(tap_dance_state_t *state, void *user_data);

void ugpro_left_finished(tap_dance_state_t *state, void *user_data);
void ugpro_left_reset(tap_dance_state_t *state, void *user_data);
void ugpro_right_finished(tap_dance_state_t *state, void *user_data);
void ugpro_right_reset(tap_dance_state_t *state, void *user_data);

void youtube_left_finished(tap_dance_state_t *state, void *user_data);
void youtube_left_reset(tap_dance_state_t *state, void *user_data);
void youtube_right_finished(tap_dance_state_t *state, void *user_data);
void youtube_right_reset(tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_SPOTIFY] = LAYOUT_stompbox_1x2(
        TD(SPOTIFY_L),  TD(SPOTIFY_R)
    ),

    [_UGPRO] = LAYOUT_stompbox_1x2(
        TD(UGPRO_L),    TD(UGPRO_R)
    ),

    [_YOUTUBE] = LAYOUT_stompbox_1x2(
        TD(YOUTUBE_L),  TD(YOUTUBE_R)
    )
};


td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        else
            return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed)
            return TD_DOUBLE_TAP;
        else
            return TD_DOUBLE_HOLD;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}


// SPOTIFY LEFT TAP DANCE
static td_tap_t spotify_lefttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void spotify_left_finished(tap_dance_state_t *state, void *user_data) {
    spotify_lefttap_state.state = cur_dance(state);
    switch (spotify_lefttap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code16(KC_MPRV);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_YOUTUBE);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_VOLD);
            break;
        case TD_TRIPLE_HOLD:
            reset_keyboard();
            break;
        default:
            break;
    }
}
void spotify_left_reset(tap_dance_state_t *state, void *user_data) {
    switch (spotify_lefttap_state.state) {
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLD);
            break;
        default:
            break;
    }
    spotify_lefttap_state.state = TD_NONE;
}

// SPOTIFY RIGHT TAP DANCE
static td_tap_t spotify_righttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void spotify_right_finished(tap_dance_state_t *state, void *user_data) {
    spotify_righttap_state.state = cur_dance(state);
    switch (spotify_righttap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_MNXT);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_UGPRO);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_VOLU);
            break;
        default:
            break;
    }
}
void spotify_right_reset(tap_dance_state_t *state, void *user_data) {
    switch (spotify_righttap_state.state) {
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLU);
            break;
        default:
            break;
    }
    spotify_righttap_state.state = TD_NONE;
}

// UGPRO LEFT TAP DANCE
static td_tap_t ugpro_lefttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void ugpro_left_finished(tap_dance_state_t *state, void *user_data) {
    ugpro_lefttap_state.state = cur_dance(state);
    switch (ugpro_lefttap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_SPOTIFY);
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLD);
            break;
        default:
            break;
    }
}
void ugpro_left_reset(tap_dance_state_t *state, void *user_data) {
    switch (ugpro_lefttap_state.state) {
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLD);
            break;
        default:
            break;
    }
    ugpro_lefttap_state.state = TD_NONE;
}

// UGPRO RIGHT TAP DANCE
static td_tap_t ugpro_righttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void ugpro_right_finished(tap_dance_state_t *state, void *user_data) {
    ugpro_righttap_state.state = cur_dance(state);
    switch (ugpro_righttap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_M);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_L);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_YOUTUBE);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_VOLU);
            break;
        default:
            break;
    }
}
void ugpro_right_reset(tap_dance_state_t *state, void *user_data) {
    switch (ugpro_righttap_state.state) {
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLU);
            break;
        default:
            break;
    }
    ugpro_righttap_state.state = TD_NONE;
}

// YOUTUBE LEFT TAP DANCE
static td_tap_t youtube_lefttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void youtube_left_finished(tap_dance_state_t *state, void *user_data) {
    youtube_lefttap_state.state = cur_dance(state);
    switch (youtube_lefttap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_J);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_UGPRO);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(KC_LABK);
            break;
        default:
            break;
    }
}
void youtube_left_reset(tap_dance_state_t *state, void *user_data) {
    switch (youtube_lefttap_state.state) {
        default:
            break;
    }
    youtube_lefttap_state.state = TD_NONE;
}

// YOUTUBE RIGHT TAP DANCE
static td_tap_t youtube_righttap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void youtube_right_finished(tap_dance_state_t *state, void *user_data) {
    youtube_righttap_state.state = cur_dance(state);
    switch (youtube_righttap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_J);
            break;
        case TD_DOUBLE_TAP:
            layer_move(_SPOTIFY);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(KC_RABK);
            break;
        default:
            break;
    }
}
void youtube_right_reset(tap_dance_state_t *state, void *user_data) {
    switch (youtube_righttap_state.state) {
        default:
            break;
    }
    youtube_righttap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [SPOTIFY_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spotify_left_finished, spotify_left_reset),
    [SPOTIFY_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spotify_right_finished, spotify_right_reset),
    [UGPRO_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ugpro_left_finished, ugpro_left_reset),
    [UGPRO_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ugpro_right_finished, ugpro_right_reset),
    [YOUTUBE_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, youtube_left_finished, youtube_left_reset),
    [YOUTUBE_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, youtube_right_finished, youtube_right_reset)
};


// RGBLIGHT LAYERS
const rgblight_segment_t PROGMEM spotify_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 85, 255, 125}
);
const rgblight_segment_t PROGMEM ugpro_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 43, 255, 125}
);
const rgblight_segment_t PROGMEM youtube_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 0, 255, 125}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    spotify_layer,
    ugpro_layer,
    youtube_layer
);


void keyboard_pre_init_kb(void) {
    // address the neopixel
    setPinOutput(GP11);
    writePinHigh(GP11);

    // turn off the anode RGB LED
    setPinInputHigh(GP16);
    setPinInputHigh(GP17);
    setPinInputHigh(GP25);
}


void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
    rgblight_blink_layer(get_highest_layer(layer_state), 30000);
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _SPOTIFY));
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _UGPRO));
    rgblight_set_layer_state(2, layer_state_cmp(state, _YOUTUBE));
    return state;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            // power on the neopixel
            rgblight_blink_layer(get_highest_layer(layer_state), 30000);
        }
    }
