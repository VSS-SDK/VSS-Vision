/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "sqlite.h"


SQLite::SQLite(string path_database, string password){
    this->path_database = path_database;
    this->password = password;
}

//! Addendum
//! --------
//! 
void SQLite::open(){
    status_db = sqlite3_open(path_database.c_str(), &db);

    //! > Return any error, if something happen when try to open the database
    if(status_db){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
}

void SQLite::close(){
    sqlite3_close(db);
}

//! Addendum
//! --------
//! 
int SQLite::callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;

   //! > Print the info like on the table in database
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


void SQLite::insert_calibration(){

}

void SQLite::select_calibration(string s){

}

