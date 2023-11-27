#include "database.h"


void put(db_key_t key, db_data_t data){
    /*
     * Implemente sua função de cache aqui
     */

    return file_put(key, data);
}

db_data_t get(db_key_t key){
    /*
     * Implemente sua função de cache aqui
     * Não esqueça de atualizar os contadores de cache_hits e cache_misses
     */

    cache_misses++;
    return file_get(key);
}


// Do not modify below this function
void print_cache_stats() {
    printf("%6d: %6d/%6d\n", ASSOCIATIVITY ,cache_hits, cache_hits + cache_misses);
}
