enum {
    _SPOTIFY,
    _UGPRO,
    _YOUTUBE
};

//Tap Dance states enum
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

//define tap
typedef struct {
    bool is_press_action;
    int state;
} td_tap_t;

//Tap Dance enums
enum {
    S1_TD,
    S2_TD,
    U1_TD,
    U2_TD,
    Y1_TD,
    Y2_TD,
};

//set up Tap Dance for tap vs. hold
td_state_t cur_dance (qk_tap_dance_state_t *state);

//tap dance functions
void s1_finished (qk_tap_dance_state_t *state, void *user_data);
void s1_reset (qk_tap_dance_state_t *state, void *user_data);

void s2_finished (qk_tap_dance_state_t *state, void *user_data);
void s2_reset (qk_tap_dance_state_t *state, void *user_data);

void u1_finished (qk_tap_dance_state_t *state, void *user_data);
void u1_reset (qk_tap_dance_state_t *state, void *user_data);

void u2_finished (qk_tap_dance_state_t *state, void *user_data);
void u2_reset (qk_tap_dance_state_t *state, void *user_data);

void y1_finished (qk_tap_dance_state_t *state, void *user_data);
void y1_reset (qk_tap_dance_state_t *state, void *user_data);

void y2_finished (qk_tap_dance_state_t *state, void *user_data);
void y2_reset (qk_tap_dance_state_t *state, void *user_data);


/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currently not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustrating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the s1 tap dance.
static td_tap_t s1tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void s1_finished(qk_tap_dance_state_t *state, void *user_data) {
    s1tap_state.state = cur_dance(state);
    switch (s1tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_MPRV);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_YOUTUBE);
        case TD_DOUBLE_HOLD:
            register_code(KC_VOLD);
            break;
        case TD_TRIPLE_HOLD:
            tap_code16(QK_BOOT);
            break;
        default:
            break;
    }
}
void s1_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (s1tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLD);
            break;
        case TD_TRIPLE_HOLD:
            break;
        default:
            break;
    }
    s1tap_state.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the s2 tap dance.
static td_tap_t s2tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void s2_finished(qk_tap_dance_state_t *state, void *user_data) {
    s2tap_state.state = cur_dance(state);
    switch (s2tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_MNXT);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_UGPRO);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_VOLU);
            break;
        default:
            break;
    }
}
void s2_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (s2tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLU);
            break;
        default:
            break;
    }
    s2tap_state.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the u1 tap dance.
static td_tap_t u1tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void u1_finished(qk_tap_dance_state_t *state, void *user_data) {
    u1tap_state.state = cur_dance(state);
    switch (u1tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_BSPC);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_SPOTIFY);
            break;
        default:
            register_code(KC_VOLD);
            break;
    }
}
void u1_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (u1tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLD);
            break;
        default:
            break;
    }
    u1tap_state.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the u2 tap dance.
static td_tap_t u2tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void u2_finished(qk_tap_dance_state_t *state, void *user_data) {
    u2tap_state.state = cur_dance(state);
    switch (u2tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_M);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_L);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_YOUTUBE);
            break;
        case TD_DOUBLE_HOLD:
            register_code(KC_VOLU);
            break;
        default:
            break;
    }
}
void u2_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (u2tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            unregister_code(KC_VOLU);
            break;
        default:
            break;
    }
    u2tap_state.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the y1 tap dance.
static td_tap_t y1tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void y1_finished(qk_tap_dance_state_t *state, void *user_data) {
    y1tap_state.state = cur_dance(state);
    switch (y1tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_J);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_UGPRO);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(KC_LABK);
            break;
        default:
            break;
    }
}
void y1_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (y1tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            break;
        default:
            break;
    }
    y1tap_state.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the y2 tap dance.
static td_tap_t y2tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
void y2_finished(qk_tap_dance_state_t *state, void *user_data) {
    y2tap_state.state = cur_dance(state);
    switch (y2tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_MPLY);
            break;
        case TD_SINGLE_HOLD:
            tap_code(KC_J);
            break;
        case TD_DOUBLE_TAP:
            layer_on(_SPOTIFY);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(KC_RABK);
            break;
        default:
            break;
    }
}
void y2_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (y2tap_state.state) {
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            break;
        default:
            break;
    }
    y2tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [S1_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s1_finished, s1_reset),
    [S2_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s2_finished, s2_reset),
    [U1_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, u1_finished, u1_reset),
    [U2_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, u2_finished, u2_reset),
    [Y1_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, y1_finished, y1_reset),
    [Y2_TD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, y2_finished, y2_reset)
};


#define S1_TD TD(S1_TD)
#define S2_TD TD(S2_TD)
#define U1_TD TD(U1_TD)
#define U2_TD TD(U2_TD)
#define Y1_TD TD(Y1_TD)
#define Y2_TD TD(Y2_TD)
