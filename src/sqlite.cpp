/*
 * This file is part of the VSS-Vision project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */

#include "sqlite.h"
#include "qdebug.h"

vector<Calibration> calibrations_s;

SQLite::SQLite(){

}

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

//! Addendum
//! --------
//! 
int SQLite::callback_calibration(void *NotUsed, int argc, char **argv, char **azColName){
    Calibration c;
    stringstream ss;
    c.comment = " ";
    c.colors.clear();
    c.cut.clear();

    string teste(argv[0]);
    c.comment = teste;

    for(int i = 1 ; i < 9 ; i++){
        Pixel min, max;
        string s = argv[i];
        clearSS(ss);

        int j = 0;
        while(s[j] != ':'){
            ss << s[j];
            j++;
        }
        j++;

        ss >> min.rgb[0];
        clearSS(ss);
        while(s[j] != ':'){
            ss << s[j];
            j++;
        }
        j++;

        ss >> min.rgb[1];
        clearSS(ss);
        while(s[j] != ':'){
            ss << s[j];
            j++;
        }
        j++;

        ss >> min.rgb[2];
        clearSS(ss);
        while(s[j] != ':'){
            ss << s[j];
            j++;
        }
        j++;

        ss >> max.rgb[0];
        clearSS(ss);
        while(s[j] != ':'){
            ss << s[j];
            j++;
        }
        j++;

        ss >> max.rgb[1];
        clearSS(ss);
        while(s[j] != ':'){
            ss << s[j];
            j++;
        }
        j++;

        ss >> max.rgb[2];
        clearSS(ss);
        while(s[j] != ':'){
            ss << s[j];
            j++;
        }

        c.colors.push_back(VisionColor(min, max));
    }

    clearSS(ss);
    ss << argv[9];
    ss >> c.rotation;

    Point cut[2];

    string s = argv[10];

    int j = 0;
    while(s[j] != ':'){
        ss << s[j];
        j++;
    }
    j++;

    ss >> cut[0].x;
    clearSS(ss);
    while(s[j] != ':'){
        ss << s[j];
        j++;
    }
    j++;

    ss >> cut[0].y;
    clearSS(ss);
    while(s[j] != ':'){
        ss << s[j];
        j++;
    }
    j++;

    ss >> cut[1].x;
    clearSS(ss);
    while(s[j] != ':'){
        ss << s[j];
        j++;
    }
    j++;

    ss >> cut[1].y;
    
    c.cut.push_back(cut[0]);
    c.cut.push_back(cut[1]);

    clearSS(ss);
    ss << argv[11];

    c.data = ss.str();

    calibrations_s.push_back(c);

    return 0;
}



bool SQLite::insert_calibration(Calibration c){
    bool ok = true;

    if(c.comment != "lorem"){
        stringstream query;
        time_t t = time(0);   // get time now
        struct tm * now = localtime( & t );

        query << "INSERT INTO calibration (name, orange, blue, yellow, red, pink, purple, green, brown, rotation, cut, date_of)";
        query << " VALUES (";

            query << "'" << c.comment << "'" << ", ";

            for(int i = 0 ; i < c.colors.size() ; i++){
                query << "'";
                for(int j = 0 ; j < 3 ; j++){
                    query << c.colors.at(i).min.rgb[j] << ":";
                }
                for(int j = 0 ; j < 3 ; j++){
                    if(j != 2){
                        query << c.colors.at(i).max.rgb[j] << ":";
                    }else{
                        query << c.colors.at(i).max.rgb[j] << "'";
                    }
                }
                query << ", ";
            }

            query << "'" << c.rotation << "'" <<  ", ";

            query << "'" << c.cut.at(0).x << ":" << c.cut.at(0).y << ":" << c.cut.at(1).x << ":" << c.cut.at(1).y << "', " ;
            
            query << "'"
                << (now->tm_year + 1900)
                << (now->tm_mon + 1)
                <<  now->tm_mday
                << now->tm_hour
                << now->tm_min
                << now->tm_sec << "'";

        query << ")";

        //cout << query.str() << endl;

        open();
            status_db = sqlite3_exec(db, query.str().c_str(), callback, 0, &error_query);
            if(status_db != SQLITE_OK){
                fprintf(stderr, "SQL error: %s\n", error_query);
                sqlite3_free(error_query);
            }
        close();
    }else{
        ok = false;
    }
    return ok;
}

vector<Calibration> SQLite::select_calibration(string s){
    calibrations_s.clear();
    stringstream query;

    if(s == ""){
        query << "SELECT * FROM calibration";
    }else{
        query << "SELECT * FROM calibration WHERE name='" << s << "'"; 
    }

    open();
        status_db = sqlite3_exec(db, query.str().c_str(), callback_calibration, 0, &error_query);
        if(status_db != SQLITE_OK){
            fprintf(stderr, "SQL error: %s\n", error_query);
            sqlite3_free(error_query);
        }
    close();

    return calibrations_s;
}

