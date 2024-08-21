#include "../../include/repositories/repositoryTrip.hpp"

void createTableTrips(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS trips (
            id INTEGER PRIMARY KEY,
            transport_name INTEGER NOT NULL,
            origin_city_name TEXT NOT NULL,
            destination_city_name TEXT NOT NULL,
            next_trip_id INTEGER,
            hours_in_route DOUBLE,
            trip_in_progress INTEGER NOT NULL,
            FOREIGN KEY(transport_name) REFERENCES transports(name),
            FOREIGN KEY(origin_city_name) REFERENCES cities(name),
            FOREIGN KEY(destination_city_name) REFERENCES cities(name)
        );
    )";

    char* errorMessage = nullptr;

    // Create the trips table
    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela trips: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }

    const char* sql_create_pivot = R"(
        CREATE TABLE IF NOT EXISTS pivot_trips_passengers (
            id INTEGER PRIMARY KEY,
            trip_id INTEGER NOT NULL,
            passenger_name TEXT NOT NULL,
            FOREIGN KEY(trip_id) REFERENCES trips(id),
            FOREIGN KEY(passenger_name) REFERENCES passengers(name)
        );
    )";

    // Create the pivot table
    if (sqlite3_exec(db, sql_create_pivot, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela pivot: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

bool addTripInTrips(sqlite3* db, const std::string& transportName, const std::string& originCityName, const std::string& destinationCityName, const double hoursInRoute, const std::list<Passenger*> passengers, const bool inProgress) {
    const char* sql_insert = R"(
        INSERT INTO trips (transport_name, origin_city_name, destination_city_name, hours_in_route, trip_in_progress)
        VALUES (?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }


    // Vincula os parâmetros ao comando SQL
    sqlite3_bind_text(stmt, 1, transportName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, originCityName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, destinationCityName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, hoursInRoute);
    sqlite3_bind_int(stmt, 5, inProgress ? 1 : 0); // Define o valor de inProgress como 1 (verdadeiro) ou 0 (falso)

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir a viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Captura o ID da linha recém-criada
    int tripId = sqlite3_last_insert_rowid(db);

    sqlite3_finalize(stmt);
    addPassengersInTripDB(db, tripId, passengers);
    return true;
}

Trip* findTripById(sqlite3* db, int tripId) {
    const char* sql_select = "SELECT transport_name, origin_city_name, destination_city_name, next_trip_id, hours_in_route, trip_in_progress FROM trips WHERE id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, tripId);

    Trip* trip = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string transportName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string originCityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string destinationCityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        int nextTripId = sqlite3_column_int(stmt, 3);
        double hoursInRoute = sqlite3_column_double(stmt, 4);
        bool tripInProgress = static_cast<bool>(sqlite3_column_int(stmt, 5));

        Transport* transport = findTransportByName(db, transportName);
        City* originCity = findCityByName(db, originCityName);
        City* destinationCity = findCityByName(db, destinationCityName);

        if (transport == nullptr) {
            std::cerr << "Erro: Transporte não encontrado para o nome " << transportName << std::endl;
        }

        if (originCity == nullptr) {
            std::cerr << "Erro: Cidade de origem não encontrada para o nome " << originCityName << std::endl;
        }

        if (destinationCity == nullptr) {
            std::cerr << "Erro: Cidade de destino não encontrada para o nome " << destinationCityName << std::endl;
        }

        if (transport == nullptr || originCity == nullptr || destinationCity == nullptr) {
            std::cerr << "Erro: Ponteiros nulos encontrados em Trip ID " << tripId << "." << std::endl;
            sqlite3_finalize(stmt);
            return nullptr;
        }

        std::list<Passenger*> passengers = findPassengersInTrip(db, tripId);
        trip = new Trip(transport, passengers, originCity, destinationCity);
        
        Trip* nextTrip = findTripById(db, nextTripId);
        if (nextTripId != 0 && nextTrip == nullptr) {
            std::cerr << "Erro: Próxima viagem com ID " << nextTripId << " não encontrada para Trip ID " << tripId << "." << std::endl;
        }
        trip->setNextTrip(nextTrip);

        trip->setHoursInRoute(hoursInRoute);
        trip->setTripInProgress(tripInProgress);
        trip->setId(tripId);
    }

    sqlite3_finalize(stmt);
    return trip;
}


std::list<Passenger*> findPassengersInTrip(sqlite3* db, int tripId) {
    std::list<Passenger*> passengers;
    const char* sql_select = "SELECT passenger_name FROM pivot_trips_passengers WHERE trip_id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return passengers;
    }

    sqlite3_bind_int(stmt, 1, tripId);

    // Para cada linha retornada, os dados do passageiro são recuperados e um objeto Passenger é criado e adicionado à lista de passageiros.
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string passengerName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));

        // Cria o objeto Passenger e adiciona à lista
        passengers.emplace_back(findPassengerByName(db, passengerName));
    }

    sqlite3_finalize(stmt);
    return passengers;
}

bool addPassengersInTripDB(sqlite3* db, const int tripId, const std::list<Passenger*> passengers) {
    for (Passenger* passenger : passengers) {
        const char* sql_insert = R"(
            INSERT INTO pivot_trips_passengers (trip_id, passenger_name)
            VALUES (?, ?);
        )";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);
        if (rc != SQLITE_OK) {
            std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        // Vincula os parâmetros ao comando SQL
        sqlite3_bind_int(stmt, 1, tripId);
        sqlite3_bind_text(stmt, 2, passenger->getName().c_str(), -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Erro ao inserir passageiros: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
    }
    return true;
}

bool removeTripInTrips(sqlite3* db, const int tripId) {
    Trip* trip = findTripById(db, tripId);
    if (trip == nullptr) {
        std::cout << "A viagem informada não existe." << std::endl;
        return false;
    }
    delete trip;

    const char* sql_remove = R"(
        DELETE FROM trips WHERE id = ?;
    )";
    const char* sql_remove_pivot = R"(
        DELETE FROM pivot_trips_passengers WHERE trip_id = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_remove, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de remoção: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_stmt* stmt_pivot = nullptr;
    if (sqlite3_prepare_v2(db, sql_remove_pivot, -1, &stmt_pivot, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de remoção no pivot: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_int(stmt, 1, tripId) != SQLITE_OK) {
        std::cerr << "Erro ao vincular o id da viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    if (sqlite3_bind_int(stmt_pivot, 1, tripId) != SQLITE_OK) {
        std::cerr << "Erro ao vincular o id da viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt_pivot);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao remover a viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }
    if (sqlite3_step(stmt_pivot) != SQLITE_DONE) {
        std::cerr << "Erro ao remover passageiros da viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt_pivot);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_finalize(stmt_pivot);
    return true;
}

bool editTripInTrips(sqlite3* db, Trip* trip) {
    const char* sql = R"(
        UPDATE trips
        SET origin_city_name = ?, destination_city_name = ?, transport_name = ?, hours_in_route = ?, trip_in_progress = ?
        WHERE id = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, trip->getOrigin()->getCityName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, trip->getDestination()->getCityName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, trip->getTransport()->getTransportName().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, trip->getHoursInRoute());
    sqlite3_bind_int(stmt, 5, trip->isTripInProgress() ? 1 : 0); // Define o valor de trip_in_progress como 1 (verdadeiro) ou 0 (falso)
    sqlite3_bind_int(stmt, 6, trip->getId());

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao atualizar a viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool updateTripInProgress(sqlite3* db, int tripId, bool inProgress) {
    const char* sql_update = R"(
        UPDATE trips
        SET trip_in_progress = ?
        WHERE id = ?;
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_update, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, inProgress ? 1 : 0); // Define o valor de trip_in_progress como 1 (verdadeiro) ou 0 (falso)
    sqlite3_bind_int(stmt, 2, tripId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao atualizar o status da viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

std::list<Trip*> listTripInTrips(sqlite3* db) {
    std::list<Trip*> trips;

    const char* sql_select_all = "SELECT id FROM trips;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select_all, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return trips;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int tripId = sqlite3_column_int(stmt, 0);
        Trip* trip = findTripById(db, tripId);
        if (trip) {
            trips.push_back(trip);
        }
    }

    sqlite3_finalize(stmt);
    return trips;
}

std::list<Trip*> listTripsInProgress(sqlite3* db) {
    std::list<Trip*> trips;

    const char* sql_select_in_progress = "SELECT id FROM trips WHERE trip_in_progress = 1;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select_in_progress, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return trips;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int tripId = sqlite3_column_int(stmt, 0);
        Trip* trip = findTripById(db, tripId);
        if (trip != nullptr) {
            trips.push_back(trip);
        } else {
            std::cerr << "Erro: Viagem com ID " << tripId << " não foi adicionada à lista por conter ponteiros nulos." << std::endl;
        }
    }

    sqlite3_finalize(stmt);
    return trips;
}

bool advanceHours(sqlite3* db, double hours) {
    // Lista todas as viagens em progresso
    std::list<Trip*> tripsInProgress = listTripsInProgress(db);

    if (tripsInProgress.empty()) {
        std::cout << "Não há viagens em andamento." << std::endl;
        return true;
    }

    for (Trip* trip : tripsInProgress) {
        if (trip == nullptr) {
            std::cerr << "Erro: Ponteiro nulo encontrado na lista de viagens em andamento." << std::endl;
            continue;
        }

        double newHoursInRoute = trip->getHoursInRoute() - hours;
        std::cout << "Horas restantes para a viagem ID " << trip->getId() << ": " << newHoursInRoute << std::endl;

        if (newHoursInRoute <= 0) {
            newHoursInRoute = 0;
            trip->setTripInProgress(false);
            std::cout << "Viagem de " << trip->getOrigin()->getCityName() 
                                            << " para " << trip->getDestination()->getCityName() 
                                            << " finalizada." << std::endl;
            
            // Atualiza a localização do transporte para o destino
            std::list<Transport*> transports = findAllTransports(db);
            for (Transport* transport : transports) {
                if (transport->isInTrip()) {
                    transport->setCurrentPlace(trip->getDestination());
                    transport->setTripStatus(false, 0);
                }
            }
        } else {
             std::cout << "Viagem de " << trip->getOrigin()->getCityName() 
                                            << " para " << trip->getDestination()->getCityName() 
                                            << " em andamento." << std::endl;
        }

        trip->setHoursInRoute(newHoursInRoute);

        // Atualiza o valor de hours_in_route e o status da viagem no banco de dados
        const char* sql_update = R"(
            UPDATE trips
            SET hours_in_route = ?, trip_in_progress = ?
            WHERE id = ?;
        )";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql_update, -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "Erro ao preparar SQL: " << sqlite3_errmsg(db) << std::endl;
            return false;
        }

        sqlite3_bind_double(stmt, 1, newHoursInRoute);
        sqlite3_bind_int(stmt, 2, trip->isTripInProgress() ? 1 : 0);
        sqlite3_bind_int(stmt, 3, trip->getId());

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Erro ao atualizar a viagem: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return false;
        }

        sqlite3_finalize(stmt);
    }

    // Limpa a lista de viagens
    for (Trip* trip : tripsInProgress) {
        delete trip;
    }

    return true;
}

