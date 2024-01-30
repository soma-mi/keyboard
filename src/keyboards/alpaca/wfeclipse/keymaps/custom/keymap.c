/* Copyright 2023 temp4gh
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
#include "os_detection.h"
#include "features/jtu_custom_keycodes/default/jtu_custom_keycodes.h"
#include "features/casemodes.h"
#include "features/qmk-vim/src/vim.h"

#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif
#include "process_combo.h"
#include "functions.h"

static bool is_windows;
static bool is_lang1;

enum custom_keycodes {
  SIDE_BTN = JTU_SAFE_RANGE + 1,
  SIDE_BTN_2,
  VIM_ON,
  VIM_OFF,
  VIM_TOGGLE,
  COMBI,
  REPEAT_M,
  JIGGLE,
  CAPSWORD,
  SNAKECASE,
  KEBABCASE,
  CAMELCASE,
  COPY,
  PASTE,
  MOVE_HEAD,
  MOVE_TAIL,
  SELECT,
  SURROUND_QUOT,
  SURROUND_PARENTHESES,
  SURROUND_BRACKETS,
  SURROUND_LESS,
  DUPLICARE_OR_DELETE_LINE,
  DELETE_LINE,
  JOIN_LINE,
  TRIM,
  INDENT,
  INSERT_SCLN_TAIL,
  INSERT_COMM_TAIL,
  DELETE_END_WORD,
  DELETE_SUBSEQUENT_LINE,
  ADD_NEXT_LINE,
  DEBUG
};

enum layer_names {
  MAC_BASE,
  WIN_BASE,
  FN,
  MC1,
  MC2,
  DEV
};

// タップダンスの宣言
enum {
  TD_D,
  TD_V,
};

void d(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    clean_tap_code(KC_D);
  } else if (state->count == 2) {
    delete_line();
  }
}

void v(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    clean_tap_code(KC_V);
  } else if (state->count == 2) {
    toggle_vim_mode();
  }
}

// タップダンスの定義
tap_dance_action_t tap_dance_actions[] = {
    [TD_D]  = ACTION_TAP_DANCE_FN(d),
    [TD_V]  = ACTION_TAP_DANCE_FN(v),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [MAC_BASE] =LAYOUT(
    KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_DEL,    KC_GRV,
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       SNAKECASE, CAPSWORD,
    MO(FN),     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,        CAMELCASE, KEBABCASE,
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   OSM(MOD_RSFT), KC_UP,     MO(DEV),
    KC_LCTL,    KC_LALT,       LGUI_T(KC_LNG2),           LT(MC1, KC_SPC),              RGUI_T(KC_LNG1), KC_RALT, KC_HYPR,   KC_LEFT,      KC_DOWN,   KC_RGHT
    ),
  [WIN_BASE] =LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, LCTL_T(KC_LNG2),           KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS
    ),
  [FN] =LAYOUT(
    KC_GRV,  KC_F1,      KC_F2,   KC_F3,   KC_F4,   KC_F5, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12, KC_DEL,        KC_NO,   KC_NO,
    KC_LSFT, KC_NO,      KC_NO,   KC_WH_U, KC_NO,   KC_NO, KC_NO,   KC_HOME, KC_UP,   KC_END,  KC_NO,  KC_NO,  KC_NO,  KC_NO,         KC_NO,   KC_NO,
    KC_NO,   SIDE_BTN_2, KC_WH_L, KC_WH_D, KC_WH_R, KC_NO, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL, KC_NO,          KC_ENT,        KC_NO,   KC_NO,
    KC_LSFT, SIDE_BTN,   KC_NO,   KC_BTN2, KC_NO,   KC_NO, KC_NO,   KC_PGUP, KC_BTN2, KC_PGDN, KC_NO,                  OSM(MOD_RSFT), KC_PGUP, KC_NO,
    KC_LCTL, KC_LALT,    VIM_OFF,                   KC_ENT,              VIM_ON,       KC_RALT, KC_HYPR,            KC_HOME,       KC_PGDN, KC_END
    ),
  [MC1] =LAYOUT(
    KC_NO,   DM_PLY1,   DM_PLY2, KC_NO,                    KC_NO,    KC_NO, KC_NO, KC_NO,     KC_NO,         SURROUND_PARENTHESES, KC_NO, KC_NO,             KC_NO, DELETE_SUBSEQUENT_LINE, DELETE_LINE, KC_NO,
    KC_LSFT, MO(MC2),   SELECT,  MOVE_TAIL,                KC_NO,    KC_NO, KC_NO, KC_NO,     INDENT,        KC_NO,                KC_NO, SURROUND_BRACKETS, KC_NO, KC_NO,                  DM_REC1,     DM_RSTP,
    COMBI,   MOVE_HEAD, KC_NO,   DUPLICARE_OR_DELETE_LINE, KC_NO,    KC_NO, KC_NO, JOIN_LINE, KC_NO,         KC_NO,                KC_NO, SURROUND_QUOT,            ADD_NEXT_LINE,          DM_REC2,     DM_RSTP,
    KC_LSFT, SIDE_BTN,  TRIM,    KC_NO,                    REPEAT_M, MOVE_HEAD, KC_NO, KC_NO, SURROUND_LESS, KC_NO,                KC_NO,                           OSM(MOD_RSFT),          KC_WH_U,     KC_NO,
    KC_LCTL, KC_LALT,   COMBI,                       KC_NO,                    COMBI,    KC_RALT,   KC_HYPR,                                                        KC_WH_L,                KC_WH_D,     KC_WH_R
    ),
  [MC2] =LAYOUT(
    KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO,            KC_NO, KC_NO, DELETE_END_WORD, KC_NO,   KC_NO,
    KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, KC_NO,            KC_NO, KC_NO, KC_NO,           KC_NO,   KC_NO,
    COMBI,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,            KC_NO, INSERT_SCLN_TAIL, KC_NO,        KC_NO,           KC_NO,   KC_NO,
    KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, INSERT_COMM_TAIL, KC_NO, KC_NO,                          OSM(MOD_RSFT),   KC_UP,   KC_NO,
    KC_LCTL, KC_LALT,   COMBI,                       KC_NO,             COMBI, KC_RALT, KC_HYPR,                       KC_LEFT,         KC_DOWN, KC_RGHT
    ),
  [DEV]=LAYOUT(
    KC_NO, TO(MAC_BASE), TO(WIN_BASE),   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, EE_CLR, QK_BOOT,
    KC_NO, KC_NO,    KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO, KC_NO, KC_NO, RGB_TOG, KC_NO,  KC_NO,
    KC_NO, KC_VOLD,  KC_VOLU, KC_MUTE, KC_NO, KC_NO, KC_NO, JIGGLE, KC_NO, KC_NO,  KC_NO, KC_NO,        DEBUG,   KC_NO,  KC_NO,
    KC_NO, KC_BRMD,  KC_BRMU, KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO,  KC_NO,               KC_NO,   KC_NO,  KC_NO,
    KC_NO, KC_NO, KC_NO,                            KC_NO,          KC_NO,  KC_NO, KC_NO,               KC_NO,   KC_NO,  KC_NO
    )
//   [MC2] =LAYOUT(
//     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
//     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
//     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,
//     KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,               KC_TRNS, KC_TRNS, KC_TRNS,                       KC_TRNS, KC_TRNS, KC_TRNS
//     ),
//   [MC2] =LAYOUT(
//     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO,
//     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO,
//     KC_NO, KC_NO, KC_NO,               KC_NO,               KC_NO, KC_NO, KC_NO,               KC_NO, KC_NO, KC_NO
//     ),
};

void keyboard_post_init_user(void) {
  wait_ms(1000);
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    // debug_matrix = true;
    // debug_mouse  = true;
    // debug_keyboard = true;
#endif
  is_windows = detected_host_os() == OS_WINDOWS;
  set_is_windows(is_windows);
  if (is_windows) {
    layer_move(WIN_BASE);
    disable_vim_for_mac();
  } else {
    layer_move(MAC_BASE);
    enable_vim_for_mac();
  }
  is_lang1 = false;
  ime_off();
}

enum combo_events {
  CLEAR_LINE,
};

const uint16_t PROGMEM CLEAR_LINE_combo[] = {KC_BSPC, KC_LSFT, COMBO_END};

combo_t key_combos[] = {
  [CLEAR_LINE] = COMBO_ACTION(CLEAR_LINE_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
  if (!pressed) { return; }

  switch(combo_index) {
    case CLEAR_LINE:
      end(false);
      home(true);
      clean_tap_code(KC_BSPC);
      break;
  }
};

bool terminate_case_modes(uint16_t keycode, const keyrecord_t *record) {
  switch (keycode) {
    // Keycodes to ignore (don't disable caps word)
    case KC_A ... KC_Z:
    case KC_1 ... KC_0:
    case KC_MINS:
    case KC_UNDS:
    case KC_BSPC:
      // If mod chording disable the mods
      if (record->event.pressed && (get_mods() != 0)) {
        return true;
      }
      break;
    default:
      if (record->event.pressed) {
        return true;
      }
      break;
  }
  return false;
}

static bool combi = false;
static uint16_t repeat_keycode;
static uint8_t repeat_mods;
static bool repeat_combi;
static bool repeat_is_lang1;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 以下追加
  // JIGGLER
  if (record->event.pressed) {
    static deferred_token token = INVALID_DEFERRED_TOKEN;
    static report_mouse_t report = {0};
    if (token) {
      // If jiggler is currently running, stop when any key is pressed.
      cancel_deferred_exec(token);
      token = INVALID_DEFERRED_TOKEN;
      report = (report_mouse_t){};  // Clear the mouse.
      host_mouse_send(&report);
    } else if (keycode == JIGGLE) {

      uint32_t jiggler_callback(uint32_t trigger_time, void* cb_arg) {
        // Deltas to move in a circle of radius 20 pixels over 32 frames.
        static const int8_t deltas[32] = {
            0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
            0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
        static uint8_t phase = 0;
        // Get x delta from table and y delta by rotating a quarter cycle.
        report.x = deltas[phase];
        report.y = deltas[(phase + 8) & 31];
        phase = (phase + 1) & 31;
        host_mouse_send(&report);
        return 16;  // Call the callback every 16 ms.
      }

      token = defer_exec(1, jiggler_callback, NULL);  // Schedule callback.
    }
  }

  if (!process_vim_mode(keycode, record)) {
    return false;
  }

  if (!process_case_modes(keycode, record)) {
    return false;
  }

  uint8_t mods_bk = keyboard_report->mods;
  bool combi_bk = combi;
  bool is_lang1_bk = is_lang1;
  if (keycode == REPEAT_M && record->event.pressed) {
    keycode = repeat_keycode;
    combi = repeat_combi;
    is_lang1 = repeat_is_lang1;
    ime_change_if_needed(is_lang1_bk, repeat_is_lang1);
    restore_mods(repeat_mods);
  }
  uint8_t mods = keyboard_report->mods;
  const bool lgui = mods & MOD_BIT(KC_LGUI);
  const bool rgui = mods & MOD_BIT(KC_RGUI);
  const bool lctrl = mods & MOD_BIT(KC_LCTL);
  const bool lshift = mods & MOD_BIT(KC_LSFT);
//   const bool rshift = mods & MOD_BIT(KC_LSFT);
//   const bool lalt = mods & MOD_BIT(KC_LALT);

#ifdef CONSOLE_ENABLE
  printf("KL: kc: %u, col: %u, row: %u, pressed: %u, is_lang1: %u, lshift: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, is_lang1, lshift);
#endif

  switch (keycode) {
    case LGUI_T(KC_LNG2):
      if (!lgui && !record->event.pressed) {
        is_lang1 = false;
      }
      return true;
    case RGUI_T(KC_LNG1):
      if (!rgui && !record->event.pressed) {
        is_lang1 = true;
      }
      return true;
    case LCTL_T(KC_LNG2):
      if (!lctrl && !record->event.pressed) {
        is_lang1 = false;
      }
      return true;
    case VIM_ON:
      if (record->event.pressed) {
        enable_vim_mode();
      }
      return false;
    case VIM_OFF:
      if (record->event.pressed) {
        disable_vim_mode();
      }
      return false;
    case VIM_TOGGLE:
      if (record->event.pressed) {
        toggle_vim_mode();
      }
      return false;
    case COMBI:
      combi = record->event.pressed;
      return false;
    case SIDE_BTN:
      if (record->event.pressed) {
        clear_oneshot_mods();
        reset_mods();
        if (lshift) {
           clean_tap_code(KC_BTN5);
        } else {
           clean_tap_code(KC_BTN4);
        }
        restore_mods(mods_bk);
      }
      return false;
    case SIDE_BTN_2:
      if (record->event.pressed) {
        clear_oneshot_mods();
        reset_mods();
        if (lshift) {
           clean_tap_code(KC_BTN4);
        } else {
           clean_tap_code(KC_BTN5);
        }
        restore_mods(mods_bk);
      }
      return false;
    case CAPSWORD:
      if (record->event.pressed) {
        clear_oneshot_mods();
        reset_mods();
        enable_caps_word();
        restore_mods(mods_bk);
      }
      return false;
    case SNAKECASE:
      if (record->event.pressed) {
        clear_oneshot_mods();
        reset_mods();
        if (lshift) {
          enable_caps_word();
        }
        enable_xcase_with(KC_UNDS);
        restore_mods(mods_bk);
      }
      return false;
    case KEBABCASE:
      if (record->event.pressed) {
        clear_oneshot_mods();
        reset_mods();
        if (lshift) {
          enable_caps_word();
        }
        enable_xcase_with(KC_MINS);
        restore_mods(mods_bk);
      }
      return false;
    case CAMELCASE:
      if (record->event.pressed) {
        clear_oneshot_mods();
        reset_mods();
        enable_xcase_with(OSM(MOD_LSFT));
        if (lshift) {
          set_oneshot_mods(MOD_BIT(KC_LSFT));
        }
        restore_mods(mods_bk);
      }
      return false;
    case COPY:
      if (record->event.pressed) {
        clear_oneshot_mods();

        copy();

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case PASTE:
      if (record->event.pressed) {
        clear_oneshot_mods();

        paste();

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case MOVE_HEAD:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (combi) {
          home(lshift);
        } else {
          move_word_head(lshift);
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case MOVE_TAIL:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (combi) {
          end(lshift);
        } else {
          move_word_end(lshift);
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case SELECT:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (combi) {
          select_line();
        } else {
          select_word();
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case SURROUND_QUOT:
      if (record->event.pressed) {
        clear_oneshot_mods();

        surround(key_conv(KC_QUOT), key_conv(KC_QUOT), combi, is_lang1, lshift, record);

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case SURROUND_PARENTHESES:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (lshift) {
          surround(key_conv(KC_9), key_conv(KC_0), combi, is_lang1, lshift, record);
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case SURROUND_BRACKETS:
      if (record->event.pressed) {
        clear_oneshot_mods();

        surround(key_conv(KC_LBRC), key_conv(KC_RBRC), combi, is_lang1, lshift, record);

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case SURROUND_LESS:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (lshift) {
          surround(key_conv(KC_COMM), key_conv(KC_DOT), combi, is_lang1, lshift, record);
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case DUPLICARE_OR_DELETE_LINE:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (combi) {
          delete_line();
        } else {
          duplicate_line();
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case DELETE_LINE:
      if (record->event.pressed) {
        clear_oneshot_mods();

        delete_line();

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case JOIN_LINE:
      if (record->event.pressed) {
        clear_oneshot_mods();

        join_line();

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case TRIM:
      if (record->event.pressed) {
        clear_oneshot_mods();

        trim(!lshift, combi);

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case INDENT:
      if (record->event.pressed) {
        clear_oneshot_mods();

        indent(combi);

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case INSERT_SCLN_TAIL:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (combi) {
          insert_line_end(key_conv(KC_SCLN), is_lang1, lshift, record);
          clean_tap_code(KC_RGHT);
        } else {
          insert_word_end(key_conv(KC_SCLN), is_lang1, lshift, record);
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case INSERT_COMM_TAIL:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (combi) {
          insert_line_end(key_conv(KC_COMM), is_lang1, lshift, record);
          clean_tap_code(KC_RGHT);
        } else {
          insert_word_end(key_conv(KC_COMM), is_lang1, lshift, record);
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case DELETE_END_WORD:
      if (record->event.pressed) {
        clear_oneshot_mods();

        if (combi) {
          end(false);
          clean_tap_code(KC_BSPC);
        } else {
          move_word_end(false);
          clean_tap_code(KC_DEL);
        }

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case DELETE_SUBSEQUENT_LINE:
      if (record->event.pressed) {
        clear_oneshot_mods();

        end(true);
        clean_tap_code(KC_BSPC);

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case ADD_NEXT_LINE:
      if (record->event.pressed) {
        clear_oneshot_mods();

        end(false);
        clean_tap_code(KC_ENTER);

        repeat_keycode = keycode;
        repeat_mods = mods;
        repeat_combi = combi;
        repeat_is_lang1 = is_lang1;
        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
        ime_change_if_needed(repeat_is_lang1, is_lang1_bk);
      }
      return false;
    case DEBUG:
      if (record->event.pressed) {
        clear_oneshot_mods();

        ime_change_if_needed(is_lang1, false);

        char s[300] = "";
        strcat(s, "is_windows: ");
        strcat(s, is_windows ? "true" : "false");
        strcat(s, "\n");

        strcat(s, "is_lang1: ");
        strcat(s, is_lang1 ? "true" : "false");
        strcat(s, "\n");

        strcat(s, "repeat_is_lang1: ");
        strcat(s, repeat_is_lang1 ? "true" : "false");
        strcat(s, "\n");

        strcat(s, "repeat_combi: ");
        strcat(s, repeat_combi ? "true" : "false");
        strcat(s, "\n");

        send_string(s);

        ime_change_if_needed(false, is_lang1);

        restore_mods(mods_bk);
        combi = combi_bk;
        is_lang1 = is_lang1_bk;
      }
      return false;
    default:
      if (!process_record_user_jtu(key_conv(keycode), record)) {
        return false;
      }
      break;

  }
  return true;
}

bool process_normal_mode_user(uint16_t key_code, const keyrecord_t *record) {
    switch (key_code) {
      case KC_SLSH:
        if (record->event.pressed) {
          if (is_windows) {
            tap_code16(C(KC_F));
          } else {
            tap_code16(G(KC_F));
          }
        }
        return false;
      case KC_ESC:
        if (record->event.pressed) {
          disable_vim_mode();
          tap_code16(key_code);
          enable_vim_mode();
        }
        return false;
    }
    return true;
}

bool process_insert_mode_user(uint16_t key_code, const keyrecord_t *record) {
    // uint8_t mods = keyboard_report->mods;
    // const bool lgui = mods & MOD_BIT(KC_LGUI);
    // const bool rgui = mods & MOD_BIT(KC_RGUI);
    // const bool lctrl = mods & MOD_BIT(KC_LCTL);
    // const bool lshift = mods & MOD_BIT(KC_LSFT);
    switch (key_code) {
      case KC_ESC:
        if (record->event.pressed) {
          disable_vim_mode();
          tap_code16(key_code);
          enable_vim_mode();
        }
        return false;
    }
    return true;
}
