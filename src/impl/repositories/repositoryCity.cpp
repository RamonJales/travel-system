#include "../../include/repositories/repositoryCity.hpp"

void createTableCities(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS cities (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    // Create the cities table
    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela cities: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}