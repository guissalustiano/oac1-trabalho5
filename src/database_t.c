#include "database_t.h"

int db_data_cmp(db_data_t a, db_data_t b) {
    if (a.a != b.a) return a.a - b.a;
    if (a.b != b.b) return a.b - b.b;
    if (a.c != b.c) return a.c - b.c;
    if (a.d != b.d) return a.d - b.d;
    return 0;
}
