#pragma once

#include QMK_KEYBOARD_H

enum mode {
    insert, // low white
    command, // blue
    delete, // red
    change, // red
    replace, // red
    yank, // yellow
};

void on_vim_layer_activated(void);
bool handle_vim_mode(uint16_t keycode, keyrecord_t* record);

void update_hsv_from_mode(void);

bool vim_should_cancel_insert(void);
void vim_cancel_insert(void);
uint8_t get_current_mode(void);
void set_current_mode(uint8_t new_mode);
void set_current_mode_without_hsv(uint8_t new_mode);

bool is_command_inside(void);
void activate_inside_mode_for_next_command(void);

void reset_data(void);
void clear_repeat(void);
bool append_repeat(uint8_t r);
uint8_t get_num_repeats(void);
void set_num_repeats(uint8_t r);

void repeating_tap_code(uint16_t keycode);
void repeating_tap_code_with_os_modifier(uint16_t keycode, uint16_t mac_alternative);
void tap_code_with_os_modifier(uint16_t keycode, uint16_t mac_alternative);