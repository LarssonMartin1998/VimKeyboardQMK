#include "yank_mode.h"

#include "vim_core.h"
#include "command_mode.h"
#include "delete_mode.h"
#include "goto_vimlayer.h"

#include "utils.h"

void command_yank_line_forwards(void);
void command_yank_line_backwards(void);
void command_yank_upwards(void);
void command_yank_downwards(void);
void command_yank_current_line(void);
void command_yank_left(void);
void command_yank_right(void);
void command_yank_to_next_word(void);
void command_yank_to_beginning_of_word(void);
void command_yank_to_end_of_word(void);
void command_yank_in_word(void);
void command_yank_to_beginning_of_document(void);
void command_yank_to_end_of_document(void);
void perform_copy(void);

void yank_mode_process_keycode(uint16_t keycode) {
    bool performed_command = false;

    if (goto_vimlayer_process_keycode(keycode)) {
        if (wants_to_go_to_beginning_of_document()) {
            performed_command = true;
            command_yank_to_beginning_of_document();
        } else if (wants_to_go_to_end_of_document()) {
            performed_command = true;
            command_yank_to_end_of_document();
        }

        goto skip_switchcase;
    }

    switch (keycode) {
        case KC_4:
            command_yank_line_forwards();
            performed_command = true;
            break;
        case KC_6:
        case KC_0:
            command_yank_line_backwards();
            performed_command = true;
            break;
        case KC_Y:
            command_yank_current_line();
            performed_command = true;
            break;
        case KC_I:
            activate_inside_mode_for_next_command();
            break;
        case KC_H:
            command_yank_left();
            performed_command = true;
            break;
        case KC_J:
            command_yank_downwards();
            performed_command = true;
            break;
        case KC_K:
            command_yank_upwards();
            performed_command = true;
            break;
        case KC_L:
            command_yank_right();
            performed_command = true;
            break;
        case KC_W:
            if (is_command_inside()) {
                command_yank_in_word();
                performed_command = true;
            } else {
                command_yank_to_next_word();
                performed_command = true;
            }

            break;
        case KC_B:
            command_yank_to_beginning_of_word();
            performed_command = true;
            break;
        case KC_E:
            command_yank_to_end_of_word();
            performed_command = true;
            break;
    }

skip_switchcase:
    if (performed_command) {
        reset_data();
    }
}

void command_yank_line_forwards(void) {
    register_code(KC_LSFT);
    command_go_to_end_of_line();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_RIGHT);
}

void command_yank_line_backwards(void) {
    register_code(KC_LSFT);
    command_go_to_beginning_of_line();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_LEFT);
}

void command_yank_upwards(void) {
    command_go_to_end_of_line();
    register_code(KC_LSFT);
    command_up();
    command_go_to_beginning_of_line();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_LEFT);
}

void command_yank_downwards(void) {
    command_go_to_beginning_of_line();
    register_code(KC_LSFT);
    command_down();
    command_go_to_end_of_line();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_RIGHT);
}

void command_yank_current_line(void) {
    command_go_to_beginning_of_line();
    register_code(KC_LSFT);
    command_go_to_end_of_line();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_RIGHT);
}

void command_yank_left(void) {
    register_code(KC_LSFT);
    command_left();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_LEFT);
}

void command_yank_right(void) {
    register_code(KC_LSFT);
    command_right();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_RIGHT);
}

void command_yank_to_next_word(void) {
    register_code(KC_LSFT);
    command_go_to_next_word();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_RIGHT);
}

void command_yank_to_beginning_of_word(void) {
    register_code(KC_LSFT);
    command_go_to_beginning_of_word();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_LEFT);
}

void command_yank_to_end_of_word(void) {
    register_code(KC_LSFT);
    command_go_to_end_of_word();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_RIGHT);
}

void command_yank_in_word(void) {
    set_num_repeats(1);
    command_go_to_end_of_word();
    register_code(KC_LSFT);
    command_go_to_beginning_of_word();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_LEFT);
}

void command_yank_to_beginning_of_document(void) {
    register_code(KC_LSFT);
    command_go_to_beginning_of_document();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_LEFT);
}

void command_yank_to_end_of_document(void) {
    register_code(KC_LSFT);
    command_go_to_end_of_document();
    unregister_code(KC_LSFT);
    perform_copy();
    tap_code(KC_RIGHT);
}

void perform_copy(void) {
    const uint16_t os_key = get_os_key(KC_LCMD);
    register_code(os_key);

    if (is_mac_os()) {
        tap_code(KC_C);
    } else {
        tap_code(KC_INS);
    }

    unregister_code(os_key);
}