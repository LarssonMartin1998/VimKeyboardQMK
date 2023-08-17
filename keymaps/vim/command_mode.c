#include "command_mode.h"

#include "vim_core.h"
#include "delete_mode.h"

#include "layers.h"
#include "utils.h"

void command_enter_change_mode(void);
void command_enter_delete_mode(void);
void command_enter_insert_mode_after(void);
void command_undo(void);
void command_redo(void);

void command_mode_process_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_4:
            command_go_to_end_of_line();
            break;
        case KC_6:
            command_go_to_beginning_of_line();
            break;
        case KC_0:
            command_go_to_beginning_of_line();
            break;
        case KC_A:
            command_enter_insert_mode_after();
            break;
        case KC_I:
            command_enter_insert_mode();
            break;
        case KC_C:
            command_enter_change_mode();
            break;
        case KC_D:
            command_enter_delete_mode();
            break;
        case KC_U:
            command_undo();
            break;
        case KC_R:
            if (is_ctrl_held()) {
                command_redo();
                break;
            }

            // Forward to future replace mode
            break;
        case KC_H:
            command_left();
            break;
        case KC_J:
            command_down();
            break;
        case KC_K:
            command_up();
            break;
        case KC_L:
            command_right();
            break;
        case KC_X:
            // Forward to delete mode as X is a delete command
            delete_mode_process_keycode(keycode);
            break;
        case KC_TAB: // These three commands deviate from Vim, however, it makes the Vim Layer more useful when navigating things outside coding like forms.
            command_enter_insert_mode();
            tap_code(KC_TAB);
            break;
        case KC_SPC: //
            command_enter_insert_mode();
            tap_code(KC_SPC);
            break;
        case KC_ENT: //
            command_enter_insert_mode();
            tap_code(KC_ENT);
            break;
    }
}

void command_enter_change_mode(void) {
    set_current_mode(change);
}

void command_enter_delete_mode(void) {
    set_current_mode(delete);
}

void command_enter_insert_mode(void) {
    set_current_mode(insert);
    layer_off(VIM);
}

void command_enter_insert_mode_after(void) {
    command_right();
    command_enter_insert_mode();
}

void command_go_to_beginning_of_line(void) {
    tap_code(KC_HOME);
}

void command_go_to_end_of_line(void) {
    tap_code(KC_END);
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