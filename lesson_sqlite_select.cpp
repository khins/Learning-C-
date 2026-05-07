#include <iostream>
#include <stdexcept>
#include <string>

#include "sqlite3.h"
using namespace std;

void showUsers(sqlite3* db) {
    const char* sql = "SELECT id, name, age FROM users ORDER BY id;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare SELECT: " << sqlite3_errmsg(db) << endl;
        return;
    }

    cout << "\n=== Users Table ===" << endl;

    bool foundRows = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        foundRows = true;

        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int age = sqlite3_column_int(stmt, 2);

        cout << "ID: " << id
             << " | Name: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
             << " | Age: " << age
             << endl;
    }

    if (!foundRows) {
        cout << "No users found." << endl;
    }

    sqlite3_finalize(stmt);
}

void deleteUserById(sqlite3* db) {
    string idText;
    int id;

    cout << "Enter user ID to delete: ";
    getline(cin, idText);

    try {
        id = stoi(idText);
    } catch (const invalid_argument&) {
        cerr << "Invalid ID. Please enter a number." << endl;
        return;
    } catch (const out_of_range&) {
        cerr << "Invalid ID. The number is too large." << endl;
        return;
    }

    const char* sql = "DELETE FROM users WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare DELETE: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Delete failed: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Delete completed for ID " << id << "." << endl;
    }

    sqlite3_finalize(stmt);
}

void filterUsersByAge(sqlite3* db) {
    string ageText;
    int minAge;

    cout << "Show users older than age: ";
    getline(cin, ageText);

    try {
        minAge = stoi(ageText);
    } catch (const invalid_argument&) {
        cerr << "Invalid age. Please enter a number." << endl;
        return;
    } catch (const out_of_range&) {
        cerr << "Invalid age. The number is too large." << endl;
        return;
    }

    const char* sql = "SELECT id, name, age FROM users WHERE age > ? ORDER BY age;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare age filter: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, minAge);

    cout << "\n=== Users Older Than " << minAge << " ===" << endl;

    bool foundRows = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        foundRows = true;

        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int age = sqlite3_column_int(stmt, 2);

        cout << "ID: " << id
             << " | Name: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
             << " | Age: " << age
             << endl;
    }

    if (!foundRows) {
        cout << "No users found." << endl;
    }

    sqlite3_finalize(stmt);
}

void searchUsersByName(sqlite3* db) {
    string searchText;

    cout << "Enter name search text: ";
    getline(cin, searchText);

    if (searchText.empty()) {
        cerr << "Search text cannot be empty." << endl;
        return;
    }

    string pattern = "%" + searchText + "%";
    const char* sql = "SELECT id, name, age FROM users WHERE name LIKE ? ORDER BY name;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare name search: " << sqlite3_errmsg(db) << endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);

    cout << "\n=== Users Matching \"" << searchText << "\" ===" << endl;

    bool foundRows = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        foundRows = true;

        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        int age = sqlite3_column_int(stmt, 2);

        cout << "ID: " << id
             << " | Name: " << (name ? reinterpret_cast<const char*>(name) : "NULL")
             << " | Age: " << age
             << endl;
    }

    if (!foundRows) {
        cout << "No users found." << endl;
    }

    sqlite3_finalize(stmt);
}

void printMenu() {
    cout << "\n=== SQLite User Menu ===" << endl;
    cout << "1. View all users" << endl;
    cout << "2. Delete user by ID" << endl;
    cout << "3. Filter users by age" << endl;
    cout << "4. Search users by name" << endl;
    cout << "5. Clear screen" << endl;
    cout << "6. Quit" << endl;
    cout << "Choose an option: ";
}

int main() {
    sqlite3* db;

    const char* dbPath = "C:\\python\\learning_python\\example.db";

    if (sqlite3_open(dbPath, &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }

    cout << "Opened database successfully!" << endl;

    string choice;

    while (true) {
        printMenu();
        getline(cin, choice);

        if (choice == "1") {
            showUsers(db);
        } else if (choice == "2") {
            deleteUserById(db);
        } else if (choice == "3") {
            filterUsersByAge(db);
        } else if (choice == "4") {
            searchUsersByName(db);
        } else if (choice == "5") {
            system("cls");
        } else if (choice == "6") {
            break;
        } else {
            cout << "Invalid option. Please choose 1, 2, 3, 4, 5, or 6." << endl;
        }
    }

    sqlite3_close(db);

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
