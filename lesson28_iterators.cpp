#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "sqlite3.h"

using namespace std;

// Insert helper
void insertResult(sqlite3* db, const string& category, const string& value) {
    const char* sql =
        "INSERT INTO iterator_results (category, value) VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Insert failed: " << sqlite3_errmsg(db) << endl;
    }

    sqlite3_finalize(stmt);
}

// Function to clear existing data from the results table
void clearResults(sqlite3* db) {
    char* errMsg = nullptr;
    const char* sql = "DELETE FROM iterator_results;";

    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Failed to clear table: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Table 'iterator_results' cleared for new run." << endl;
    }
}

int main() {
    sqlite3* db;

    const char* dbPath =
        "C:\\C++\\cpp-fundamentals\\lesson28_iterators.db";

    if (sqlite3_open(dbPath, &db)) {
        cerr << "Can't open database: "
             << sqlite3_errmsg(db)
             << endl;
        return 1;
    }

    cout << "Database opened successfully!" << endl;

    // Create table
    const char* createTableSql =
        "CREATE TABLE IF NOT EXISTS iterator_results ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "category TEXT NOT NULL,"
        "value TEXT NOT NULL"
        ");";

    char* errMsg = nullptr;

    if (sqlite3_exec(db, createTableSql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        cerr << "Table creation failed: " << errMsg << endl;
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 1;
    }

    // Clear previous data before running the lesson
    clearResults(db);

    vector<int> numbers = {10, 20, 30, 40, 50};

    cout << "\n=== Basic Iterator Traversal ===" << endl;

    string traversalValues;

    vector<int>::iterator it = numbers.begin();

    // Traverse using iterator and store values in string for database insertion
    while (it != numbers.end()) {
        cout << "Value: " << *it << endl;
        traversalValues += to_string(*it) + " ";
        ++it;
    }

    insertResult(db, "Basic Traversal", traversalValues); // Store traversal results in database

    cout << "\n=== Modify Values Through Iterator ===" << endl;

    // Modify values by doubling them using an iterator
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
        *iter *= 2;
    }

    string modifiedValues;

    // Display modified values and store them in string for database insertion
    for (int n : numbers) {
        cout << n << " ";
        modifiedValues += to_string(n) + " ";
    }

    cout << endl;

    insertResult(db, "Modified x2", modifiedValues); // Store modified values in database

    cout << "\n=== Reverse Iterator Traversal ===" << endl;

    string reverseValues;

    // Traverse in reverse using reverse iterators and store values in string for database insertion
    for (auto rit = numbers.rbegin(); rit != numbers.rend(); ++rit) {
        cout << *rit << " ";
        reverseValues += to_string(*rit) + " ";
    }

    cout << endl;

    insertResult(db, "Reverse Traversal", reverseValues);

    cout << "\n=== Sum Using Iterators ===" << endl;

    int total = 0;

    // auto iter = numbers.begin() allows the compiler to deduce the iterator type
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
        total += *iter;
    }

    cout << "Total: " << total << endl;

    insertResult(db, "Iterator Sum", to_string(total));

    cout << "\n=== Even Numbers Only ===" << endl;

    string evenValues;

    // Filter even numbers using iterator
    for (auto iter = numbers.begin(); iter != numbers.end(); ++iter) {
        if (*iter % 2 == 0) {
            cout << *iter << " ";
            evenValues += to_string(*iter) + " ";
        }
    }

    cout << endl;

    insertResult(db, "Even Numbers", evenValues);

    cout << "\n=== String Iterator Example ===" << endl;

    string word = "across the cosmos";
    string characters;

    for (auto ch = word.begin(); ch != word.end(); ++ch) {
        cout << *ch << " ";
        characters += *ch;
        characters += " ";
    }

    cout << endl;

    insertResult(db, "String Characters", characters);

    cout << "\n=== Constant Iterators (Read-Only) ===" << endl;

    string constValues;
    // cbegin() and cend() provide a const_iterator, preventing modification
    for (auto cit = numbers.cbegin(); cit != numbers.cend(); ++cit) {
        // *cit = 5; // This would cause a compiler error!
        cout << *cit << " ";
        constValues += to_string(*cit) + " ";
    }
    cout << endl;

    insertResult(db, "Constant Iterators", constValues);

    cout << "\n=== Finding Elements with Iterators ===" << endl;

    int target = 40;
    // std::find returns an iterator to the first occurrence
    auto foundIt = find(numbers.begin(), numbers.end(), target);

    if (foundIt != numbers.end()) {
        // Use std::distance to find the numerical index
        int index = distance(numbers.begin(), foundIt);
        cout << "Found " << target << " at index " << index << endl;
        
        string findResult = "Value " + to_string(target) + " found at index " + to_string(index);
        insertResult(db, "Search Result", findResult);
    } else {
        cout << target << " not found in vector." << endl;
        insertResult(db, "Search Result", "Value not found");
    }

    sqlite3_close(db);

    cout << "\nIterator lesson results stored in SQLite successfully!" << endl;
    cout << "Database: lesson28_iterators.db" << endl;

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}