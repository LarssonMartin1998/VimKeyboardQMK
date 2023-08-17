#pragma once

#include QMK_KEYBOARD_H

bool is_mac_os(void);
uint16_t get_os_key(void);

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