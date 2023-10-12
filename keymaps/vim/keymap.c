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

#include <stdint.h>
#include <stdio.h>
#include "action.h"
#include "action_layer.h"
#include "action_util.h"
#include "debug.h"
#include "keycodes.h"
#include "keymap_us.h"
#include "matrix.h"
#include "modifiers.h"
#include QMK_KEYBOARD_H

#include <process_combo.h>

#include "vim_core.h"
#include "layers.h"
#include "utils.h"

#define COMBO_STRICT_TIMER

#define HSV_FN 87, 205, 110    // green
#define HSV_GAME 197, 205, 110 // purple

struct mod_shortcut_group {
    const uint16_t  size;
    const uint16_t  mods[2];
    const uint16_t *sources;
    const uint16_t *others;
};

enum combo_events { CHANGE_TO_VIM_LAYER };

const uint16_t PROGMEM change_to_vim_layer[] = {KC_LCTL, KC_ESC, COMBO_END};

combo_t key_combos[] = {[CHANGE_TO_VIM_LAYER] = COMBO_ACTION(change_to_vim_layer)};

uint16_t prev_layer = MAC;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC] = LAYOUT_iso_83(
    KC_PSCR,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_PGUP,
    KC_NUBS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_HOME,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                      KC_END,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_NUHS,  KC_ENT,             KC_PGDN,
    KC_LSFT,  KC_GRV,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
    KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD,  TG(FN),   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN] = LAYOUT_iso_83(
    KC_PSCR,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_PGUP,
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
// clang-format on

void keyboard_post_init_user(void) {
    layer_state_is(MAC);
    rgblight_enable_noeeprom();
    update_hsv_from_mode();
    rgblight_mode_noeeprom(1);
}

bool process_mod_convert(uint16_t keycode, uint16_t source, uint16_t other, uint16_t lmod, uint16_t rmod) {
    uint16_t valid   = source;
    uint16_t invalid = other;

    const bool is_source_held = is_keycode_pressed(source);
    if (!is_source_held) {
        unregister_code(source);
        unregister_code(other);

        return false;
    }

    const bool should_update = keycode == source || keycode == lmod || keycode == rmod;
    if (should_update) {
        if (is_keycode_pressed(lmod) || is_keycode_pressed(rmod)) {
            invalid = valid;
            valid   = other;
        }

        register_code(valid);
        unregister_code(invalid);

        return true;
    }

    return false;
}

bool process_mod_shortcut_group(uint16_t keycode, const struct mod_shortcut_group *shortcut_group) {
    const uint8_t  num_mods      = 2;
    const uint16_t lmod          = shortcut_group->mods[0];
    const uint16_t rmod          = shortcut_group->mods[1];
    bool           should_update = keycode == lmod || keycode == rmod;
    if (!should_update) {
        for (uint8_t i = 0; i < shortcut_group->size; i++) {
            if (shortcut_group->sources[i] == keycode) {
                should_update = true;
                break;
            }
        }
    }

    if (should_update) {
        for (uint8_t i = 0; i < num_mods; i++) {
            unregister_code(shortcut_group->mods[i]);
        }
    }

    bool result = false;
    for (uint8_t i = 0; i < shortcut_group->size; i++) {
        if (process_mod_convert(keycode, shortcut_group->sources[i], shortcut_group->others[i], lmod, rmod)) {
            result = true;
        }
    }

    if (!result) {
        for (uint8_t i = 0; i < num_mods; i++) {
            if (is_keycode_pressed(lmod)) {
                register_code(shortcut_group->mods[i]);
            }
        }
    }

    return result;
}

bool process_mod_shortcuts(uint16_t keycode, const struct mod_shortcut_group *mod_groups[]) {
    for (size_t i = 0; mod_groups[i] != NULL; i++) {
        if (process_mod_shortcut_group(keycode, mod_groups[i])) {
            return true;
        }
    }

    return false;
}

bool state_base(uint16_t keycode, keyrecord_t *record) {
    const uint8_t typesize = sizeof(uint16_t);

    const uint16_t ctl_sources[] = {KC_BSPC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL};
    const uint16_t ctl_others[]  = {KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12};
    // clang-format off
    const struct mod_shortcut_group ctl_group = {
        .size = sizeof(ctl_sources) / typesize,
        .mods = {KC_LCTL, KC_RCTL},
        .sources = ctl_sources,
        .others = ctl_others
    };
    // clang-format on

    const uint16_t alt_sources[] = {KC_H, KC_J, KC_K, KC_L};
    const uint16_t alt_others[]  = {KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT};
    // clang-format off
    const struct mod_shortcut_group alt_group = {
        .size = sizeof(alt_sources) / typesize,
        .mods = {KC_LALT, KC_RALT},
        .sources = alt_sources,
        .others = alt_others
    };
    // clang-format on

    const struct mod_shortcut_group *mod_groups[] = {&ctl_group, &alt_group, NULL};
    if (process_mod_shortcuts(keycode, mod_groups)) {
        return false;
    }

    return true;
}

bool state_vim(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool state_fn(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool state_game(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_keycode(keycode, record);

    if (layer_state_is(GAME)) {
        return state_game(keycode, record);
    } else if (layer_state_is(FN)) {
        return state_fn(keycode, record);
    } else if (layer_state_is(VIM)) {
        return state_vim(keycode, record);
    } else {
        return state_base(keycode, record);
    }
}

void process_combo_event(uint16_t combo_index, bool pressed) {
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

void matrix_init_user(void) {
    initialize_keys_state(keymaps);
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
