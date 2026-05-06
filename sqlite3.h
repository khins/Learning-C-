#ifndef CPP_FUNDAMENTALS_SQLITE3_H
#define CPP_FUNDAMENTALS_SQLITE3_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sqlite3 sqlite3;

#define SQLITE_OK 0

int sqlite3_open(const char* filename, sqlite3** ppDb);
int sqlite3_exec(
    sqlite3* db,
    const char* sql,
    int (*callback)(void*, int, char**, char**),
    void* firstArg,
    char** errMsg
);
const char* sqlite3_errmsg(sqlite3* db);
void sqlite3_free(void* ptr);
int sqlite3_close(sqlite3* db);

#ifdef __cplusplus
}
#endif

#endif
