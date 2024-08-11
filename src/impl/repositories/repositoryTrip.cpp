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
            trip_in_progess INTEGER NOT NULL,
            FOREIGN KEY(transport_name) REFERENCES transports(name),
            FOREIGN KEY(origin_city_name) REFERENCES cities(name),
            FOREIGN KEY(destination_city_name) REFERENCES cities(name)
        );
    )";

    char* errorMessage = nullptr;

    // Create the trips table
    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela transports: " << errorMessage << std::endl;
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

bool addTripInTrips(sqlite3* db, const std::string& transportName, const std::string& originCityName, const std::string& destinationCityName, double hoursInRoute) {

    const char* sql_insert = R"(
        INSERT INTO trips (transport_name, origin_city_name, destination_city_name, next_trip_id, hours_in_route, trip_in_progess)
        VALUES (?, ?, ?, ?, NULL, NULL, 0);
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
    sqlite3_bind_int(stmt, 4, hoursInRoute);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir o transporte: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

Trip* findTripById(sqlite3* db, int tripId) {
    const char* sql_select = "SELECT transport_name, origin_city_name, destination_city_name, next_trip_id, hours_in_route, trip_in_progess FROM trips WHERE id = ?;";

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
        int hoursInRoute = sqlite3_column_int(stmt, 4);
        bool tripInProgess = static_cast<bool>(sqlite3_column_int(stmt, 5));

        std::list<Passenger*> passengers = findPassengersInTrip(db, tripId);

        trip = new Trip(findTransportByName(db, transportName), passengers, findCityByName(db, originCityName), findCityByName(db, destinationCityName));
        trip->setNextTrip(findTripById(db, nextTripId));
        trip->setHoursInRoute(hoursInRoute);
        trip->setTripInProgress(tripInProgess);
        trip->setId(tripId);
    }

    sqlite3_finalize(stmt);
    return trip;
}

std::list<Passenger*> findPassengersInTrip(sqlite3* db, int tripId){
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

bool addPassengerInTripDB (sqlite3* db, const int tripId, const Passenger* passenger){
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
        std::cerr << "Erro ao inserir o transporte: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
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
        std::cerr << "Erro ao remover a viagem: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt_pivot);
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_finalize(stmt_pivot);
    return true;
}

bool editTripInTrips(sqlite3* db, const int tripId, const Trip* newTrip) {

    // Tem que adicionar a verificação de se existe trip com esse id na main 
    //     antes de perguntar o resto das informações e chamar essa função

    const char* sql_edit = R"(
        UPDATE trips 
        SET transport_name = ?, origin_city_name = ?, destination_city_name = ?, next_trip_id = ?, hours_in_route = ?, trip_in_progess = ?
        WHERE id = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_edit, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de edição: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, newTrip->getTransport()->getTransportName().c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, newTrip->getOrigin()->getCityName().c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 3, newTrip->getDestination()->getCityName().c_str(), -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 4, newTrip->getNextTrip()->getId()) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 5, newTrip->getHoursInRoute()) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 6, newTrip->getTripInProgress()) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 7, tripId) != SQLITE_OK) {

        std::cerr << "Erro ao vincular os parâmetros: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao alterar o transporte: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool listTripInTrips(sqlite3* db, std::list<Trip*>& trips) {
    const char* sql_select = "SELECT id FROM trips;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    trips.clear();

    // Para cada linha retornada, os dados da viagem são recuperados e um objeto Trip é criado e adicionado à lista de viagens.
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int tripId = sqlite3_column_int(stmt, 0);
        Trip* trip = findTripById(db, tripId);

        // Cria o objeto Trip e adiciona à lista
        trips.push_back(trip);
    }

    sqlite3_finalize(stmt);
    return true;
}