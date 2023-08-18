#include "goto_vimlayer.h"

#include "vim_core.h"
#include "utils.h"

#define BEGINNING_OF_DOCUMENT_BIT (1 << 0)
#define END_OF_DOCUMENT_BIT (1 << 1)
#define IN_GOTO_MODE_BIT (1 << 2)
unsigned char document_actions_mask = 0x00;

bool is_in_goto_mode(void);

bool goto_vimlayer_process_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_G:
            if (is_shift_held()) {
                if (is_in_goto_mode()) {
                    reset_data();
                } else {
                    document_actions_mask |= END_OF_DOCUMENT_BIT;
                }

                return true;
            } else {
                if (is_in_goto_mode()) {
                    document_actions_mask |= BEGINNING_OF_DOCUMENT_BIT;
                } else {
                    document_actions_mask |= IN_GOTO_MODE_BIT;
                }

                return true;
            }
            break;
    }

    return false;
}

void goto_vimlayer_reset(void) {
    document_actions_mask = 0x00;
}

bool is_in_goto_mode(void) {
    return document_actions_mask & IN_GOTO_MODE_BIT;
}

bool wants_to_go_to_beginning_of_document(void) {
    return document_actions_mask & BEGINNING_OF_DOCUMENT_BIT;
}

bool wants_to_go_to_end_of_document(void) {
    return document_actions_mask & END_OF_DOCUMENT_BIT;
}