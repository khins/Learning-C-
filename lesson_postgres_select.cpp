// connects to a local Postgres database
// selects rows from exercise_session
// prints the table data to the console
#include <cstdlib>
#include <iostream>
#include <string>

#include <libpq-fe.h>
using namespace std;

string getEnvOrDefault(const char* name, const string& fallback) {
    const char* value = getenv(name);

    if (value == nullptr || string(value).empty()) {
        return fallback;
    }

    return value;
}

int main() {
    string host = getEnvOrDefault("PGHOST", "localhost");
    string port = getEnvOrDefault("PGPORT", "5433");
    string dbname = getEnvOrDefault("PGDATABASE", "postgres");
    string user = getEnvOrDefault("PGUSER", "postgres");
    string password = getEnvOrDefault("PGPASSWORD", "");

    string conninfo =
        "host=" + host +
        " port=" + port +
        " dbname=" + dbname +
        " user=" + user +
        " connect_timeout=5";

    if (!password.empty()) {
        conninfo += " password=" + password;
    }

    PGconn* conn = PQconnectdb(conninfo.c_str());

    if (PQstatus(conn) != CONNECTION_OK) {
        cerr << "Connection failed: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return 1;
    }

    cout << "Connected to Postgres successfully!" << endl;

    const char* sql = "SELECT * FROM exercise_session LIMIT 100;";
    PGresult* result = PQexec(conn, sql);

    if (PQresultStatus(result) != PGRES_TUPLES_OK) {
        cerr << "SELECT failed: " << PQerrorMessage(conn) << endl;
        PQclear(result);
        PQfinish(conn);
        return 1;
    }

    int rows = PQntuples(result);
    int columns = PQnfields(result);

    for (int col = 0; col < columns; col++) {
        cout << PQfname(result, col);

        if (col < columns - 1) {
            cout << " | ";
        }
    }

    cout << endl;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (PQgetisnull(result, row, col)) {
                cout << "NULL";
            } else {
                cout << PQgetvalue(result, row, col);
            }

            if (col < columns - 1) {
                cout << " | ";
            }
        }

        cout << endl;
    }

    cout << "Rows returned: " << rows << endl;

    PQclear(result);
    PQfinish(conn);

    cout << "Press Enter to exit...";
    cin.get();

    return 0;
}
