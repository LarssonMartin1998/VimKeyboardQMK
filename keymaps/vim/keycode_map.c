#include "keycode_map.h"

struct KeyValue table[TABLE_SIZE];

unsigned int hash(uint16_t key) {
    return key % TABLE_SIZE;
}

void keycode_map_init(void) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = 0; // Initialize keys to 0 (unused)
    }
}

void keycode_map_insert(uint16_t keycode, bool value) {
    unsigned int index = hash(keycode);
    table[index].key   = keycode;
    table[index].value = value;
}

bool keycode_map_lookup(uint16_t keycode) {
    unsigned int index = hash(keycode);
    return table[index].value;
}
