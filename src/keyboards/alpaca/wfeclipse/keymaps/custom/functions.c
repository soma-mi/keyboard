#include QMK_KEYBOARD_H
#include "functions.h"
#include "features/jtu_custom_keycodes/default/jtu_custom_keycodes.h"

static bool is_windows;

void set_is_windows(bool is_windows_arg) {
  is_windows = is_windows_arg;
}

uint16_t key_conv(uint16_t key_code) {
  if (!is_windows) {return key_code;}

  switch(key_code) {
    case KC_2:
      return JU_2;
    case KC_6:
      return JU_6;
    case KC_7:
      return JU_7;
    case KC_8:
      return JU_8;
    case KC_9:
      return JU_9;
    case KC_0:
      return JU_0;
    case KC_MINS:
      return JU_MINS;
    case KC_EQL:
      return JU_EQL;
    case KC_LBRC:
      return JU_LBRC;
    case KC_RBRC:
      return JU_RBRC;
    case KC_BSLS:
      return JU_BSLS;
    case KC_SCLN:
      return JU_SCLN;
    case KC_QUOT:
      return JU_QUOT;
    case KC_GRV:
      return JU_GRV;
    case KC_CAPS:
      return JU_CAPS;
  }
  return key_code;
}

uint8_t reset_mods(void) {
  uint8_t mods_bk = keyboard_report->mods;
  clear_mods();
  send_keyboard_report();
  return mods_bk;
}

void restore_mods(uint8_t mods_bk) {
  set_mods(mods_bk);
  send_keyboard_report();
}

void clean_tap_code(uint16_t key_code) {
  uint8_t mods_bk = reset_mods();
  tap_code16(key_code);
  restore_mods(mods_bk);
}

void move_word_head(bool lshift) {
  uint8_t mods_bk = reset_mods();
  if (lshift) {
    register_code(KC_LSFT);
  }
  if (is_windows) {
    tap_code16(C(KC_LEFT));
  } else {
    tap_code16(A(KC_LEFT));
  }
  if (lshift) {
    unregister_code(KC_LSFT);
  }
  restore_mods(mods_bk);
}

void move_word_end(bool lshift) {
  uint8_t mods_bk = reset_mods();
  if (lshift) {
    register_code(KC_LSFT);
  }
  if (is_windows) {
    tap_code16(C(KC_RGHT));
  } else {
    tap_code16(A(KC_RGHT));
  }
  if (lshift) {
    unregister_code(KC_LSFT);
  }
  restore_mods(mods_bk);
}

void move_line_head(void) {
  uint8_t mods_bk = reset_mods();
  if(is_windows) {
    end(false);
    tap_code16(KC_RGHT);
    tap_code16(KC_UP);
  } else {
    tap_code16(C(KC_A));
  }
  restore_mods(mods_bk);
}

void home(bool lshift) {
  uint8_t mods_bk = reset_mods();
  if (lshift) {
    register_code(KC_LSFT);
  }
  tap_code16(KC_HOME);
  if (lshift) {
    unregister_code(KC_LSFT);
  }
  restore_mods(mods_bk);
}

void end(bool lshift) {
  uint8_t mods_bk = reset_mods();
  if (lshift) {
    register_code(KC_LSFT);
  }
  tap_code16(KC_END);
  if (lshift) {
    unregister_code(KC_LSFT);
  }
  restore_mods(mods_bk);
}

void cut(void) {
  uint8_t mods_bk = reset_mods();
  if (is_windows) {
    tap_code16(C(KC_X));
  } else {
    tap_code16(G(KC_X));
  }
  restore_mods(mods_bk);
}

void copy(void) {
  uint8_t mods_bk = reset_mods();
  if (is_windows) {
    tap_code16(C(KC_C));
  } else {
    tap_code16(G(KC_C));
  }
  restore_mods(mods_bk);
}

void paste(void) {
  uint8_t mods_bk = reset_mods();
  if (is_windows) {
    tap_code16(C(KC_V));
  } else {
    tap_code16(G(KC_V));
  }
  restore_mods(mods_bk);
}

void select_word(void) {
  uint8_t mods_bk = reset_mods();
  if (is_windows) {
    tap_code16(C(KC_W));
  } else {
    register_code(KC_LALT);
    tap_code16(KC_RGHT);
    tap_code16(KC_LEFT);
    tap_code16(S(KC_RGHT));
    unregister_code(KC_LALT);
  }
  restore_mods(mods_bk);
}

void select_line(void) {
  uint8_t mods_bk = reset_mods();
  move_line_head();
  tap_code16(S(KC_DOWN));
  restore_mods(mods_bk);
}

void select_space(bool is_forward) {
  uint8_t mods_bk = reset_mods();
  if (is_windows) {
    register_code(KC_LCTL);
    tap_code16(is_forward ? S(KC_RGHT) : S(KC_LEFT));
    unregister_code(KC_LCTL);
  } else {
    register_code(KC_LALT);
    tap_code16(is_forward ? S(KC_RGHT) : S(KC_LEFT));
    tap_code16(is_forward ? S(KC_LEFT) : S(KC_RGHT));
    unregister_code(KC_LALT);
  }
  restore_mods(mods_bk);
}

void surround(uint16_t start_keycode, uint16_t end_keycode, bool contains_word, bool is_lang1, bool lshift, keyrecord_t *record) {
  uint8_t mods_bk = reset_mods();
  if (contains_word) {
    select_word();
    tap_code16(KC_LEFT);
  }
  restore_mods(mods_bk);
  if (process_record_user_jtu(start_keycode, record)) {
    tap_code16(lshift ? S(start_keycode) : start_keycode);
  }
  reset_mods();
  if (is_lang1) {
    tap_code16(KC_ENT);
  }
  if (contains_word) {
    move_word_end(false);
  }
  restore_mods(mods_bk);
  if (process_record_user_jtu(end_keycode, record)) {
    tap_code16(lshift ? S(end_keycode) : end_keycode);
  }
  reset_mods();
  if (is_lang1) {
    tap_code16(KC_ENT);
  }
  if (!contains_word) {
    tap_code16(KC_LEFT);
  }
  restore_mods(mods_bk);
};

void duplicate_line(void) {
  uint8_t mods_bk = reset_mods();
  select_line();
  copy();
  move_line_head();
  tap_code16(KC_UP);
  paste();
  restore_mods(mods_bk);
}

void delete_line(void) {
  uint8_t mods_bk = reset_mods();
  select_line();
  tap_code16(KC_DEL);
  restore_mods(mods_bk);
}

void join_line(void) {
  uint8_t mods_bk = reset_mods();
  end(false);
  tap_code16(KC_DEL);
  tap_code16(KC_SPC);
  if (is_windows) {
    tap_code16(C(KC_RGHT));
    tap_code16(C(KC_LEFT));
    tap_code16(RCS(KC_LEFT));
    tap_code16(RCS(KC_RGHT));
  } else {
    tap_code16(A(KC_RGHT));
    tap_code16(A(KC_LEFT));
    tap_code16(LSA(KC_LEFT));
    tap_code16(LSA(KC_RGHT));
  }
  tap_code16(KC_SPC);
  restore_mods(mods_bk);
}

void trim(bool is_forward, bool both) {
  uint8_t mods_bk = reset_mods();
  select_space(is_forward);
  tap_code16(KC_DEL);
  if (both) {
    select_space(!is_forward);
    tap_code16(KC_DEL);
  }
  restore_mods(mods_bk);
}

void indent(bool next) {
  uint8_t mods_bk = reset_mods();
  tap_code16(KC_UP);
  move_line_head();
  select_space(true);
  copy();
  tap_code16(KC_DOWN);
  move_line_head();
  trim(true, false);
  paste();
  if (next) {
    wait_ms(300);
    tap_code16(KC_DOWN);
  }
  restore_mods(mods_bk);
}

void insert_word_end(uint16_t keycode, bool is_lang1, bool lshift, keyrecord_t *record) {
  uint8_t mods_bk = reset_mods();
  move_word_end(false);
  restore_mods(mods_bk);
  if (process_record_user_jtu(keycode, record)) {
    tap_code16(lshift ? S(keycode) : keycode);
  }
  reset_mods();
  if (is_lang1) {
    tap_code16(KC_ENT);
  }
  restore_mods(mods_bk);
}

void insert_line_end(uint16_t keycode, bool is_lang1, bool lshift, keyrecord_t *record) {
  uint8_t mods_bk = reset_mods();
  end(false);
  restore_mods(mods_bk);
  if (process_record_user_jtu(keycode, record)) {
    tap_code16(lshift ? S(keycode) : keycode);
  }
  reset_mods();
  if (is_lang1) {
    tap_code16(KC_ENT);
  }
  restore_mods(mods_bk);
}

void ime_on(void) {
  uint8_t mods_bk = reset_mods();
  tap_code16(KC_LNG1);
  restore_mods(mods_bk);
}

void ime_off(void) {
  uint8_t mods_bk = reset_mods();
  tap_code16(KC_LNG2);
  restore_mods(mods_bk);
}

void ime_change_if_needed(bool before, bool after) {
  if (before != after) {
    if (after) {
      ime_on();
    } else {
      ime_off();
    }
  }
}
