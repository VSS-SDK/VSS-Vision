#include "sqlite.h"

SQLite::SQLite(string path_database, string password){
    this->path_database = path_database;
    this->password = password;
}

void SQLite::open(){
    status_db = sqlite3_open(path_database.c_str(), &db);

    if(status_db){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
}

void SQLite::close(){
    sqlite3_close(db);
}

int SQLite::callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void SQLite::clean_query(){
    query.str(string());
    query.clear();
}

void SQLite::insert_calibration(){

}

void SQLite::select_calibration(string s){

}

