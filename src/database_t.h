#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef DATABASE_T_H

#define DATABASE_T_H
typedef struct {
    uint64_t a;
    uint64_t b;
    uint64_t c;
    uint64_t d;
} db_data_t;

typedef uint64_t db_key_t;

typedef struct {
    db_key_t key;
    db_data_t data;
} db_entry_t;

int db_data_cmp(db_data_t a, db_data_t b);

#endif
