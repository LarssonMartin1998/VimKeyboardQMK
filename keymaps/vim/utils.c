#include "utils.h"
#include "keycode_map.h" // Include the keycode map

#include "layers.h"
#include "action.h"
#include "keycodes.h"
#include "keycode_map.h"

#include QMK_KEYBOARD_H
#include <stdint.h>

#define SUPPORTS_MAC
#define SUPPORTS_WINLIN
#define NUM_KEYS 83

static uint16_t default_layer = MAC;
static bool     insert_active = false;

void utils_set_default_layer(uint16_t new_default_layer) {
    default_layer = new_default_layer;
}

bool is_mac_os(void) {
#if defined(SUPPORTS_MAC) && defined(SUPPORTS_WINLIN)
    return default_layer == MAC;
#elif defined(SUPPORTS_MAC)
    return true;
#elif defined(SUPPORTS_WINLIN)
    return false;
#endif
}

uint16_t get_os_key(uint16_t mac_alternative) {
    if (is_mac_os()) {
        return mac_alternative;
    } else {
        return KC_LCTL;
    }
}

bool is_left_shift_held(void) {
    return keycode_map_lookup(KC_LSFT); // Use the keycode_map for lookup
}

bool is_right_shift_held(void) {
    return keycode_map_lookup(KC_RSFT); // Use the keycode_map for lookup
}

bool is_shift_held(void) {
    return is_left_shift_held() || is_right_shift_held();
}

bool is_left_ctrl_held(void) {
    return keycode_map_lookup(KC_LCTL); // Use the keycode_map for lookup
}

bool is_right_ctrl_held(void) {
    return keycode_map_lookup(KC_RCTL); // Use the keycode_map for lookup
}

bool is_ctrl_held(void) {
    return is_left_ctrl_held() || is_right_ctrl_held();
}

bool is_left_alt_held(void) {
    return keycode_map_lookup(KC_LALT); // Use the keycode_map for lookup
}

bool is_right_alt_held(void) {
    return keycode_map_lookup(KC_RALT); // Use the keycode_map for lookup
}

bool is_alt_held(void) {
    return is_left_alt_held() || is_right_alt_held();
}

void tap_insert_and_update_active_state(void) {
    const bool was_left_shift_held  = is_left_shift_held();
    const bool was_right_shift_held = is_right_shift_held();
    if (was_left_shift_held) {
        unregister_code(KC_LSFT);
    }

    if (was_right_shift_held) {
        unregister_code(KC_RSFT);
    }

    toggle_insert_active_state();

    if (was_left_shift_held) {
        register_code(KC_LSFT);
    }

    if (was_right_shift_held) {
        register_code(KC_RSFT);
    }
}

void toggle_insert_active_state(void) {
    insert_active = !insert_active;
}

bool is_insert_active(void) {
    return insert_active;
}

void initialize_keys_state(const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS]) {
    keycode_map_init(); // Initialize the keycode_map
}

bool is_keycode_pressed(uint8_t keycode) {
    return keycode_map_lookup(keycode); // Use the keycode_map for lookup
}

void update_keycode(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        keycode_map_insert(keycode, true); // Use the keycode_map for insertion
    } else {
        keycode_map_insert(keycode, false); // Use the keycode_map for insertion
    }
}
