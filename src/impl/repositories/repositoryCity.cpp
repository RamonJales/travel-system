#include "../../include/repositories/repositoryCity.hpp"

void createTableCities(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS cities (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL UNIQUE
        );
    )";

    char* errorMessage = nullptr;

    // Create the cities table
    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela cities: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

bool addCityInCities(sqlite3* db, const std::string& cityName) {

    City* city = findCityByName(db, cityName);
    if (city != nullptr) {
        std::cout << "A cidade \"" << cityName << "\" já está cadastrada no banco de dados." << std::endl;
        delete city;
        return false;
    }

    const char* sql_insert = R"(
        INSERT INTO cities (name) VALUES (?);
    )";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Bind the cityName parameter
    sqlite3_bind_text(stmt, 1, cityName.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir a cidade: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

City* findCityByName(sqlite3* db, const std::string& name) {
    const char* sql_select = "SELECT name FROM cities WHERE name = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    City* city = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string cityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        city = new City(cityName);
    }

    sqlite3_finalize(stmt);
    return city;
}

bool removeCityInCities(sqlite3* db, const std::string& cityName) {

    City* city = findCityByName(db, cityName);
    if (city == nullptr) {
        std::cout << "A cidade \"" << cityName << "\" não existe." << std::endl;
        return false;
    } 
    delete city;

    const char* sql_remove = R"(
        DELETE FROM cities WHERE name = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_remove, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de remoção: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, cityName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao vincular o nome da cidade: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao remover a cidade: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool editCityInCities(sqlite3* db, const std::string& cityName, const std::string& newName) {

    City* city = findCityByName(db, cityName);
    if (city == nullptr) {
        std::cout << "A cidade \"" << cityName << "\" não existe." << std::endl;
        return false;
    }
    delete city;

    const char* sql_edit = R"(
        UPDATE cities SET name = ? WHERE name = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_edit, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de edição: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, newName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao vincular o novo nome: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_bind_text(stmt, 2, cityName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao vincular o nome atual da cidade: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao alterar a cidade: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool listCityInCities(sqlite3* db, std::list<City>& cities) {
    const char* sql_select = "SELECT name FROM cities;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    cities.clear();

    // Para cada linha retornada, o nome da cidade é recuperado e um objeto City é criado e adicionado a list cities.
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string cityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        cities.emplace_back(cityName);
    }

    sqlite3_finalize(stmt);
    return true;
}
