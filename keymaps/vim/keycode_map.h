#pragma once

#include <stdbool.h>
#include <stdint.h>
#define TABLE_SIZE 83

struct KeyValue {
    uint16_t key;
    bool     value;
};

void keycode_map_init(void);
void keycode_map_insert(uint16_t keycode, bool value);
bool keycode_map_lookup(uint16_t keycode);
