#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "sqlite3.h"

using namespace std;

void insertResult(sqlite3* db, const string& category, const string& value) {
    if (db == nullptr) {
        cerr << "Database pointer is null!" << endl;
        return;
    }

    cout << "Preparing statement..." << endl;

    const char* sql =
        "INSERT INTO lambda_results (category, value) VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Prepare failed: "
             << sqlite3_errmsg(db)
             << endl;
        return;
    }

    cout << "Binding values..." << endl;

    sqlite3_bind_text(stmt, 1, category.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, value.c_str(), -1, SQLITE_TRANSIENT);

    cout << "Executing insert..." << endl;

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Insert failed: "
             << sqlite3_errmsg(db)
             << endl;
    } else {
        cout << "Insert succeeded." << endl;
    }

    sqlite3_finalize(stmt);
}

string vectorToString(const vector<int>& nums) {
    string result;

    for (int n : nums) {
        result += to_string(n) + " ";
    }

    return result;
}

int main() {
    sqlite3* db;
    const char* dbPath = "C:\\c++\\cpp-fundamentals\\lesson27_lambda_results.db";

    if (sqlite3_open(dbPath, &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    cout << "Database created/opened successfully!" << endl;

    // Create table
    const char* createTableSql =
        "CREATE TABLE IF NOT EXISTS lambda_results ("
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

    vector<int> numbers = {10, 20, 30, 40, 50};

    // Store original values
    insertResult(db, "Original Values", vectorToString(numbers));

    // Multiply values
    for_each(numbers.begin(), numbers.end(), [](int& n) {
        n *= 2;
    });

    insertResult(db, "Multiplied x2", vectorToString(numbers));

    // Threshold filter
    int threshold = 50;
    string filtered;

    for_each(numbers.begin(), numbers.end(), [threshold, &filtered](int n) {
        if (n > threshold) {
            filtered += to_string(n) + " ";
        }
    });

    insertResult(db, "Greater Than Threshold", filtered);

    // Total sum
    int total = 0;

    for_each(numbers.begin(), numbers.end(), [&total](int n) {
        total += n;
    });

    insertResult(db, "Total Sum", to_string(total));

    // Square lambda
    auto square = [](int x) {
        return x * x;
    };

    insertResult(db, "Square of 7", to_string(square(7)));

    // Sort descending
    vector<int> moreNumbers = {3, 8, 1, 9, 4};

    sort(moreNumbers.begin(), moreNumbers.end(),
        [](int a, int b) {
            return a > b;
        });

    insertResult(db, "Sorted Descending", vectorToString(moreNumbers));

    sqlite3_close(db);

    cout << "\nLambda results stored successfully in SQLite!" << endl;
    cout << "Database file: lesson27_lambda_results.db" << endl;
    cout << "Filter values that are only even." << endl;    

    // Filter even values
    string evenFiltered;

    for_each(numbers.begin(), numbers.end(), [&evenFiltered, db](int n) {
        if (n % 2 == 0) {            
            evenFiltered += to_string(n) + " ";
            cout << n << " is even." << endl;
        }
    });

    // insert result of even filter into database
   // insertResult(db, "Even Values", evenFiltered);
   

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}