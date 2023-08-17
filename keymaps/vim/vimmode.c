//https://blog.codepen.io/2014/02/21/vim-key-bindings/
#include "vimmode.h"

#include "layers.h"
#include "utils.h"

enum mode {
    insert, // low white
    command, // blue
    delete, // red
    //change, // red
    //visual, // purple
    //replace, // yellow
    //record // green
};

uint8_t modes_color_h[] = {
    22,
    147,
    0,
    0,
    190,
    47,
    105
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

bool is_repeating = false;
uint8_t num_repeats = 1;
enum mode current_mode = insert;

void update_hsv_from_mode(void) {
    rgblight_sethsv_noeeprom(modes_color_h[current_mode], modes_color_s[current_mode], modes_color_v[current_mode]);
}

void set_current_mode(uint8_t new_mode) {
    current_mode = new_mode;
    update_hsv_from_mode();
}

void clear_repeat(void) {
    num_repeats = 1;
    is_repeating = false;
}

bool append_repeat(uint8_t r) {
    if (!is_repeating && r < 1) {
        return false;
    }

    if (!is_repeating && r > 0) {
        num_repeats = r;
    } else {
        num_repeats = num_repeats * 10 + r;
    }

    is_repeating = true;
    return true;
}

void reset_data(void) {
    clear_repeat();
    set_current_mode(command);
}

void command_enter_delete_mode(void) {
    clear_repeat();
    set_current_mode(delete);
}

void repeating_tap_code(uint16_t directional_keycode) {
    for (uint8_t i = 0; i < num_repeats; i++) {
        tap_code(directional_keycode);
    }

    reset_data();
}

void command_erase_left(void) {
    repeating_tap_code(KC_BSPC);
}

void command_erase_right(void) {
    repeating_tap_code(KC_DEL);
}

void command_left(void) {
    repeating_tap_code(KC_LEFT);
}

void command_down(void) {
    repeating_tap_code(KC_DOWN);
}

void command_up(void) {
    repeating_tap_code(KC_UP);
}

void command_right(void) {
    repeating_tap_code(KC_RIGHT);
}

void command_go_to_beginning_of_line(void) {
    tap_code(KC_HOME);
}

void command_go_to_end_of_line(void) {
    tap_code(KC_END);
}

void command_erase_current_row(void) {
    command_go_to_beginning_of_line();
    register_code(KC_LSFT);
    command_go_to_end_of_line();
    unregister_code(KC_LSFT);
    command_erase_right();
}

void command_erase_upwards(void) {
    command_go_to_end_of_line();
    register_code(KC_LSFT);
    command_up();
    command_go_to_beginning_of_line();
    unregister_code(KC_LSFT);
    tap_code(KC_BSPC);
}

void command_erase_downwards(void) {
    command_go_to_beginning_of_line();
    register_code(KC_LSFT);
    command_down();
    command_go_to_end_of_line();
    unregister_code(KC_LSFT);
    tap_code(KC_DEL);
}

void command_undo(void) {
    const uint16_t os_key = get_os_key();
    register_code(os_key);
    tap_code(KC_Z);
    unregister_code(os_key);
}

void command_redo(void) {
    const uint16_t os_key = get_os_key();
    register_code(os_key);

    if (is_mac_os()) {
        register_code(KC_LSFT);
        tap_code(KC_Z);
        unregister_code(KC_LSFT);
    } else {
        tap_code(KC_Y);
    }

    unregister_code(os_key);
}

void command_enter_insert(void) {
    set_current_mode(insert);
    layer_off(VIM);
}

void command_enter_insert_after(void) {
    command_right();
    command_enter_insert();
}

void process_command_from_keycode(uint16_t keycode) {
    switch(keycode) {
        case KC_1:
            append_repeat(1);
            break;
        case KC_2:
            append_repeat(2);
            break;
        case KC_3:
            append_repeat(3);
            break;
        case KC_4:
            append_repeat(4);
            break;
        case KC_5:
            append_repeat(5);
            break;
        case KC_6:
            append_repeat(6);
            break;
        case KC_7:
            append_repeat(7);
            break;
        case KC_8:
            append_repeat(8);
            break;
        case KC_9:
            append_repeat(9);
            break;
        case KC_0:
            if (append_repeat(0)) {
                break;
            }

            command_go_to_beginning_of_line();
            break;
        case KC_A:
            command_enter_insert_after();
            break;
        case KC_I:
            command_enter_insert();
            break;
        case KC_X:

            break;
        case KC_D:
            switch (current_mode) {
                case insert:
                    break;
                case command:
                    command_enter_delete_mode();
                    break;
                case delete:
                    command_erase_current_row();
                    break;
            }
            break;
        case KC_U:
            switch (current_mode) {
                case insert:
                    break;
                case command:
                    command_undo();
                    break;
                case delete:
                    reset_data();
                    break;
            }
            break;
        case KC_R:
            break;
        case KC_H:
            switch (current_mode) {
                case insert:
                    break;
                case command:
                    command_left();
                    break;
                case delete:
                    command_erase_left();
                    break;
            }
            break;
        case KC_J:
            switch (current_mode) {
                case insert:
                    break;
                case command:
                    command_down();
                    break;
                case delete:
                    command_erase_downwards();
                    break;
            }
            break;
        case KC_K:
            switch (current_mode) {
                case insert:
                    break;
                case command:
                    command_up();
                    break;
                case delete:
                    command_erase_upwards();
                    break;
            }
            break;
        case KC_L:
            switch (current_mode) {
                case insert:
                    break;
                case command:
                    command_right();
                    break;
                case delete:
                    command_erase_right();
                    break;
            }
            break;
    }
}

void on_vim_layer_activated(void) {
    num_repeats = 1;
    set_current_mode(command);
    command_left();
}

void handle_vim_mode(uint16_t keycode, keyrecord_t* record) {
    if (!record->event.pressed) {
        return;
    }

    process_command_from_keycode(keycode);
}