#include <iostream>
#include "sqlite3.h"
using namespace std;

int main() {
    sqlite3* db;

    const char* dbPath = "C:\\python\\learning_python\\example.db";

    if (sqlite3_open(dbPath, &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    cout << "Opened database successfully!" << endl;

    // 🔹 SQL query
    const char* sql = "SELECT id, name, age FROM users;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    cout << "\n=== Users Table ===" << endl;

    // 🔹 Loop through rows
    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);

        const unsigned char* name = sqlite3_column_text(stmt, 1);

        int age = sqlite3_column_int(stmt, 2);

        cout << "ID: " << id
             << " | Name: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
             << " | Age: " << age
             << endl;
    }

    // 🔹 Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}
