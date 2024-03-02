/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"
#include "os_detection.h"

enum layers
{
  MAC,
  NUM,
  SESSION,
  DEV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC] = LAYOUT_numpad_6x4(
        TO(MAC), TO(NUM), MO(SESSION), MO(DEV),
        HYPR(KC_F10), HYPR(KC_F11), HYPR(KC_F12), LGUI(KC_MINS),
        HYPR(KC_F1), HYPR(KC_UP), HYPR(KC_F2),
        HYPR(KC_F6), HYPR(KC_F5), HYPR(KC_F7), LSG(KC_EQL),
        HYPR(KC_F3), HYPR(KC_DOWN), HYPR(KC_F4),
        HYPR(KC_F8), HYPR(KC_F9), HYPR(KC_ENT)),

    [NUM] = LAYOUT_numpad_6x4(
        TO(MAC), TO(NUM), MO(SESSION), MO(DEV),
        KC_BSPC, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7, KC_P8, KC_P9,
        KC_P4, KC_P5, KC_P6, KC_PPLS,
        KC_P1, KC_P2, KC_P3,
        KC_P0, KC_PDOT, KC_PENT),

    [SESSION] = LAYOUT_numpad_6x4(
        TO(MAC), TO(NUM), MO(SESSION), MO(DEV),
        LCAG(KC_S), LCAG(KC_P), LCAG(KC_F), LCAG(KC_COMM),
        LCAG(KC_B), _______, _______,
        _______, _______, _______, LCAG(KC_DOT),
        _______, _______, _______,
        _______, _______, _______),

    [DEV] = LAYOUT_numpad_6x4(
        TO(MAC), TO(NUM), MO(SESSION), MO(DEV),
        RGB_TOG, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
        EE_CLR, QK_BOOT, _______,
        _______, _______, _______)};

void keyboard_post_init_user(void)
{
  wait_ms(600);
  switch (detected_host_os())
  {
    // case OS_WINDOWS:
    //   layer_move(WIN);
    //   break;
  default:
    layer_move(MAC);
  }
}

void housekeeping_task_user(void)
{
  housekeeping_task_keychron();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (!process_record_keychron(keycode, record))
  {
    return false;
  }
  return true;
}
