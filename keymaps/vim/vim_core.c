//https://blog.codepen.io/2014/02/21/vim-key-bindings/
/*
 * p
 * P
 * entire Yank mode
 * B = b + left
 * J
 */
#include "vim_core.h"

#include "command_mode.h"
#include "delete_mode.h"
#include "replace_mode.h"
#include "yank_mode.h"
#include "goto_vimlayer.h"

#include "layers.h"
#include "utils.h"

uint8_t modes_color_h[] = {
    22,
    147,
    0,
    0,
    0,
    40
};

uint8_t modes_color_s[] = {
    88,
    250,
    241,
    241,
    241,
    255
};

uint8_t modes_color_v[] = {
    110,
    205,
    205,
    205,
    205,
    205
};

bool should_cancel_insert = false;
bool command_is_inside = false; // Difficult name, but if 'I' is pressed in delete/change/yank, delete IN word, yank IN word etc
bool is_repeating = false;
uint8_t num_repeats = 1;
uint8_t current_mode = insert;

bool try_append_repeat(uint16_t keycode);
bool forward_keycode_to_current_mode(uint16_t keycode);
void on_mode_changed(uint8_t prev, uint8_t new);

void on_vim_layer_activated(void) {
    num_repeats = 1;
    set_current_mode(command);

    if (is_insert_active()) {
        tap_insert_and_update_active_state();
    }
}

bool handle_vim_mode(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) {
        return false;
    }

    if (keycode == KC_ESC) {
        reset_data();
        return true;
    }

    if (current_mode != replace && !try_append_repeat(keycode)) {
        return true;
    }

    return forward_keycode_to_current_mode(keycode);
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

bool forward_keycode_to_current_mode(uint16_t keycode) {
    switch (current_mode) {
        case command:
            command_mode_process_keycode(keycode);
            return true;
        case delete:
        case change:
            delete_mode_process_keycode(keycode);
            return true;
        case replace:
            replace_mode_process_keycode(keycode);
            return false;
        case yank:
            yank_mode_process_keycode(keycode);
            return true;
        default:
            return true;
    }
}

void update_hsv_from_mode(void) {
    rgblight_sethsv_noeeprom(modes_color_h[current_mode], modes_color_s[current_mode], modes_color_v[current_mode]);
}

bool vim_should_cancel_insert(void) {
    return should_cancel_insert;
}

void vim_cancel_insert(void) {
    const bool was_left_shift_held = is_left_shift_held();
    const bool was_right_shift_held = is_right_shift_held();
    if (was_left_shift_held) {
        unregister_code(KC_LSFT);
    }

    if (was_right_shift_held) {
        unregister_code(KC_RSFT);
    }

    tap_insert_and_update_active_state();
    should_cancel_insert = false;

    if (was_left_shift_held) {
        register_code(KC_LSFT);
    }

    if (was_right_shift_held) {
        register_code(KC_RSFT);
    }
}

uint8_t get_current_mode(void) {
    return current_mode;
}

void set_current_mode(uint8_t new_mode) {
    clear_repeat();

    uint8_t prev_mode = current_mode;
    current_mode = new_mode;
    on_mode_changed(prev_mode, new_mode);

    update_hsv_from_mode();
}

void on_mode_changed(uint8_t prev, uint8_t new) {
    switch (prev) {
        case replace:
            should_cancel_insert = true;
            break;
        default:
            break;
    }

    switch (new) {
        case replace:
            tap_insert_and_update_active_state();
            break;
        default:
            break;
    }
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
    replace_mode_reset();
    goto_vimlayer_reset();
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

void repeating_tap_code_with_os_modifier(uint16_t keycode, uint16_t mac_alternative) {
    const uint16_t os_key = get_os_key(mac_alternative);
    register_code(os_key);
    for (uint8_t i = 0; i < num_repeats; i++) {
        tap_code(keycode);
    }
    unregister_code(os_key);

    reset_data();
}

void tap_code_with_os_modifier(uint16_t keycode, uint16_t mac_alternative) {
    const uint16_t os_key = get_os_key(mac_alternative);
    register_code(os_key);
    tap_code(keycode);
    unregister_code(os_key);

    reset_data();
}