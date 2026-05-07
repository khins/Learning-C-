#include <iostream>
#include <stdexcept>
#include <string>

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

    // Prepare SQL with placeholders
    const char* sql = "INSERT INTO users (name, age) VALUES (?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    // User input
    string name;
    string ageText;
    int age;

    // cout << "Enter name: ";
    // getline(cin, name);

    // cout << "Enter age: ";
    // getline(cin, ageText);

    // Insert multiple users in loop
    while (true) {
        cout << "Enter name (or 'quit' to exit): ";
        getline(cin, name);

        if (name == "quit") {
            break;
        }

        cout << "Enter age: ";
        getline(cin, ageText);

        try {
            age = stoi(ageText);
        } catch (...) {
            cerr << "Invalid age." << endl;
            continue;
        }

        // Bind values
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, age);

        // Execute
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            cerr << "Execution failed: " << sqlite3_errmsg(db) << endl;
        } else {
            cout << "User inserted successfully!" << endl;
        }

        // Reset for next use
        sqlite3_reset(stmt);

        // Clear bindings before the next loop
        sqlite3_clear_bindings(stmt);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
