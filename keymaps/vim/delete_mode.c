#include "delete_mode.h"

#include "vim_core.h"
#include "command_mode.h"
#include "goto_vimlayer.h"

#include "utils.h"

void command_erase_line_forwards(void);
void command_erase_line_backwards(void);
void command_erase_all_on_current_line(void);
void command_erase_upwards(void);
void command_erase_downwards(void);
void command_erase_current_line(void);
void command_erase_left(void);
void command_erase_to_next_word(void);
void command_erase_to_beginning_of_word(void);
void command_erase_to_end_of_word(void);
void command_erase_in_word(void);
void command_erase_to_beginning_of_document(void);
void command_erase_to_end_of_document(void);

void delete_mode_process_keycode(uint16_t keycode) {
    bool performed_command = false;
    bool is_change_mode = get_current_mode() == change;

    if (goto_vimlayer_process_keycode(keycode)) {
        if (wants_to_go_to_beginning_of_document()) {
            command_erase_to_beginning_of_document();
            performed_command = true;
        } else if (wants_to_go_to_end_of_document()) {
            command_erase_to_end_of_document();
            performed_command = true;
        }

        goto skip_switchcase;
    }

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
            if (is_change_mode && is_shift_held()) {
                reset_data();
                return;
            }

            if (is_shift_held()) {
                command_erase_line_forwards();
                is_change_mode = true;
            } else {
                command_erase_all_on_current_line();
            }

            performed_command = true;
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
            }

            performed_command = true;
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
            command_erase_right();
            performed_command = true;
            break;
        case KC_X:
            if (is_shift_held()) {
                command_erase_left();
            } else {
                command_erase_right();
            }
            break;
        case KC_W:
            if (is_command_inside()) {
                command_erase_in_word();
            } else {
                command_erase_to_next_word();
            }

            performed_command = true;
            break;
        case KC_B:
            command_erase_to_beginning_of_word();
            performed_command = true;
            break;
        case KC_E:
            command_erase_to_end_of_word();
            performed_command = true;
            break;
    }

skip_switchcase:
    if (!performed_command) {
        return;
    }

    if (is_change_mode) {
        command_enter_insert_mode();
    } else {
        reset_data();
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
    const bool was_left_shift_held = is_left_shift_held();
    const bool was_right_shift_held = is_right_shift_held();
    if (was_left_shift_held) {
        unregister_code(KC_LSFT);
    }

    if (was_right_shift_held) {
        unregister_code(KC_RSFT);
    }

    repeating_tap_code(KC_DEL);

    if (was_left_shift_held) {
        register_code(KC_LSFT);
    }

    if (was_right_shift_held) {
        register_code(KC_RSFT);
    }
}

void command_erase_to_next_word(void) {
    register_code(KC_LSFT);
    command_go_to_next_word();
    unregister_code(KC_LSFT);
    command_erase_right();
}

void command_erase_to_beginning_of_word(void) {
    register_code(KC_LSFT);
    command_go_to_beginning_of_word();
    unregister_code(KC_LSFT);
    command_erase_left();
}

void command_erase_to_end_of_word(void) {
    register_code(KC_LSFT);
    command_go_to_end_of_word();
    unregister_code(KC_LSFT);
    command_erase_right();
}

void command_erase_in_word(void) {
    set_num_repeats(1);
    command_go_to_end_of_word();
    register_code(KC_LSFT);
    command_go_to_beginning_of_word();
    unregister_code(KC_LSFT);
    command_erase_left();
}

void command_erase_to_beginning_of_document(void) {
    register_code(KC_LSFT);
    command_go_to_beginning_of_document();
    unregister_code(KC_LSFT);
    command_erase_left();
}

void command_erase_to_end_of_document(void) {
    register_code(KC_LSFT);
    command_go_to_end_of_document();
    unregister_code(KC_LSFT);
    command_erase_right();
}