#pragma once

#include QMK_KEYBOARD_H

bool goto_vimlayer_process_keycode(uint16_t keycode);
void goto_vimlayer_reset(void);

bool wants_to_go_to_beginning_of_document(void);
bool wants_to_go_to_end_of_document(void);