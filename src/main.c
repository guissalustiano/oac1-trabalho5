#include <stdint.h>
#include <stdio.h>
#include "database.h"

#define ASSERT(cond) if (!(cond)) { printf("Assertion failed: %s\n", #cond); exit(1); }

// generate data from the key
db_data_t gen_data(db_key_t key, uint64_t data) {
    return (db_data_t) {data, 0, 0, key};
}

db_key_t get_key() {
    return (db_key_t) rand() + rand() - rand() - rand();
}

/*
 * put data into the database
 */
void pd(db_key_t key, uint64_t data) {
    put(key, gen_data(key, data));
}


// p/ ASSOCIATIVITY = 1
void test_1() {
    pd(1, 5);

    // logo depois de inserir, o dado deve estar no cache
    ASSERT(get(1).a == 5);
    ASSERT(get_cache_hits() == 1);
    ASSERT(get_cache_misses() == 0);

    pd(1025, 7); // sobrecreve o cache anterior
    ASSERT(get(1025).a == 7);
    ASSERT(get_cache_hits() == 2);
    ASSERT(get_cache_misses() == 0);

    ASSERT(get(1).a == 5); //le o antigo dado
    ASSERT(get_cache_hits() == 2);
    ASSERT(get_cache_misses() == 1);
}

// p/ ASSOCIATIVITY = 2
void test_2() {
    pd(1, 5);
    pd(1025, 7);

    ASSERT(get(1).a == 5);
    ASSERT(get(1025).a == 7);
    ASSERT(get_cache_hits() == 2);
    ASSERT(get_cache_misses() == 0);

    pd(2049, 9); // replace the 1, the oldest cache entry
    ASSERT(get(2049).a == 9);
    ASSERT(get_cache_hits() == 3);
    ASSERT(get_cache_misses() == 0);

    ASSERT(get(1025).a == 7); // 1025 should still be in the cache
    ASSERT(get_cache_hits() == 4);
    ASSERT(get_cache_misses() == 0);

    pd(3073, 11); // replace the 2049, the oldest cache entry
    ASSERT(get(3073).a == 11);
    ASSERT(get_cache_hits() == 5);
    ASSERT(get_cache_misses() == 0);

    ASSERT(get(1025).a == 7); // 1025 should still be in the cache
    ASSERT(get_cache_hits() == 6);
    ASSERT(get_cache_misses() == 0);

    ASSERT(get(1).a == 5); // 1 should be a miss
    ASSERT(get_cache_hits() == 6);
    ASSERT(get_cache_misses() == 1);
}

// p/ ASSOCIATIVITY = 1024 (max)
void test_1024() {
    for (int i = 0; i < CACHE_SIZE; i++) {
        pd(i, i);
    }

    for (int i = 0; i < CACHE_SIZE; i++) {
        ASSERT(get(i).a == i);
    }
    ASSERT(get_cache_hits() == 1024);
    ASSERT(get_cache_misses() == 0);

    pd(CACHE_SIZE, 1024); // replace the 0, the oldest cache entry
    ASSERT(get(0).a == 0);
    ASSERT(get_cache_hits() == 1024);
    ASSERT(get_cache_misses() == 1);
}

int main() {
    init();

    switch (ASSOCIATIVITY) {
        case 1: {
            test_1();
            break;
        }
        case 2: {
            test_2();
            break;
        }
        case 1024: {
            test_1024();
            break;
        }
    }

    print_cache_stats();
    return 0;
}
