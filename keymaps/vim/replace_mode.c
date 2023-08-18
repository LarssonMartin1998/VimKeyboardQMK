#include "replace_mode.h"

#include "vim_core.h"

bool exit_mode_after_once_char = false;

void replace_mode_process_keycode(uint16_t keycode) {
    if (!exit_mode_after_once_char || keycode == KC_INS) {
        return;
    }

    switch (keycode) {
        case KC_GRV:
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
        case KC_0:
        case KC_MINS:
        case KC_EQL:
        case KC_TAB:
        case KC_Q:
        case KC_W:
        case KC_E:
        case KC_R:
        case KC_T:
        case KC_Y:
        case KC_U:
        case KC_I:
        case KC_O:
        case KC_P:
        case KC_LBRC:
        case KC_RBRC:
        case KC_A:
        case KC_S:
        case KC_D:
        case KC_F:
        case KC_G:
        case KC_H:
        case KC_J:
        case KC_K:
        case KC_L:
        case KC_SCLN:
        case KC_QUOT:
        case KC_NUHS:
        case KC_ENT:
        case KC_NUBS:
        case KC_Z:
        case KC_X:
        case KC_C:
        case KC_V:
        case KC_B:
        case KC_N:
        case KC_M:
        case KC_COMM:
        case KC_DOT:
        case KC_SLSH:
        case KC_SPC:
        case KC_PSLS:
        case KC_PAST:
        case KC_PMNS:
        case KC_PPLS:
        case KC_PENT:
        case KC_P1:
        case KC_P2:
        case KC_P3:
        case KC_P4:
        case KC_P5:
        case KC_P6:
        case KC_P7:
        case KC_P8:
        case KC_P9:
        case KC_P0:
        case KC_PDOT:
        case KC_PEQL:
        case KC_PCMM:
        case KC_KP_EQUAL_AS400:
        case KC_INT1:
        case KC_INT3:
        case KC_INT6:
            // If we get to this point we haven't encountered any issues with the replace one char command.
            // So just let it pass through normally and then reset.
            reset_data();
            break;
    }
}

void replace_mode_reset(void) {
    exit_mode_after_once_char = false;
}

void command_enter_replace_mode_for_one_char(void) {
    set_current_mode(replace);
    exit_mode_after_once_char = true;
}