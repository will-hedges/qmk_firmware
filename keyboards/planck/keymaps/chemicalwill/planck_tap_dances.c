typedef struct {
    bool is_press_action;
    int state;
} tap;

// enum tap dance states
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,         //down is tapped twice, but NOT interrupted
    DOUBLE_HOLD = 4,        //down is tapped twice and held
};

// enum tap dances
enum {
    ESC_F10,
    F_F11,
    J_F12,
    M_SF12,
    MINS_SLSH,
    PLUS_ASTR
};

// tap dance functions
int cur_dance (qk_tap_dance_state_t *state);

void esc_finished (qk_tap_dance_state_t *state, void *user_data);
void esc_reset (qk_tap_dance_state_t *state, void *user_data);

void f_finished (qk_tap_dance_state_t *state, void *user_data);
void f_reset (qk_tap_dance_state_t *state, void *user_data);

void j_finished (qk_tap_dance_state_t *state, void *user_data);
void j_reset (qk_tap_dance_state_t *state, void *user_data);

void m_finished (qk_tap_dance_state_t *state, void *user_data);
void m_reset (qk_tap_dance_state_t *state, void *user_data);

void mins_finished (qk_tap_dance_state_t *state, void *user_data);
void mins_reset  (qk_tap_dance_state_t *state, void *user_data);

void plus_finished (qk_tap_dance_state_t *state, void *user_data);
void plus_reset (qk_tap_dance_state_t *state, void *user_data);


// tap dance code
int cur_dance (qk_tap_dance_state_t *state) {

    if (state->count == 1) {
        if (state->interrupted) {
            return SINGLE_TAP;
        } else {
            if (!state->pressed) {
                return SINGLE_TAP;
            } else {
                return SINGLE_HOLD;
            }
        }

    } else if (state->count == 2) {
        if (state->interrupted) {
            return DOUBLE_TAP;
        } else if (state->pressed) {
            return DOUBLE_HOLD;
        } else {
            return DOUBLE_TAP;
        }

    } else {
        return 5;   // return n + 1, where n is your number of tap dance states
    }
};


static tap esctap_state = {
    .is_press_action = true,
    .state = 0
};
void esc_finished (qk_tap_dance_state_t *state, void *user_data) {
    esctap_state.state = cur_dance(state);
    switch (esctap_state.state) {
        case SINGLE_TAP:
            register_code(KC_ESC);
            break;
        case SINGLE_HOLD:
            tap_code(KC_F10);
            break;
    }
};
void esc_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (esctap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_ESC);
            break;
    }
    esctap_state.state = 0;
};


static tap ftap_state = {
    .is_press_action = true,
    .state = 0
};
void f_finished (qk_tap_dance_state_t *state, void *user_data) {
    ftap_state.state = cur_dance(state);
    switch (ftap_state.state) {
        case SINGLE_TAP:
            register_code(KC_F);
            break;
        case SINGLE_HOLD:
            tap_code(KC_F11);
            break;
    }
};
void f_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ftap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_F);
            break;
    }
    ftap_state.state = 0;
};


static tap jtap_state = {
    .is_press_action = true,
    .state = 0
};
void j_finished (qk_tap_dance_state_t *state, void *user_data) {
    jtap_state.state = cur_dance(state);
    switch (jtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_J);
            break;
        case SINGLE_HOLD:
            tap_code(KC_F12);
            break;
    }
};
void j_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (jtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_J);
            break;
    }
    jtap_state.state = 0;
};


static tap mtap_state = {
    .is_press_action = true,
    .state = 0
};
void m_finished (qk_tap_dance_state_t *state, void *user_data) {
    mtap_state.state = cur_dance(state);
    switch (mtap_state.state) {
        case SINGLE_TAP:
            register_code(KC_M);
            break;
        case SINGLE_HOLD:
            tap_code16(S(KC_F12));
            break;
    }
};
void m_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (mtap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_M);
            break;
    }
    mtap_state.state = 0;
};


static tap minstap_state = {
    .is_press_action = true,
    .state = 0
};
void mins_finished (qk_tap_dance_state_t *state, void *user_data) {
    minstap_state.state = cur_dance(state);
    switch (minstap_state.state) {
        case SINGLE_TAP:
            register_code(KC_MINS);
            break;
        case SINGLE_HOLD:
            tap_code(KC_SLSH);
            break;
    }
};
void mins_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (minstap_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_MINS);
            break;
    }
    minstap_state.state = 0;
};

static tap plustap_state = {
    .is_press_action = true,
    .state = 0
};
void plus_finished (qk_tap_dance_state_t *state, void *user_data) {
    plustap_state.state = cur_dance(state);
    switch (plustap_state.state) {
        case SINGLE_TAP:
            register_code16(KC_PLUS);
            break;
        case SINGLE_HOLD:
            tap_code16(KC_ASTR);
            break;
    }
};
void plus_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (plustap_state.state) {
        case SINGLE_TAP:
            unregister_code16(KC_PLUS);
            break;
    }
    plustap_state.state = 0;
};


// tap dance actions
qk_tap_dance_action_t tap_dance_actions[] = {
    [ESC_F10] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_finished, esc_reset),
    [F_F11] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, f_finished, f_reset),
    [J_F12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, j_finished, j_reset),
    [M_SF12] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, m_finished, m_reset),
    [MINS_SLSH] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mins_finished, mins_reset),
    [PLUS_ASTR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, plus_finished, plus_reset)
};


// define tap dance keycodes
#define ESC_F10 TD(ESC_F10)
#define F_F11 TD(F_F11)
#define J_F12 TD(J_F12)
#define M_SF12 TD(M_SF12)
#define MINS_SLSH TD(MINS_SLSH)
#define PLUS_ASTR TD(PLUS_ASTR)
