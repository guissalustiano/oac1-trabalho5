#include "database_t.h"
#include "database_file.h"

#ifndef DATABASE_H
#define DATABASE_H

typedef uint16_t db_tag_t;

typedef struct {
    db_tag_t tag;
    db_data_t data;
} cache_entry_t;

#define CACHE_SIZE sizeof(cache_entry_t) * 4096

/* Fig 5.15
 * 1 -> One way
 * 2 -> Two way
 * 4 -> Four way
 * 8 -> Eight way
 */
#define ASSOCIATIVITY 2

static cache_entry_t cache[CACHE_SIZE];
static uint32_t cache_hits;
static uint32_t cache_misses;

/*
 * Le dado do banco a partir da chave
 * Eh garantido que a chave exite no banco
 */
db_data_t get(db_key_t key);

/*
 * Coloca dado no banco
 * Se a chave ja existir, sobrescreve o dado
 */
void put(db_key_t key, db_data_t data);

void print_cache_stats();
#endif
