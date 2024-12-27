#include<bits/stdc++.h>
#include<sqlite3.h>

int main() {
    sqlite3* db;
    char* errorMessage;
    int exit = sqlite3_open("example.db", &db);

    if(exit != SQLITE_OK) {
        std::cerr<<"Error opening database: "<<sqlite3_errmsg(db)<<std::endl;

        return -1;
    }

    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY, name TEXT);";
    exit = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage);
    if(exit != SQLITE_OK) {
        std::cerr<<"Error creating table: " << errorMessage <<std::endl;
        sqlite3_free(errorMessage);
    }

    const char* insertQuery = "INSERT INTO students(id, name) VALUES(1,'Rohan');";
    exit = sqlite3_exec(db, insertQuery, nullptr, nullptr, &errorMessage);

    if(exit != SQLITE_OK){
        std::cerr<<"Error inserting data: "<<errorMessage<<std::endl;
        sqlite3_free(errorMessage);
    }

    const char* selectQuery = "SELECT * FROM students;";
    sqlite3_stmt* stmt;
    exit = sqlite3_prepare_v2(db,selectQuery, -1,&stmt, nullptr);
    if(exit == SQLITE_OK) {
        while(sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt,0);
            const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
            std::cout<<"ID: " <<id<<", Name: "<<name<<std::endl;
        }
    }
    sqlite3_finalize(stmt);

    sqlite3_close(db);
    return 0;
}
