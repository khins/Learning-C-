// connects to your actual DB path
// inserts user input
// uses safer structure
#include <iostream>
#include <stdexcept>
#include <string>

#include "sqlite3.h"
using namespace std;

string escapeSqlText(const string& text) {
    string escaped;

    for (char ch : text) {
        escaped += ch;

        if (ch == '\'') {
            escaped += '\'';
        }
    }

    return escaped;
}

int main() {
    sqlite3* db;
    char* errMsg = 0;

    // Full path to your database
    const char* dbPath = "C:\\python\\learning_python\\example.db";

    int rc = sqlite3_open(dbPath, &db);

    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    } else {
        cout << "Opened database successfully!" << endl;
    }

    // User input
    string name;
    string ageText;
    int age;

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter age: ";
    getline(cin, ageText);

    try {
        age = stoi(ageText);
    } catch (const invalid_argument&) {
        cerr << "Invalid age. Please enter a number." << endl;
        sqlite3_close(db);
        return 1;
    } catch (const out_of_range&) {
        cerr << "Invalid age. The number is too large." << endl;
        sqlite3_close(db);
        return 1;
    }

    // Build SQL (basic version)
    string sql = "INSERT INTO users (name, age) VALUES ('" + escapeSqlText(name) + "', " + to_string(age) + ");";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "User inserted successfully!" << endl;
    }

    sqlite3_close(db);

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
