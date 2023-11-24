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
    COMP,
    COMP_C,
    COMP_P,
    ESP,
    NARR,
    PAP,
    PAP2,
    PC_XFER
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {

        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;

        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;

        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;

        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;

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

        case COMP:
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
