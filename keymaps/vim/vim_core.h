#pragma once

#include QMK_KEYBOARD_H

enum mode {
    insert, // low white
    command, // blue
    delete, // red
    change, // red
    yank, // green
    //visual, // purple
    //replace, // yellow
};

void on_vim_layer_activated(void);
void handle_vim_mode(uint16_t keycode, keyrecord_t* record);

void update_hsv_from_mode(void);

enum mode get_current_mode(void);
void set_current_mode(uint8_t new_mode);

bool is_command_inside(void);
void activate_inside_mode_for_next_command(void);

void reset_data(void);
void clear_repeat(void);
bool append_repeat(uint8_t r);
uint8_t get_num_repeats(void);
void set_num_repeats(uint8_t r);

void repeating_tap_code(uint16_t keycode);
void repeating_tap_code_with_os_modifier(uint16_t keycode);
void tap_code_with_os_modifier(uint16_t keycode);