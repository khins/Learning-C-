#include <iostream>
#include <map>
#include <string>
#include "sqlite3.h"

using namespace std;

// SQLite helper
void insertResult(sqlite3* db, const string& category, const string& key, const string& value) {
    const char* sql =
        "INSERT INTO map_results (category, map_key, map_value) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    // The prepare function compiles the SQL statement and returns a statement object
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return;
    }

    // Bind parameters to the prepared statement
    sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, key.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, value.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3* db;

    // Full path to your database file
    const char* dbPath =
        "C:\\C++\\cpp-fundamentals\\lesson29_maps.db";

    if (sqlite3_open(dbPath, &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    cout << "Database opened successfully!" << endl;

    const char* createTableSql =
        "CREATE TABLE IF NOT EXISTS map_results ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "category TEXT NOT NULL,"
        "map_key TEXT NOT NULL,"
        "map_value TEXT NOT NULL"
        ");";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, createTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Table creation failed: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    cout << "\n=== Creating map ===" << endl;

    map<string, int> ages;

    ages["Kevin"] = 42;
    ages["Alice"] = 28;
    ages["Bob"] = 35;
    ages["Diana"] = 31;

    // Persist map contents
    for (const auto& pair : ages) {
        insertResult(
            db,
            "Initial Ages",
            pair.first,
            to_string(pair.second)
        );
    }

    cout << "\n=== Iterating map ===" << endl;

    for (const auto& pair : ages) {
        cout << pair.first
             << " is "
             << pair.second
             << " years old."
             << endl;
    }

    cout << "\n=== Lookup by key ===" << endl;

    string searchName = "Alice";

    if (ages.find(searchName) != ages.end()) {
        cout << searchName
             << " found: "
             << ages[searchName]
             << endl;

        insertResult(
            db,
            "Lookup Result",
            searchName,
            to_string(ages[searchName])
        );
    }

    cout << "\n=== Update value ===" << endl;

    ages["Bob"] = 40;

    cout << "Bob updated to age "
         << ages["Bob"]
         << endl;

    insertResult(
        db,
        "Updated Age",
        "Bob",
        to_string(ages["Bob"])
    );

    cout << "\n=== Counting word frequency ===" << endl;

    string words[] = {
        "apple",
        "banana",
        "apple",
        "orange",
        "banana",
        "apple"
    };

    map<string, int> wordCount;

    for (const string& word : words) {
        wordCount[word]++;
    }

    // auto& is used to avoid copying the pair and allows us to modify the original map if needed
    for (const auto& pair : wordCount) {
        cout << pair.first
             << " appears "
             << pair.second
             << " times."
             << endl;

        insertResult(
            db,
            "Word Frequency",
            pair.first,
            to_string(pair.second)
        );
    }

    cout << "\n=== Remove entry ===" << endl;

    ages.erase("Diana");

    cout << "Diana removed." << endl;

    insertResult(
        db,
        "Removed Entry",
        "Diana",
        "Deleted"
    );

    cout << "\n=== Final Map Contents ===" << endl;

    for (const auto& pair : ages) {
        cout << pair.first
             << " -> "
             << pair.second
             << endl;
    }

    sqlite3_close(db);

    cout << "\nMap lesson results stored successfully in SQLite!" << endl;
    cout << "Database: lesson29_maps.db" << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}