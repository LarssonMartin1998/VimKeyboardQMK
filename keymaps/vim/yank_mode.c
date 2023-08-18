#include "yank_mode.h"

#include "vim_core.h"

void yank_mode_process_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_I:
            activate_inside_mode_for_next_command();
            break;
    }
}