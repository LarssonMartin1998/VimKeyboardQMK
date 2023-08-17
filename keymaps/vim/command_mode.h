#pragma once

#include QMK_KEYBOARD_H

void command_mode_process_keycode(uint16_t keycode);

void command_enter_insert_mode(void);
void command_go_to_beginning_of_line(void);
void command_go_to_end_of_line(void);
void command_left(void);
void command_down(void);
void command_up(void);
void command_right(void);