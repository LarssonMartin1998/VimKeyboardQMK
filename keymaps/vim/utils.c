#include "utils.h"
#include "hash.h" // Include the keycode map

#include "layers.h"
#include "action.h"
#include "keycodes.h"

#include QMK_KEYBOARD_H
#include <stdint.h>

#define SUPPORTS_MAC
#define SUPPORTS_WINLIN
#define NUM_KEYS 83

static uint16_t default_layer = MAC;
static bool     insert_active = false;

static struct KeyValue keys_table[NUM_KEYS] = {[0 ... NUM_KEYS - 1] = {0, false}};
static struct HashMap  keys                 = {.size = NUM_KEYS, .table = keys_table};

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
    return hashmap_lookup(&keys, KC_LSFT); // Use the keycode_map for lookup
}

bool is_right_shift_held(void) {
    return hashmap_lookup(&keys, KC_RSFT); // Use the keycode_map for lookup
}

bool is_shift_held(void) {
    return is_left_shift_held() || is_right_shift_held();
}

bool is_left_ctrl_held(void) {
    return hashmap_lookup(&keys, KC_LCTL); // Use the keycode_map for lookup
}

bool is_right_ctrl_held(void) {
    return hashmap_lookup(&keys, KC_RCTL); // Use the keycode_map for lookup
}

bool is_ctrl_held(void) {
    return is_left_ctrl_held() || is_right_ctrl_held();
}

bool is_left_alt_held(void) {
    return hashmap_lookup(&keys, KC_LALT); // Use the keycode_map for lookup
}

bool is_right_alt_held(void) {
    return hashmap_lookup(&keys, KC_RALT); // Use the keycode_map for lookup
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

bool is_keycode_pressed(uint8_t keycode) {
    return hashmap_lookup(&keys, keycode); // Use the keycode_map for lookup
}

void update_keycode(uint16_t keycode, keyrecord_t *record) {
    hashmap_insert(&keys, keycode, record->event.pressed); // Use the keycode_map for insertion
}
