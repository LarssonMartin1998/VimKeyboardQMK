#include "command_mode.h"

#include "vim_core.h"
#include "delete_mode.h"
#include "replace_mode.h"
#include "yank_mode.h"
#include "goto_vimlayer.h"

#include "layers.h"
#include "utils.h"

void command_enter_change_mode(void);
void command_enter_delete_mode(void);
void command_enter_yank_mode(void);
void command_enter_insert_mode_at_beginning_of_line(void);
void command_enter_insert_mode_at_end_of_line(void);
void command_enter_insert_mode_after(void);
void command_enter_insert_mode_on_new_line(void);
void command_paste_above(void);
void command_paste(void);
void command_scroll_down(void);
void command_scroll_up(void);
void command_undo(void);
void command_redo(void);
void command_search(void);

void command_mode_process_keycode(uint16_t keycode) {
    if (goto_vimlayer_process_keycode(keycode)) {
        if (wants_to_go_to_beginning_of_document()) {
            command_go_to_beginning_of_document();
        } else if (wants_to_go_to_end_of_document()) {
            command_go_to_end_of_document();
        }

        return;
    }

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
            if (is_shift_held()) {
                command_enter_insert_mode_at_end_of_line();
            } else {
                command_enter_insert_mode_after();
            }
            break;
        case KC_I:
            if (is_shift_held()) {
                command_enter_insert_mode_at_beginning_of_line();
            } else {
                command_enter_insert_mode();
            }
            break;
        case KC_C:
            if (is_shift_held()) {
                delete_mode_process_keycode(keycode);
            } else {
                command_enter_change_mode();
            }
            break;
        case KC_D:
            if (is_shift_held()) {
                delete_mode_process_keycode(keycode);
            } else {
                command_enter_delete_mode();
            }
            break;
        case KC_X:
        case KC_S:
            delete_mode_process_keycode(keycode);
            break;
        case KC_U:
            command_undo();
            break;
        case KC_R:
            if (is_ctrl_held()) {
                command_redo();
                break;
            }
            else {
                if (is_shift_held()) {
                    set_current_mode(replace);
                } else {
                    command_enter_replace_mode_for_one_char();
                }
            }
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
        case KC_W:
            command_go_to_next_word();
            break;
        case KC_B:
            command_go_to_beginning_of_word();
            break;
        case KC_P:
            if (is_shift_held()) {
                command_paste_above();
            } else {
                command_paste();
            }

            break;
        case KC_E:
            if (is_ctrl_held()) {
                command_scroll_down();
            } else {
                command_go_to_end_of_word();
            }
            break;
        case KC_Y:
            if (is_ctrl_held()) {
                command_scroll_up();
            } else {
                command_enter_yank_mode();
            }
            break;
        case KC_O:
            command_enter_insert_mode_on_new_line();
            break;
        case KC_SLSH:
            command_search();
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

void command_enter_yank_mode(void) {
    set_current_mode(yank);
}

void command_enter_insert_mode(void) {
    set_current_mode(insert);
    layer_off(VIM);
}

void command_enter_insert_mode_at_beginning_of_line(void) {
    command_go_to_beginning_of_line();
    command_enter_insert_mode();
}

void command_enter_insert_mode_at_end_of_line(void) {
    command_go_to_end_of_line();
    command_enter_insert_mode();
}

void command_enter_insert_mode_after(void) {
    command_right();
    command_enter_insert_mode();
}

void command_enter_insert_mode_on_new_line(void) {
    const bool make_new_line_above = is_shift_held();
    if (make_new_line_above) {
        command_go_to_beginning_of_line();
    } else {
        command_go_to_end_of_line();
    }

    tap_code(KC_ENT);

    if (make_new_line_above) {
        command_up();
    }

    command_enter_insert_mode();
}

void command_go_to_beginning_of_line(void) {
    if (is_mac_os()) {
        tap_code_with_os_modifier(KC_LEFT, KC_LCMD);
    } else {
        tap_code(KC_HOME);
    }
}

void command_go_to_end_of_line(void) {
    if (is_mac_os()) {
        tap_code_with_os_modifier(KC_RIGHT, KC_LCMD);
    } else {
        tap_code(KC_END);
    }
}

void command_paste_above(void) {
    command_go_to_beginning_of_line();
    tap_code(KC_ENT);
    command_up();
    command_paste();
}

void command_paste(void) {
    register_code(KC_LSFT);
    tap_code(KC_INS);
    unregister_code(KC_LSFT);
}

void command_scroll_down(void) {
    repeating_tap_code(KC_WH_D);
}

void command_scroll_up(void) {
    repeating_tap_code(KC_WH_U);
}

void command_undo(void) {
    const uint16_t os_key = get_os_key(KC_LCMD);
    register_code(os_key);
    repeating_tap_code(KC_Z);
    unregister_code(os_key);
}

void command_redo(void) {
    const uint16_t os_key = get_os_key(KC_LCMD);
    register_code(os_key);

    if (is_mac_os()) {
        register_code(KC_LSFT);
        repeating_tap_code(KC_Z);
        unregister_code(KC_LSFT);
    } else {
        repeating_tap_code(KC_Y);
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

void command_go_to_next_word(void) {
    uint8_t num_repeats = get_num_repeats();
    for (uint8_t i = 0; i < num_repeats; i++) {
        set_num_repeats(2);
        command_go_to_end_of_word();
        command_go_to_beginning_of_word();
    }
}

void command_go_to_beginning_of_word(void) {
    repeating_tap_code_with_os_modifier(KC_LEFT, KC_LOPT);
}

void command_go_to_end_of_word(void) {
    repeating_tap_code_with_os_modifier(KC_RIGHT, KC_LOPT);
}

void command_go_to_beginning_of_document(void) {
    const uint16_t os_key = get_os_key(KC_LCMD);
    register_code(os_key);

    if (is_mac_os()) {
        tap_code(KC_UP);
    } else {
        tap_code(KC_HOME);
    }

    unregister_code(os_key);
    goto_vimlayer_reset();
}

void command_go_to_end_of_document(void) {
    const uint16_t os_key = get_os_key(KC_LCMD);
    register_code(os_key);

    if (is_mac_os()) {
        tap_code(KC_DOWN);
    } else {
        tap_code(KC_END);
    }

    unregister_code(os_key);
    goto_vimlayer_reset();
}

void command_search(void) {
    const uint16_t os_key = get_os_key(KC_LCMD);
    register_code(os_key);
    tap_code(KC_F);
    unregister_code(os_key);
    command_enter_insert_mode();
}