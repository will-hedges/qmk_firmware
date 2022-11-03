/*
Copyright 2022 chemicalwill <https://github.com/chemicalwill>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "bear_box_tap_dances.c"

#define _SPOTIFY 0
#define _UGPRO 1
#define _YOUTUBE 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_SPOTIFY] = LAYOUT_stomp_1x2(
        S1_TD, S2_TD
    ),
    [_UGPRO] = LAYOUT_stomp_1x2(
        U1_TD, U2_TD
    ),
    [_YOUTUBE] = LAYOUT_stomp_1x2(
        Y1_TD, Y2_TD
    )
};
