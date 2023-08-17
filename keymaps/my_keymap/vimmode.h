#pragma once

#include QMK_KEYBOARD_H

void update_hsv_from_mode(void);
void on_vim_layer_activated(void);
void handle_vim_mode(uint16_t keycode, keyrecord_t* record);