#include "database_file.h"

FILE *open_file(db_key_t key, char *mode) {
    char path[48];
    sprintf(path, "%s/%ld.db", DB_DIR, key);

    FILE *fptr;
    fptr = fopen(path, mode);

    if(fptr == NULL){
        printf("Error opening file\n");
        exit(1);
    }

    return fptr;
}

db_data_t file_get(db_key_t key){
    FILE *fptr = open_file(key, "rb");

    db_data_t data;
    fread(&data, sizeof(db_data_t), 1, fptr);

    fclose(fptr);
    return data;
}

void file_put(db_key_t key, db_data_t data){
    FILE *fptr = open_file(key, "wb");

    fwrite(&data, sizeof(db_data_t), 1, fptr);

    fclose(fptr);
}
