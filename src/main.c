#include <stdio.h>
#include "database.h"

// generate data from the key
db_data_t gen_data(db_key_t key) {
    return (db_data_t) {key, key%2023 + key*2023, ~key, ~key};
}

db_key_t get_key() {
    return (db_key_t) rand() + rand() - rand() - rand();
}

void put_data(db_key_t key) {
    put(key, gen_data(key));
}

void get_and_assert(db_key_t key) {
    db_data_t data = get(key);
    db_data_t expected = gen_data(key);

    if (db_data_cmp(data, expected) != 0) {
        printf("Error: data mismatch for key %ld\n", key);
        exit(1);
    }
}

int main() {
    put_data(0);
    get_and_assert(0);

    put_data(1);
    get_and_assert(0);
    get_and_assert(1);

    put_data(2);
    get_and_assert(0);
    get_and_assert(1);
    get_and_assert(2);

    put_data(3);
    get_and_assert(0);
    get_and_assert(1);
    get_and_assert(2);
    get_and_assert(3);

    print_cache_stats();
    return 0;
}
