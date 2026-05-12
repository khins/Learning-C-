#include <iostream>
#include <fstream>
#include <string>
#include "sqlite3.h"

using namespace std;

// helper functions
bool isValidName(const string& name) {
    return !name.empty();
}

bool isValidAge(int age) {
    return age >= 0 && age <= 120;
}

void exportToCsv(sqlite3* db) {
    const char* sql =
        "SELECT u.id, u.name, u.age, j.title, j.company "
        "FROM users u "
        "LEFT JOIN jobs j ON u.id = j.user_id "
        "ORDER BY u.id;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare export query: "
             << sqlite3_errmsg(db)
             << endl;
        return;
    }

    ofstream file("users_export.csv");

    if (!file.is_open()) {
        cerr << "Failed to create CSV file." << endl;
        sqlite3_finalize(stmt);

        cout << "Press Enter to exit...";
        cin.get();

        return;
    }

    // CSV header
    file << "id,name,age,job_title,company\n";

    int rowCount = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);

        const unsigned char* nameText = sqlite3_column_text(stmt, 1);
        int age = sqlite3_column_int(stmt, 2);

        const unsigned char* titleText = sqlite3_column_text(stmt, 3);
        const unsigned char* companyText = sqlite3_column_text(stmt, 4);

        string name =
            nameText ? reinterpret_cast<const char*>(nameText) : "";

        string title =
            titleText ? reinterpret_cast<const char*>(titleText) : "";

        string company =
            companyText ? reinterpret_cast<const char*>(companyText) : "";

        file << id << ","
             << "\"" << name << "\","
             << age << ","
             << "\"" << title << "\","
             << "\"" << company << "\""
             << "\n";

        rowCount++;
    }

    file.close();
    sqlite3_finalize(stmt);

    cout << "Export complete!" << endl;
    cout << rowCount << " row(s) written to users_export.csv" << endl;
}

// 🔹 View Analytics
void viewAnalytics(sqlite3* db) {

    sqlite3_stmt* stmt;

    cout << "\n===== ANALYTICS DASHBOARD =====\n";

    // 🔹 Total Users
    const char* totalUsersSql =
        "SELECT COUNT(*) FROM users;";

    sqlite3_prepare_v2(db, totalUsersSql, -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Total Users: "
             << sqlite3_column_int(stmt, 0)
             << endl;
    }

    sqlite3_finalize(stmt);

    // 🔹 Average Age
    const char* avgAgeSql =
        "SELECT AVG(age) FROM users;";

    sqlite3_prepare_v2(db, avgAgeSql, -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Average Age: "
             << sqlite3_column_double(stmt, 0)
             << endl;
    }

    sqlite3_finalize(stmt);

    // 🔹 Oldest User
    const char* oldestUserSql =
        "SELECT name, age "
        "FROM users "
        "ORDER BY age DESC "
        "LIMIT 1;";

    sqlite3_prepare_v2(db, oldestUserSql, -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        const char* name =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        int age = sqlite3_column_int(stmt, 1);

        cout << "Oldest User: "
             << name
             << " (" << age << ")"
             << endl;
    }

    sqlite3_finalize(stmt);

    // 🔹 Users Without Jobs
    const char* noJobsSql =
        "SELECT COUNT(*) "
        "FROM users u "
        "LEFT JOIN jobs j ON u.id = j.user_id "
        "WHERE j.id IS NULL;";

    sqlite3_prepare_v2(db, noJobsSql, -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Users Without Jobs: "
             << sqlite3_column_int(stmt, 0)
             << endl;
    }

    sqlite3_finalize(stmt);

    // 🔹 Top Companies
    const char* topCompaniesSql =
        "SELECT company, COUNT(*) as total "
        "FROM jobs "
        "GROUP BY company "
        "ORDER BY total DESC;";

    sqlite3_prepare_v2(db, topCompaniesSql, -1, &stmt, nullptr);

    cout << "\n--- Top Companies ---\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        const char* company =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

        int total = sqlite3_column_int(stmt, 1);

        cout << company
             << " -> "
             << total
             << " employee(s)"
             << endl;
    }

    sqlite3_finalize(stmt);
}

// 🔹 Add User
void addUser(sqlite3* db) {
    const char* sql = "INSERT INTO users (name, age) VALUES (?, ?);";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    string name;
    int age;

    cout << "Enter name: ";
    getline(cin, name);

    // validate name
    if (!isValidName(name)) {
        cout << "Invalid name. Cannot be empty.\n";
        sqlite3_finalize(stmt);
        return;
    }

    cout << "Enter age: ";
    cin >> age;
    // validate age
    if (!isValidAge(age)) {
        cout << "Invalid age. Please enter a value between 0 and 120.\n";
        sqlite3_finalize(stmt);
        return;
    }
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

void listUsersWithJobsGrouped(sqlite3* db) {
    const char* sql =
        "SELECT u.id, u.name, u.age, j.title, j.company "
        "FROM users u "
        "LEFT JOIN jobs j ON u.id = j.user_id "
        "ORDER BY u.id;";

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    cout << "\n--- Users + Jobs (Grouped) ---\n";

    int currentUserId = -1;
    bool hasJob = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);

        const unsigned char* titleText = sqlite3_column_text(stmt, 3);
        const unsigned char* companyText = sqlite3_column_text(stmt, 4);

        string title = titleText ? reinterpret_cast<const char*>(titleText) : "";
        string company = companyText ? reinterpret_cast<const char*>(companyText) : "";

        // 🔹 New user detected
        if (id != currentUserId) {
            // print "No Jobs" for previous user if needed
            if (currentUserId != -1 && !hasJob) {
                cout << "    - No Jobs\n";
            }

            cout << "\nID: " << id
                 << " | Name: " << name
                 << " | Age: " << age
                 << endl;

            currentUserId = id;
            hasJob = false;
        }

        // 🔹 Print job if exists
        if (!title.empty()) {
            cout << "    - " << title << " @ " << company << endl;
            hasJob = true;
        }
    }

    // 🔹 Handle last user with no jobs
    if (currentUserId != -1 && !hasJob) {
        cout << "    - No Jobs\n";
    }

    sqlite3_finalize(stmt);
}

// update job
void updateJob(sqlite3* db) {
    const char* sql = "UPDATE jobs SET title = ?, company = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    int jobId;
    string title, company;

    cout << "Enter job ID to update: ";
    cin >> jobId;
    cin.ignore();

    cout << "Enter new job title: ";
    getline(cin, title);

    cout << "Enter new company: ";
    getline(cin, company);

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, company.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, jobId);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        if (sqlite3_changes(db) > 0) {
            cout << "Job updated successfully!\n";
        } else {
            cout << "No job found with that ID.\n";
        }
    } else {
        cout << "Error updating job\n";
    }

    sqlite3_finalize(stmt);
}

void deleteJob(sqlite3* db) {
    const char* sql = "DELETE FROM jobs WHERE id = ?;";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    int jobId;

    cout << "Enter job ID to delete: ";
    cin >> jobId;
    cin.ignore();

    sqlite3_bind_int(stmt, 1, jobId);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        if (sqlite3_changes(db) > 0) {
            cout << "Job deleted successfully!\n";
        } else {
            cout << "No job found with that ID.\n";
        }
    } else {
        cout << "Error deleting job\n";
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
        cout << "4. Update Job\n";
        cout << "5. Delete Job\n";
        cout << "6. Exit\n";
        cout << "7. View Analytics\n";
        cout << "8. Export to CSV\n";
        cout << "Choose option: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid menu option.\n";

            cin.clear();
            cin.ignore(10000, '\n');

            continue;
        }

        cin.ignore();

        switch (choice) {
            case 1:
                addUser(db);
                break;
            case 2:
                addJob(db);
                break;
            case 3:
                listUsersWithJobsGrouped(db);
                break;
            case 4:
                updateJob(db);
                break;
            case 5:
                deleteJob(db);
                break;
            case 6:
                sqlite3_close(db);
                cout << "Goodbye!\n";
                cout << "Press Enter to exit...";
                cin.get();
                return 0;
            case 7:
                viewAnalytics(db);
                break;
            case 8:
                exportToCsv(db);
                break;
            default:
                cout << "Invalid choice\n";
        }
    }
}
