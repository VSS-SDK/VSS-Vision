#ifndef SQLITE_H
#define SQLITE_H

#include <stdio.h>

#include "iostream"
#include "sstream"

#include <sqlite3.h>

using namespace std;

class SQLite{
    sqlite3 *db;

    string path_database;
    string password;

    stringstream query;

    int status_db;
    char *error_query;
    const char* data;

    static int callback(void *NotUsed, int argc, char **argv, char **azColName);
    void clean_query();
public:
    SQLite(string, string);
    void open();
    void close();

    void insert_calibration();
    void select_calibration(string s = "");
};

#endif // SQLITE_H
