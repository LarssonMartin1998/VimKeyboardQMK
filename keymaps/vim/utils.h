#pragma once

#include <stdint.h>
#include QMK_KEYBOARD_H

void utils_set_default_layer(uint16_t new_default_layer);

bool     is_mac_os(void);
uint16_t get_os_key(uint16_t mac_alternative);

void set_left_shift_held(void);
void set_left_shift_released(void);
bool is_left_shift_held(void);
void set_right_shift_held(void);
void set_right_shift_released(void);
bool is_right_shift_held(void);
bool is_shift_held(void);

void set_left_ctrl_held(void);
void set_left_ctrl_released(void);
bool is_left_ctrl_held(void);
void set_right_ctrl_held(void);
void set_right_ctrl_released(void);
bool is_right_ctrl_held(void);
bool is_ctrl_held(void);

void set_left_alt_held(void);
void set_left_alt_released(void);
bool is_left_alt_held(void);
void set_right_alt_held(void);
void set_right_alt_released(void);
bool is_right_alt_held(void);
bool is_alt_held(void);

void set_backspace_held(void);
void set_backspace_released(void);
bool is_backspace_held(void);

void tap_insert_and_update_active_state(void);
void toggle_insert_active_state(void);
bool is_insert_active(void);

bool is_mod_held(uint16_t keycode);
