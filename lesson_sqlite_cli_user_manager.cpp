#include <iostream>
#include <vector>
#include <string>
#include "sqlite3.h"

using namespace std;

// 🔹 User struct
struct User {
    int id;
    string name;
    int age;
};

// add job
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

// 🔹 Add user
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

// 🔹 List users
void listUsers(sqlite3* db) {
    const char* sql = "SELECT id, name, age FROM users;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    cout << "\n--- Users ---\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "ID: " << sqlite3_column_int(stmt, 0)
             << " | Name: " << sqlite3_column_text(stmt, 1)
             << " | Age: " << sqlite3_column_int(stmt, 2)
             << endl;
    }

    sqlite3_finalize(stmt);
}

// 🔹 Search user by name
void searchUser(sqlite3* db) {
    const char* sql = "SELECT id, name, age FROM users WHERE name = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    string name;
    cout << "Enter name to search: ";
    getline(cin, name);

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

    cout << "\n--- Search Results ---\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "ID: " << sqlite3_column_int(stmt, 0)
             << " | Name: " << sqlite3_column_text(stmt, 1)
             << " | Age: " << sqlite3_column_int(stmt, 2)
             << endl;
    }

    sqlite3_finalize(stmt);
}

// 🔹 Delete user by ID
void deleteUser(sqlite3* db) {
    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    int id;
    cout << "Enter user ID to delete: ";
    cin >> id;
    cin.ignore();

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << "User deleted successfully!\n";
    } else {
        cout << "Error deleting user\n";
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

    cout << "Database connected!\n";

    while (true) {
        cout << "\n===== USER MANAGER =====\n";
        cout << "1. Add User\n";
        cout << "2. List Users\n";
        cout << "3. Search User\n";
        cout << "4. Delete User\n";
        cout << "5. Exit\n";
        cout << "Choose option: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addUser(db);
                break;
            case 2:
                listUsers(db);
                break;
            case 3:
                searchUser(db);
                break;
            case 4:
                deleteUser(db);
                break;
            case 5:
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