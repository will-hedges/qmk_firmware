//Custom macro keycodes
enum custom_keycodes {
    BASE_QW = SAFE_RANGE,
    BASE_COE
};

//Macros
/* here's a cool-ass example:
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SWAGGER:
        if (record->event.pressed) {
            // when keycode SWAGGER is pressed
            SEND_STRING("I got the most swag on this corner of the street :sunglasses:!");
        } else {
            // when keycode SWAGGER is released
        }
        break;
    }
    return true;
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BASE_QW:
        if (record->event.pressed) {
            // when keycode BASE_QW is pressed
            set_single_persistent_default_layer(_QWERTY);
        } else {
            // when keycode BASE_QW is released
        }
        break;

        case BASE_COE:
        if (record->event.pressed) {
            // when keycode BASE_GM is pressed
            set_single_persistent_default_layer(_COE);
        } else {
            // when keycode BASE_GM is released
        }
        break;
    }
    return true;
};
