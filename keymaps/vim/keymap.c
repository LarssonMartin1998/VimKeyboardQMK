/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include <process_combo.h>

#include "vim_core.h"
#include "layers.h"
#include "utils.h"

#define COMBO_STRICT_TIMER

#define HSV_FN            95, 255, 255
#define HSV_GAME          30, 255, 255

enum combo_events {
    CHANGE_TO_VIM_LAYER
};

const uint16_t PROGMEM change_to_vim_layer[] = { KC_LCTL, KC_ESC, COMBO_END };

combo_t key_combos[] = {
    [CHANGE_TO_VIM_LAYER] = COMBO_ACTION(change_to_vim_layer)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC] = LAYOUT_iso_83(
    KC_PSCR,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_PGUP,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_END,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
    KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
    KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD, TG(FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN] = LAYOUT_iso_83(
    KC_PSCR,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_PGUP,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_END,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_HOME,
    KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
    KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT, TG(FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[FN] = LAYOUT_iso_83(
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    KC_PSCR,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
    _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
    _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  TO(GAME),  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MUTE,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                                KC_MPLY,                                _______,  _______,  _______,  _______,  _______,  _______),

[GAME] = LAYOUT_iso_83(
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  KC_NO,    _______,                                _______,                                _______,  TG(GAME), _______,  _______,  _______,  _______),

[VIM] = LAYOUT_iso_83(
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                                _______,                                _______,  KC_NO,    _______,  _______,  _______,  _______)
};
void keyboard_post_init_user(void) {
    layer_state_is(MAC);
    rgblight_enable_noeeprom();
    update_hsv_from_mode();
    rgblight_mode_noeeprom(1);
}

void update_tracked_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSFT:
            if (record->event.pressed) {
                set_left_shift_held();
            } else {
                set_left_shift_released();
            }
            break;
        case KC_RSFT:
            if (record->event.pressed) {
                set_right_shift_held();
            } else {
                set_right_shift_released();
            }
            break;
        case KC_LCTL:
            if (record->event.pressed) {
                set_left_ctrl_held();
            } else {
                set_left_ctrl_released();
            }
            break;
        case KC_RCTL:
            if (record->event.pressed) {
                set_right_ctrl_held();
            } else {
                set_right_ctrl_released();
            }
            break;
        case KC_LALT:
            if (record->event.pressed) {
                set_left_alt_held();
            } else {
                set_left_alt_released();
            }
            break;
        case KC_RALT:
            if (record->event.pressed) {
                set_right_alt_held();
            } else {
                set_right_alt_released();
            }
            break;
        case KC_BSPC:
            if (record->event.pressed) {
                set_backspace_held();
            } else {
                set_backspace_released();
            }
            break;
    }
}

bool update_backspace_delete(uint16_t keycode) {
    switch (keycode) {
        case KC_BSPC:
        case KC_LCTL:
            if (is_left_ctrl_held() && is_backspace_held()) {
                unregister_code(KC_BSPC);
                unregister_code(KC_LCTL);
                register_code(KC_DEL);
            } else if (is_backspace_held()) {
                unregister_code(KC_DEL);
                unregister_code(KC_LCTL);
                register_code(KC_BSPC);
            } else if (is_left_ctrl_held()) {
                unregister_code(KC_DEL);
                unregister_code(KC_BSPC);
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_BSPC);
                unregister_code(KC_DEL);
                unregister_code(KC_LCTL);
            }

            return false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_tracked_keys(keycode, record);

    if (layer_state_is(VIM)) {
        handle_vim_mode(keycode, record);
        return false;
    }

    return update_backspace_delete(keycode);
}

void process_combo_event(uint16_t combo_index, bool pressed){
    switch (combo_index) {
        case CHANGE_TO_VIM_LAYER:
            // Shouldn't need to check if vim layer is active since combos are turned off for that layer.
            if (!pressed) {
                return;
            }

            if (layer_state_is(FN)) {
                layer_off(FN);
            }

            layer_on(VIM);

            break;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case MAC:
        case WIN:
            update_hsv_from_mode();
            combo_enable();
            break;
        case FN:
            rgblight_sethsv_noeeprom(HSV_FN);
            combo_enable();
            break;
        case GAME:
            rgblight_sethsv_noeeprom(HSV_GAME);
            combo_disable();
            break;
        case VIM:
            on_vim_layer_activated();
            combo_disable();
            break;
    }

    return state;
}

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? 1 : 0));
    }

    return false;
}

#endif // DIP_SWITCH_ENABLE