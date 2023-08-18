#include "utils.h"

#include QMK_KEYBOARD_H

#include "layers.h"

#define SUPPORTS_MAC
#define SUPPORTS_WIN // Same as Linux

#define LSFT_BIT (1 << 0)
#define RSFT_BIT (1 << 1)
#define LCTL_BIT (1 << 2)
#define RCTL_BIT (1 << 3)
#define LALT_BIT (1 << 4)
#define RALT_BIT (1 << 5)
#define BACKSPACE_BIT (1 << 6)
#define INSERT_BIT (1 << 7)

unsigned char modifiers_state_mask = 0x00;

bool is_mac_os(void) {
#if defined(SUPPORTS_MAC) && defined(SUPPORTS_WIN)
    return layer_state_is(MAC);
#elif defined(SUPPORTS_MAC)
    return true;
#elif defined(SUPPORTS_WIN)
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

void set_left_shift_held(void) {
    modifiers_state_mask |= LSFT_BIT;
}

void set_left_shift_released(void) {
    modifiers_state_mask &= ~LSFT_BIT;
}

bool is_left_shift_held(void) {
    return modifiers_state_mask & LSFT_BIT;
}

void set_right_shift_held(void) {
    modifiers_state_mask |= RSFT_BIT;
}

void set_right_shift_released(void) {
    modifiers_state_mask &= ~RSFT_BIT;
}

bool is_right_shift_held(void) {
    return modifiers_state_mask & RSFT_BIT;
}

bool is_shift_held(void) {
    return is_left_shift_held() || is_right_shift_held();
}

void set_left_ctrl_held(void) {
    modifiers_state_mask |= LCTL_BIT;
}

void set_left_ctrl_released(void) {
    modifiers_state_mask &= ~LCTL_BIT;
}

bool is_left_ctrl_held(void) {
    return modifiers_state_mask & LCTL_BIT;
}

void set_right_ctrl_held(void) {
    modifiers_state_mask |= RCTL_BIT;
}

void set_right_ctrl_released(void) {
    modifiers_state_mask &= ~LALT_BIT;
}

bool is_right_ctrl_held(void) {
    return modifiers_state_mask & RCTL_BIT;
}

bool is_ctrl_held(void) {
    return is_left_ctrl_held() || is_right_ctrl_held();
}

void set_left_alt_held(void) {
    modifiers_state_mask |= LALT_BIT;
}

void set_left_alt_released(void) {
    modifiers_state_mask &= ~LALT_BIT;
}

bool is_left_alt_held(void) {
    return modifiers_state_mask & LALT_BIT;
}

void set_right_alt_held(void) {
    modifiers_state_mask |= RALT_BIT;
}

void set_right_alt_released(void) {
    modifiers_state_mask &= ~RALT_BIT;
}

bool is_right_alt_held(void) {
    return modifiers_state_mask & RALT_BIT;
}

bool is_alt_held(void) {
    return is_left_alt_held() || is_right_alt_held();
}

void set_backspace_held(void) {
    modifiers_state_mask |= BACKSPACE_BIT;
}

void set_backspace_released(void) {
    modifiers_state_mask &= ~BACKSPACE_BIT;
}

bool is_backspace_held(void) {
    return modifiers_state_mask & BACKSPACE_BIT;
}

void tap_insert_and_update_active_state() {
    tap_code(KC_INS);
    toggle_insert_active_state();
}

void toggle_insert_active_state(void) {
    modifiers_state_mask ^= INSERT_BIT;
}

bool is_insert_active(void) {
    return modifiers_state_mask & INSERT_BIT;
}