#pragma once

#include QMK_KEYBOARD_H

void replace_mode_process_keycode(uint16_t keycode);
void replace_mode_reset(void);

void command_enter_replace_mode_for_one_char(void);