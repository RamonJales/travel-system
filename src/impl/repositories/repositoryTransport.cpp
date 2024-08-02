#include "../../include/repositories/repositoryTransport.hpp"

void createTableTransports(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS transports (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            type TEXT NOT NULL,
            capacity INTEGER NOT NULL,
            speed REAL NOT NULL,
            distance_between_rest REAL NOT NULL,
            rest_time REAL NOT NULL,
            current_rest_time REAL NOT NULL,
            current_place TEXT,
            FOREIGN KEY(current_place) REFERENCES cities(name)
        );
    )";

    char* errorMessage = nullptr;

    // Create the transports table
    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela transports: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}