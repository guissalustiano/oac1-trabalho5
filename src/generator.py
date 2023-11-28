import random

N = 2**15
MAX_UINT = 2**10 - 1
random.seed(404)

class Code:
    keys: set[int]

    def __init__(self):
        self.lines = []
        self.keys = set()

    def put(self, key: int):
        print(f"put_data({key});")
        self.keys.add(key)

    def get(self, key: int):
        if key not in self.keys:
            self.put(key)
        print(f"get_and_assert({key});")

def gen_key() -> int:
    v = random.normalvariate(mu=MAX_UINT/2, sigma=2**4)
    if v < 0:
        return 0
    elif v > MAX_UINT:
        return MAX_UINT
    else:
        return int(v)


def main():
    print("""#include <stdio.h>
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
        printf("Error: data mismatch for key %ld\\n", key);
        exit(1);
    }
}

int main() {
""")
    code = Code()
    for i in range(N):
        key = gen_key()
        if random.random() < 0.05: # 5% chance of a put
            code.put(key)
        else:
            code.get(key)

    print("""
    print_cache_stats();
    return 0;
}""")

if __name__ == "__main__":
    main()


