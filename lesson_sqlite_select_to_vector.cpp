#include <iostream>
#include <vector>
#include <string>
#include "sqlite3.h"

using namespace std;

// 🔹 Struct to represent a DB row
struct User {
    int id;
    string name;
    int age;
};

int main() {
    sqlite3* db;

    const char* dbPath = "C:\\python\\learning_python\\example.db";

    if (sqlite3_open(dbPath, &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    cout << "Opened database successfully!" << endl;

    const char* sql = "SELECT id, name, age FROM users;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    }

    vector<User> users;

    // 🔹 Fetch rows and store in vector
    while (sqlite3_step(stmt) == SQLITE_ROW) {

        User u;

        u.id = sqlite3_column_int(stmt, 0);

        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        u.name = nameText ? reinterpret_cast<const char*>(nameText) : "NULL";

        u.age = sqlite3_column_int(stmt, 2);

        users.push_back(u);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    cout << "\n=== Users Loaded into Vector ===" << endl;

    // 🔹 Print all users
    for (const User& u : users) {
        cout << "ID: " << u.id
             << " | Name: " << u.name
             << " | Age: " << u.age
             << endl;
    }

    // 🔹 Example: Filter users (age > 25)
    cout << "\n=== Users with Age > 25 ===" << endl;
    for (const User& u : users) {
        if (u.age > 25) {
            cout << u.name << " (" << u.age << ")" << endl;
        }
    }

    // 🔹 Example: Compute average age
    if (!users.empty()) {
        int total = 0;
        for (const User& u : users) {
            total += u.age;
        }

        double avg = (double)total / users.size();

        cout << "\nAverage age: " << avg << endl;
    }

    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}