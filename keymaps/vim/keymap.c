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

#define HSV_FN            87, 205, 110 // green
#define HSV_GAME          197, 205, 110 // purple

enum combo_events {
    CHANGE_TO_VIM_LAYER
};

const uint16_t PROGMEM change_to_vim_layer[] = { KC_LCTL, KC_ESC, COMBO_END };

combo_t key_combos[] = {
    [CHANGE_TO_VIM_LAYER] = COMBO_ACTION(change_to_vim_layer)
};

uint16_t prev_layer = MAC;
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC] = LAYOUT_iso_83(
    KC_PSCR,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_PGUP,
    KC_NUBS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_END,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
    KC_LSFT,  KC_GRV,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
    KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  TG(FN),   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN] = LAYOUT_iso_83(
    KC_INS,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_PGUP,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_END,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
    KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
    KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  TG(FN),   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[VIM] = LAYOUT_iso_83(
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                                _______,                                _______,  TG(FN),    _______,  _______,  _______,  _______),

[FN] = LAYOUT_iso_83(
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    KC_PSCR,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
    _______,  KC_BTN1,  KC_MS_U,  KC_BTN2,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
    _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  _______,  TO(GAME), KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MUTE,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,                                KC_MPLY,                                _______,  _______,  _______,  _______,  _______,  _______),

[GAME] = LAYOUT_iso_83(
    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  KC_NO,    _______,                                _______,                                _______,  TG(GAME), _______,  _______,  _______,  _______)

};

void keyboard_post_init_user(void) {
    layer_state_is(MAC);
    rgblight_enable_noeeprom();
    update_hsv_from_mode();
    rgblight_mode_noeeprom(1);
}

bool try_register_function_key(uint16_t keycode, keyrecord_t *record) {
    if (!is_ctrl_held()) {
        return false;
    }

    uint16_t code_to_tap = 0;
    switch (keycode) {
        case KC_1:
            code_to_tap = KC_F1;
            break;
        case KC_2:
            code_to_tap = KC_F2;
            break;
        case KC_3:
            code_to_tap = KC_F3;
            break;
        case KC_4:
            code_to_tap = KC_F4;
            break;
        case KC_5:
            code_to_tap = KC_F5;
            break;
        case KC_6:
            code_to_tap = KC_F6;
            break;
        case KC_7:
            code_to_tap = KC_F7;
            break;
        case KC_8:
            code_to_tap = KC_F8;
            break;
        case KC_9:
            code_to_tap = KC_F9;
            break;
        case KC_0:
            code_to_tap = KC_F10;
            break;
        case KC_MINS:
            code_to_tap = KC_F11;
            break;
        case KC_EQL:
            code_to_tap = KC_F12;
            break;
        default:
            return false;
    }

    bool was_left_ctrl_held = is_left_ctrl_held();
    bool was_right_ctrl_held = is_right_ctrl_held();

    if (was_left_ctrl_held) {
        unregister_code(KC_LCTL);
    }

    if (was_right_ctrl_held) {
        unregister_code(KC_RCTL);
    }

    if (record->event.pressed) {
        register_code(code_to_tap);
    } else {
        unregister_code(code_to_tap);
    }

    if (was_left_ctrl_held) {
        register_code(KC_LCTL);
    }

    if (was_right_ctrl_held) {
        register_code(KC_RCTL);
    }

    return true;
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
    if (!layer_state_is(GAME) && try_register_function_key(keycode, record)) {
        return false;
    }

    update_tracked_keys(keycode, record);

    if (keycode == TG(FN) || keycode == TG(GAME)) {
        return true;
    }

    if (layer_state_is(VIM) && !layer_state_is(FN)) {
        if (handle_vim_mode(keycode, record)) {
            return false;
        }
    } else { // insert key is ignored in VIM, so don't handle it if it's active
        if (keycode == KC_INS) {
            toggle_insert_active_state();
            return true;
        }
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

            if (!layer_state_is(VIM)) {
                layer_on(VIM);
            }
            break;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    return 200;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint16_t curr_layer = get_highest_layer(state);
    switch (curr_layer) {
        case MAC:
        case WIN:
            update_hsv_from_mode();
            combo_enable();
            break;
        case VIM:
            // Don't reinit VIM when coming from FN layer as we want to be able to switch between VIM & FN seamlessly.
            if (prev_layer != FN) {
                on_vim_layer_activated();
            } else {
                update_hsv_from_mode();
            }

            if (is_insert_active()) {
                tap_insert_and_update_active_state();
            }

            combo_disable();
            break;
        case FN:
            rgblight_sethsv_noeeprom(HSV_FN);
            combo_enable();
            break;
        case GAME:
            set_current_mode_without_hsv(insert);
            rgblight_sethsv_noeeprom(HSV_GAME);
            combo_disable();
            break;
    }

    prev_layer = curr_layer;
    return state;
}

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        const uint16_t new_layer = active ? WIN : MAC;
        default_layer_set(1UL << new_layer);

        set_current_mode(insert);
        layer_clear();
        utils_set_default_layer(new_layer);
    }

    return false;
}

#endif // DIP_SWITCH_ENABLE
