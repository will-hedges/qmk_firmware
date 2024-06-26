#include "quantum.h"

__attribute__((weak))
void matrix_init_kb(void){
    gpio_set_pin_output(F4);
    gpio_write_pin_high(F4);
}

__attribute__((weak))
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        // gpio_write_pin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        gpio_write_pin(F4, !led_state.caps_lock);
    }
    return res;
}
