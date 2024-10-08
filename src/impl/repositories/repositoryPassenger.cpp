#include "../../include/repositories/repositoryPassenger.hpp"

void createTablePassengers(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS passengers (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL UNIQUE,
            current_location TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    // Create the passengers table
    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela passengers: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

bool addPassengerInPassengers(sqlite3* db, const std::string& passengerName, const std::string& cityName) {
    const char* sql_insert = R"(
        INSERT INTO passengers (name, current_location)
        VALUES (?, ?);
    )";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Bind the passenger name to the first placeholder
    sqlite3_bind_text(stmt, 1, passengerName.c_str(), -1, SQLITE_STATIC);
    // Bind the city name to the second placeholder
    sqlite3_bind_text(stmt, 2, cityName.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir o passageiro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}


Passenger* findPassengerByName(sqlite3* db, const std::string& passengerName) {
    const char* sql_select = "SELECT name, current_location FROM passengers WHERE name = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, passengerName.c_str(), -1, SQLITE_STATIC);

    Passenger* passenger = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* nameText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* locationText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        if (nameText) {
            std::string name(nameText);
            City* cityPtr = nullptr;

            if (locationText) {
                std::string currentLocation(locationText);
                cityPtr = findCityByName(db, currentLocation);
            }

            if (cityPtr != nullptr) {
                passenger = new Passenger(name, *cityPtr);
            } else {
                City defaultCity;
                passenger = new Passenger(name, defaultCity);
            }
        } else {
            std::cerr << "Error: Passenger name is NULL in database results." << std::endl;
        }
    }

    sqlite3_finalize(stmt);
    return passenger;
}

bool removePassengerInPassengers(sqlite3* db, const std::string& passengerName) {
    Passenger* passenger = findPassengerByName(db, passengerName);
    if (passenger == nullptr) {
        std::cout << "O passageiro informado não existe." << std::endl;
        return false;
    } 
    delete passenger;

    const char* sql_remove = R"(
        DELETE FROM passengers WHERE name = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_remove, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de remoção: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, passengerName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao vincular o id do passageiro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao remover o passageiro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool editPassengerInPassengers(sqlite3* db, Passenger& newPassenger) {
    const char* sql_edit = R"(
        UPDATE passengers 
        SET name = ?, current_location = ?
        WHERE name = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_edit, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de edição: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    const std::string passengerName = newPassenger.getName();
    const std::string passengerLocation = newPassenger.getCurrentLocation().getCityName();

    sqlite3_bind_text(stmt, 1, passengerName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, passengerLocation.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, passengerName.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao alterar o passageiro: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool listPassengerInPassengers(sqlite3* db, std::list<Passenger>& passengers) {
    const char* sql_select = "SELECT name, current_location FROM passengers;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    passengers.clear();

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string currentLocation(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));

        // Cria o objeto Passenger e adiciona à lista
        City* city = currentLocation.empty() ? nullptr : findCityByName(db, currentLocation);
        passengers.emplace_back(name, *city);
    }

    sqlite3_finalize(stmt);
    return true;
}


std::list<Passenger*> findAllPassengers(sqlite3* db) {
    std::list<Passenger*> passengers;

    const char* sql_select_all = R"(
        SELECT id, name, current_location FROM passengers;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select_all, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return passengers;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string cityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));

        // Assuming findCityByName is a function that retrieves a City object by its name.
        City* cityPtr = findCityByName(db, cityName);
        City currentLocation = cityPtr != nullptr ? *cityPtr : City();

        // Create a Passenger object and add it to the list
        Passenger* passenger = new Passenger(name, currentLocation);
        passenger->setId(id);  // Set the passenger's ID
        passengers.push_back(passenger);
    }

    sqlite3_finalize(stmt);
    return passengers;
}