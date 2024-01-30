// Keycodes to use jis keycode in us keymap

#pragma once

#include "action.h"
#include "quantum_keycodes.h"
#include "features/jtu_custom_keycodes/default/jtu_custom_keycodes.h"

void set_is_windows(bool is_windows);
uint16_t key_conv(uint16_t key_code);
uint8_t reset_mods(void);
void restore_mods(uint8_t mods_bk);
void clean_tap_code(uint16_t key_code);
void move_word_head(bool lshift);
void move_word_end(bool lshift);
void move_line_head(void);
void home(bool lshift);
void end(bool lshift);
void cut(void);
void copy(void);
void paste(void);
void select_word(void);
void select_line(void);
void select_space(bool is_forward);
void surround(uint16_t start_keycode, uint16_t end_keycode, bool need_cut_and_paste, bool is_lang1, bool lshift, keyrecord_t *record);
void duplicate_line(void);
void delete_line(void);
void join_line(void);
void trim(bool is_forward, bool both);
void indent(bool next);
void insert_word_end(uint16_t keycode, bool is_lang1, bool lshift, keyrecord_t *record);
void insert_line_end(uint16_t keycode, bool is_lang1, bool lshift, keyrecord_t *record);
void ime_on(void);
void ime_off(void);
void ime_change_if_needed(bool before, bool after);
