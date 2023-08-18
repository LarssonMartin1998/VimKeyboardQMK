#include "delete_mode.h"

#include "vim_core.h"
#include "command_mode.h"

#include "utils.h"

void command_erase_line_forwards(void);
void command_erase_line_backwards(void);
void command_erase_all_on_current_line(void);
void command_erase_upwards(void);
void command_erase_downwards(void);
void command_erase_current_line(void);
void command_erase_left(void);
void command_erase_right(void);
v

void delete_mode_process_keycode(uint16_t keycode) {
    bool performed_command = false;
    bool is_change_mode = get_current_mode() == change;

    switch (keycode) {
        case KC_4:
            command_erase_line_forwards();
            performed_command = true;
            break;
        case KC_6:
        case KC_0:
            command_erase_line_backwards();
            performed_command = true;
            break;
        case KC_C:
            if (!is_change_mode) {
                reset_data();
                return;
            }

            if (is_shift_held()) {
                is_change_mode = true;
                command_erase_line_forwards();
            } else {
                command_erase_all_on_current_line();
                performed_command = true;
            }
            break;
        case KC_D:
            if (is_change_mode) {
                reset_data();
                return;
            }

            if (is_shift_held()) {
                command_erase_line_forwards();
            } else {
                command_erase_current_line();
                performed_command = true;
            }
            break;
        case KC_I:
            activate_inside_mode_for_next_command();
            break;
        case KC_S:
            is_change_mode = true;
            if (is_shift_held()) {
                command_erase_all_on_current_line();
            } else {
                command_erase_right();
            }

            performed_command = true;
            break;
        case KC_H:
            command_erase_left();
            performed_command = true;
            break;
        case KC_J:
            command_erase_downwards();
            performed_command = true;
            break;
        case KC_K:
            command_erase_upwards();
            performed_command = true;
            break;
        case KC_L:
        case KC_X:
            command_erase_right();
            performed_command = true;
            break;
        case KC_W:
            command_go_to_next_word();
            break;
        case KC_B:
            command_go_to_beginning_of_word();
            break;
        case KC_E:
            command_go_to_end_of_word();
            break;
    }

    if (performed_command && is_change_mode) {
        command_enter_insert_mode();
    }
}

void command_erase_line_forwards(void) {
    register_code(KC_LSFT);
    command_go_to_end_of_line();
    command_erase_left();
    unregister_code(KC_LSFT);
}

void command_erase_line_backwards(void) {
    register_code(KC_LSFT);
    command_go_to_beginning_of_line();
    command_erase_right();
    unregister_code(KC_LSFT);
}

void command_erase_all_on_current_line(void) {
    command_erase_current_line();
    tap_code(KC_ENT);
    command_up();
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
void command_erase_current_line(void) {
    command_go_to_beginning_of_line();
    register_code(KC_LSFT);
    command_go_to_end_of_line();
    unregister_code(KC_LSFT);
    command_erase_right();
}

void command_erase_left(void) {
    repeating_tap_code(KC_BSPC);
}

void command_erase_right(void) {
    repeating_tap_code(KC_DEL);
}