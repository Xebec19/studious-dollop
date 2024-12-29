#include <iostream>
#include <sqlite3.h>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem;

void listFiles(const fs::path &path, sqlite3 *db)
{
    try
    {
        // Check if the path exists
        if (!fs::exists(path))
        {
            std::cout << "Path does not exist!" << std::endl;
            return;
        }

        // Iterate through the directory
        for (const auto &entry : fs::directory_iterator(path))
        {
            std::cout << entry.path() << std::endl;

            // Insert the entry into the database
            std::string insertQuery = "INSERT INTO files(path, type) VALUES('" + entry.path().string() + "', '" + (fs::is_directory(entry.path()) ? "directory" : "file") + "');";
            char *errorMessage;
            int exit = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, &errorMessage);
            if (exit != SQLITE_OK)
            {
                std::cerr << "Error inserting data: " << errorMessage << std::endl;
                sqlite3_free(errorMessage); // Free the error message
            }

            // If the entry is a directory, list its contents
            if (fs::is_directory(entry.path()))
            {
                listFiles(entry.path(), db);
            }
        }
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::string readConfig(const std::string &configFilePath)
{
    std::ifstream configFile(configFilePath);
    std::string path;
    if (configFile.is_open())
    {
        std::getline(configFile, path);
        configFile.close();
    }
    else
    {
        std::cerr << "Unable to open config file" << std::endl;
    }
    return path;
}

int main(int argc, char *argv[])
{
    std::string configFilePath = "config.txt";
    std::string path = readConfig(configFilePath);

    if (path.empty())
    {
        std::cerr << "Path not found in config file" << std::endl;
        return -1;
    }

    sqlite3 *db;
    char *errorMessage;
    int exit = sqlite3_open("example.db", &db);

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    const char *createTableQuery = "CREATE TABLE IF NOT EXISTS files (id INTEGER PRIMARY KEY, path TEXT, type TEXT);";
    exit = sqlite3_exec(db, createTableQuery, nullptr, nullptr, &errorMessage);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error creating table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage); // Free the error message
    }

    listFiles(path, db);

    sqlite3_close(db);

    return 0;
}