#include <stdbool.h>
#include "database_t.h"
#include "database_file.h"
#include <time.h>

#ifndef DATABASE_H
#define DATABASE_H

typedef uint32_t db_tag_t;

typedef struct {
    bool valid;
    // prefira a funcao clock() para obter um instante de tempo, pelo programa rodar muito rapido o time() pode retornar o mesmo valor em chamadas consecutivas
    long last_access;
    db_tag_t tag;
    db_data_t data;
} cache_entry_t;

#define CACHE_SIZE 1024

/* Fig 5.15
 * 1 -> One way
 * 2 -> Two way
 * 4 -> Four way
 * 8 -> Eight way
 */
#define ASSOCIATIVITY 1

static cache_entry_t cache[CACHE_SIZE];
static uint32_t cache_hits;
static uint32_t cache_misses;

/*
 * Inicializa o banco de dados
 * Chamado uma unica vez no inicio do programa
 */
void init();

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

uint32_t get_cache_hits();
uint32_t get_cache_misses();
void print_cache_stats();
#endif
