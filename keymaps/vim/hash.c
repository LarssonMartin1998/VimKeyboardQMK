#include "hash.h"
#include <stdint.h>

static uint16_t hash(const uint8_t size, const uint16_t key) {
    return key % size;
}

void hashmap_insert(struct HashMap *map, const uint16_t key, bool value) {
    const uint16_t index    = hash(map->size, key);
    map->table[index].key   = key;
    map->table[index].value = value;
}

bool hashmap_lookup(const struct HashMap *map, const uint16_t key) {
    const uint16_t index = hash(map->size, key);
    if (map->table[index].key != key) {
        // Key doesn't exist
        return false;
    }

    return map->table[index].value;
}
