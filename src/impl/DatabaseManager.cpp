#include "../include/DatabaseManager.hpp"


void createTables(sqlite3* db) {
    const char* sql_create_cidades = R"(
        CREATE TABLE IF NOT EXISTS cities (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            populacao INTEGER
        );
    )";

    const char* sql_create_transportes = R"(
        CREATE TABLE IF NOT EXISTS transports (
            id INTEGER PRIMARY KEY,
            kind TEXT NOT NULL,
            capacity INTEGER,
            city_id INTEGER,
            FOREIGN KEY(city_id) REFERENCES cities(id)
        );
    )";

    char* errorMessage = nullptr;

    // Criar a tabela cidades
    int exit = sqlite3_exec(db, sql_create_cidades, nullptr, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela cidades: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Tabela cidades criada com sucesso!" << std::endl;
    }

    // Criar a tabela transportes
    exit = sqlite3_exec(db, sql_create_transportes, nullptr, 0, &errorMessage);
    if (exit != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela transportes: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Tabela transportes criada com sucesso!" << std::endl;
    }
}