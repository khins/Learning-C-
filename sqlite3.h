#ifndef CPP_FUNDAMENTALS_SQLITE3_H
#define CPP_FUNDAMENTALS_SQLITE3_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sqlite3 sqlite3;
typedef struct sqlite3_stmt sqlite3_stmt;

#define SQLITE_OK 0
#define SQLITE_ROW 100
#define SQLITE_DONE 101
#define SQLITE_TRANSIENT ((void (*)(void*)) -1)

int sqlite3_open(const char* filename, sqlite3** ppDb);
int sqlite3_prepare_v2(
    sqlite3* db,
    const char* sql,
    int nByte,
    sqlite3_stmt** ppStmt,
    const char** pzTail
);
int sqlite3_bind_text(
    sqlite3_stmt* stmt,
    int index,
    const char* value,
    int n,
    void (*destructor)(void*)
);
int sqlite3_bind_int(sqlite3_stmt* stmt, int index, int value);
int sqlite3_step(sqlite3_stmt* stmt);
int sqlite3_column_int(sqlite3_stmt* stmt, int column);
const unsigned char* sqlite3_column_text(sqlite3_stmt* stmt, int column);
int sqlite3_reset(sqlite3_stmt* stmt);
int sqlite3_clear_bindings(sqlite3_stmt* stmt);
int sqlite3_finalize(sqlite3_stmt* stmt);
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
