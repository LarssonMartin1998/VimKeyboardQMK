#pragma once

#include QMK_KEYBOARD_H

enum mode {
    insert, // low white
    command, // blue
    delete, // red
    change, // red
    //visual, // purple
    //copy
    //replace, // yellow
};

void on_vim_layer_activated(void);
void handle_vim_mode(uint16_t keycode, keyrecord_t* record);

void update_hsv_from_mode(void);

enum mode get_current_mode(void);
void set_current_mode(uint8_t new_mode);

void reset_data(void);
void clear_repeat(void);
bool append_repeat(uint8_t r);

void repeating_tap_code(uint16_t keycode);