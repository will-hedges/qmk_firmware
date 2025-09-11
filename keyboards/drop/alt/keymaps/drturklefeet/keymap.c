#include QMK_KEYBOARD_H

enum layers {
    _QWER,
    _FN1,
    _META
};

#define FN1_CAPS LT(_FN1, KC_CAPS)

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

// ** START MACROS
enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    ARD,
    BHCC,
    BLCC,
    _COMP,
    COMP_C,
    COMP_P,
    ESP,
    NARR,
    PAP,
    PAP2,
    PC_XFER
};

void matrix_init_user(void) {
};
void matrix_scan_user(void) {
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {

        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;

        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                        rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                    }
                    break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                    }
                    break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
            }
            return false;

        case ARD:
            if (record->event.pressed) {
                SEND_STRING("The Ardelyx Medical Information Department (MID) received information from the Ardelyx Assist program regarding a potential adverse event (AE).\n");
                SEND_STRING("Please refer to the attached source document for additional case information.\n\n");
                SEND_STRING("No additional information was available at the time of this report.");
            } else {
            }
            break;

        case BHCC:
            if (record->event.pressed) {
                SEND_STRING("The Bausch Health Medical Information Department (MID) received information from the Bausch Health Customer Care program (BHCC) regarding a potential adverse event (AE).\n");
                SEND_STRING("Please refer to the attached source document for additional case information.\n\n");
                SEND_STRING("No additional information was available at the time of this report.");
            } else {
            }
            break;

        case BLCC:
            if (record->event.pressed) {
                SEND_STRING("The Bausch + Lomb Medical Information Department (MID) received information from the Bausch + Lomb Customer Care program (BLCC) regarding a potential adverse event (AE).\n");
                SEND_STRING("Please refer to the attached source document for additional case information.\n\n");
                SEND_STRING("No additional information was available at the time of this report.\n");
            } else {
            }
            break;

        case _COMP:
            if (record->event.pressed) {
                SEND_STRING("Was unable to provide the off-label disclaimer to the customer because the customer was not directly contacted.");
            } else {
            }
            break;

        case COMP_C:
            if (record->event.pressed) {
                SEND_STRING("Informed customer that the inquiry is outside of the current labeling for product and flagged inquiry as off-label as per Compliance and referred the customer to their Health Care provider.");
            } else {
            }
            break;

        case COMP_P:
            if (record->event.pressed) {
                SEND_STRING("Informed customer that the inquiry is outside of the current labeling for product and flagged inquiry as off-label as per Compliance.");
            } else {
            }
            break;

        case ESP:
            if (record->event.pressed) {
                SEND_STRING("The Esperion Call Center received notification from a pharmacist calling on behalf of the ASPN Pharmacy Support Program.\n");
                SEND_STRING("The pharmacist shared the following:\n");
                SEND_STRING("No additional information was available at the time of this report.\n");
            } else {
            }
            break;

        case NARR:
            if (record->event.pressed) {
                SEND_STRING("Please refer to the attached source document for more information.\n");
                SEND_STRING("Per the agent from  BHPAP:\n");
                SEND_STRING("The reporter was warm-transferred via phone to MID. Per the reporter:\n");
                SEND_STRING("No additional information was available at the time of this report.\n");
            } else {
            }
            break;

        case PAP:
            if (record->event.pressed) {
                SEND_STRING("CF: customer was triaged to Patient Assistance program for consultation.");
            } else {
            }
            break;

        case PAP2:
            if (record->event.pressed){
                SEND_STRING("The Bausch Health Medical Information Department (MID) received information from the Bausch Health Patient Assistance Program (PAP) regarding a potential adverse event (AE).\n");
                SEND_STRING("Please refer to the attached source document for more information.\n\n");
                SEND_STRING("Per the agent from  BHPAP:\n\n");
                SEND_STRING("No additional information was available at the time of this report.");
            } else {
            }
            break;

        case PC_XFER:
            if (record->event.pressed) {
                SEND_STRING("()CF: PC forwarded to Customer care for filing.");
            } else {
            }
            break;
    }
    return true;
};
// ** END MACROS

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
        _______,  RGB_SPD,   RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO, U_T_AGCR, _______, KC_PSCR,  KC_SCRL, KC_PAUS, _______, KC_END,  \
        _______,  RGB_RMOD,  RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______,  _______,  _______, _______,  _______,          _______, KC_VOLU, \
        _______,  RGB_TOG,   _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG,  _______,  _______, _______,  _______,          KC_PGUP, KC_VOLD, \
        _______, _______,    QK_BOOT,                              _______,                            _______,  _______, KC_HOME, KC_PGDN, KC_END   \
    ),
    [_META] = LAYOUT_65_ansi_blocker(
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______, _______, _______, ARD,     \
        _______,  _______,   _______, ESP,     PAP,     _______, _______, COMP_P,   _COMP,    COMP_C,  PC_XFER,  _______, _______, _______, BHCC,    \
        _______,  NARR,      _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______,          _______, PAP2,    \
        _______,  _______,   _______, _______, _______, _______, _______, _______,  _______,  _______, _______,  _______,          _______, BLCC,    \
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
