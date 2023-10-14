#pragma once

#include <stdbool.h>
#include <stdint.h>

struct KeyValue {
    uint16_t key;
    bool     value;
};

struct HashMap {
    const uint8_t    size;
    struct KeyValue *table;
};

void hashmap_insert(struct HashMap *map, uint16_t keycode, bool value);
bool hashmap_lookup(const struct HashMap *map, uint16_t keycode);
