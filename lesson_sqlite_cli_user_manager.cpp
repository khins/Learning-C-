#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

// 🔹 Add User
void addUser(sqlite3* db) {
    const char* sql = "INSERT INTO users (name, age) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    string name;
    int age;

    cout << "Enter name: ";
    getline(cin, name);

    cout << "Enter age: ";
    cin >> age;
    cin.ignore();

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, age);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << "User added successfully!\n";
    } else {
        cout << "Error adding user\n";
    }

    sqlite3_finalize(stmt);
}

// 🔹 Add Job
void addJob(sqlite3* db) {
    const char* sql = "INSERT INTO jobs (user_id, title, company) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    int userId;
    string title, company;

    cout << "Enter user ID: ";
    cin >> userId;
    cin.ignore();

    cout << "Enter job title: ";
    getline(cin, title);

    cout << "Enter company: ";
    getline(cin, company);

    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_text(stmt, 2, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, company.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << "Job added successfully!\n";
    } else {
        cout << "Error adding job\n";
    }

    sqlite3_finalize(stmt);
}

// 🔹 List Users + Jobs (JOIN)
void listUsersWithJobs(sqlite3* db) {
    const char* sql =
        "SELECT u.id, u.name, u.age, j.title, j.company "
        "FROM users u "
        "LEFT JOIN jobs j ON u.id = j.user_id "
        "ORDER BY u.id;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    cout << "\n--- Users + Jobs ---\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);

        const unsigned char* titleText = sqlite3_column_text(stmt, 3);
        const unsigned char* companyText = sqlite3_column_text(stmt, 4);

        string title = titleText ? reinterpret_cast<const char*>(titleText) : "No Job";
        string company = companyText ? reinterpret_cast<const char*>(companyText) : "-";

        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age
             << " | Job: " << title
             << " | Company: " << company
             << endl;
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3* db;
    const char* dbPath = "C:\\python\\learning_python\\example.db";

    if (sqlite3_open(dbPath, &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    // 🔥 Enable foreign keys
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    cout << "Database connected!\n";

    while (true) {
        cout << "\n===== USER MANAGER =====\n";
        cout << "1. Add User\n";
        cout << "2. Add Job\n";
        cout << "3. List Users + Jobs\n";
        cout << "4. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addUser(db);
                break;
            case 2:
                addJob(db);
                break;
            case 3:
                listUsersWithJobs(db);
                break;
            case 4:
                sqlite3_close(db);
                cout << "Goodbye!\n";
                cout << "Press Enter to exit...";
                cin.get();
                return 0;
            default:
                cout << "Invalid choice\n";
        }
    }
}