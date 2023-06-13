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


// repurpose the backlight pin for caps lock indicator
#define LED_CAPS_LOCK_PIN A8

#define TAPPING_TERM 250
#define TAPPING_TERM_PER_KEY

#define ENCODERS_PAD_A { A9 }
#define ENCODERS_PAD_B { A10 }

#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 2

// see PR #6907, short delay helps with media key tap_codes from encoders
#define TAP_CODE_DELAY 10
