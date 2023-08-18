//https://blog.codepen.io/2014/02/21/vim-key-bindings/
#include "vim_core.h"

#include "command_mode.h"
#include "delete_mode.h"
#include "yank_mode.h"

#include "layers.h"
#include "utils.h"

uint8_t modes_color_h[] = {
    22,
    147,
    0,
    0,
    81,
    190,
    47
};

uint8_t modes_color_s[] = {
    88,
    255,
    255,
    255,
    255,
    255,
    255,
};

uint8_t modes_color_v[] = {
    90,
    255,
    255,
    255,
    255,
    255,
    255
};

bool command_is_inside = false; // Difficult name, but if 'I' is pressed in delete/change/yank, delete IN word, yank IN word etc
bool is_repeating = false;
uint8_t num_repeats = 1;
enum mode current_mode = insert;

bool try_append_repeat(uint16_t keycode);
void forward_keycode_to_current_mode(uint16_t keycode);

void on_vim_layer_activated(void) {
    num_repeats = 1;
    set_current_mode(command);
    command_left();
}

void handle_vim_mode(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) {
        return;
    }

    if (keycode == KC_ESC) {
        reset_data();
        return;
    }

    if (!try_append_repeat(keycode)) {
        return;
    }

    forward_keycode_to_current_mode(keycode);
}

bool try_append_repeat(uint16_t keycode) {
    bool keycode_needs_handling = true;

    switch (keycode) {
        case KC_1:
            keycode_needs_handling = append_repeat(1);
            break;
        case KC_2:
            keycode_needs_handling = append_repeat(2);
            break;
        case KC_3:
            keycode_needs_handling = append_repeat(3);
            break;
        case KC_4:
            if (is_shift_held()) {
                break; // $ = Go to end of line
            }

            keycode_needs_handling = append_repeat(4);
            break;
        case KC_5:
            keycode_needs_handling = append_repeat(5);
            break;
        case KC_6:
            if (is_shift_held()) {
                break; // Command for go to beginning of line = ^
            }

            keycode_needs_handling = append_repeat(6);
            break;
        case KC_7:
            keycode_needs_handling = append_repeat(7);
            break;
        case KC_8:
            keycode_needs_handling = append_repeat(8);
            break;
        case KC_9:
            keycode_needs_handling = append_repeat(9);
            break;
        case KC_0:
            keycode_needs_handling = append_repeat(0);
            break;
    }

    return keycode_needs_handling;
}

void forward_keycode_to_current_mode(uint16_t keycode) {
    switch (current_mode) {
        case insert:
            break;
        case command:
            command_mode_process_keycode(keycode);
            break;
        case delete:
        case change:
            delete_mode_process_keycode(keycode);
            break;
        case yank:
            yank_mode_process_keycode(keycode);
            break;
    }
}

void update_hsv_from_mode(void) {
    rgblight_sethsv_noeeprom(modes_color_h[current_mode], modes_color_s[current_mode], modes_color_v[current_mode]);
}

enum mode get_current_mode(void) {
    return current_mode;
}

void set_current_mode(uint8_t new_mode) {
    clear_repeat();
    current_mode = new_mode;
    update_hsv_from_mode();
}

bool is_command_inside(void) {
    return command_is_inside;
}

void activate_inside_mode_for_next_command(void) {
    if (command_is_inside) {
        reset_data();
    } else {
        command_is_inside = true;
    }
}

void reset_data(void) {
    command_is_inside = false;
    clear_repeat();
    set_current_mode(command);
}

void clear_repeat(void) {
    num_repeats = 1;
    is_repeating = false;
}

bool append_repeat(uint8_t r) {
    if (!is_repeating && r < 1) {
        return true;
    }

    if (!is_repeating && r > 0) {
        num_repeats = r;
    } else {
        num_repeats = num_repeats * 10 + r;
    }

    is_repeating = true;
    return false;
}

uint8_t get_num_repeats(void) {
    return num_repeats;
}

void set_num_repeats(uint8_t r) {
    num_repeats = r;
}

void repeating_tap_code(uint16_t keycode) {
    for (uint8_t i = 0; i < num_repeats; i++) {
        tap_code(keycode);
    }

    reset_data();
}

void repeating_tap_code_with_os_modifier(uint16_t keycode) {
    register_code(get_os_key());
    for (uint8_t i = 0; i < num_repeats; i++) {
        tap_code(keycode);
    }
    unregister_code(get_os_key());

    reset_data();
}