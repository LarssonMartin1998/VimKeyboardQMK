#include "delete_mode.h"

#include "vim_core.h"
#include "command_mode.h"

#include "utils.h"

void command_erase_all_on_current_row(void);
void command_erase_upwards(void);
void command_erase_downwards(void);
void command_erase_current_row(void);
void command_erase_left(void);
void command_erase_right(void);

void delete_mode_process_keycode(uint16_t keycode) {
    bool performed_command = false;
    bool is_change_mode = get_current_mode() == change;

    switch (keycode) {
        case KC_4:
            // Erase row forwards
            performed_command = true;
            break;
        case KC_6:
            // Erase row backwards
            performed_command = true;
            break;
        case KC_C:
            if (!is_change_mode) {
                reset_data();
                return;
            }

            command_erase_all_on_current_row();
            performed_command = true;
            break;
        case KC_D:
            if (is_change_mode) {
                reset_data();
                return;
            }

            command_erase_current_row();
            performed_command = true;
            break;
        case KC_I:
            activate_inside_mode_for_next_command();
            break;
        case KC_S:
            is_change_mode = true;
            if (is_shift_held()) {
                command_erase_all_on_current_row();
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
    }

    if (performed_command && is_change_mode) {
        command_enter_insert_mode();
    }
}

void command_erase_all_on_current_row(void) {
    command_erase_current_row();
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
void command_erase_current_row(void) {
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