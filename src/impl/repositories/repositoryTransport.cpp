#include "../../include/repositories/repositoryTransport.hpp"

TransportTypeEnum stringToTransportType(const std::string& typeString) {
    static const std::unordered_map<std::string, TransportTypeEnum> typeMap = {
        {"GROUND", GROUND},
        {"WATER", WATER}
    };
    
    auto it = typeMap.find(typeString);
    if (it != typeMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Tipo de transporte inválido");
}

std::string transportTypeToString(TransportTypeEnum type) {
    switch (type) {
        case GROUND: return "GROUND";
        case WATER: return "WATER";
        default: throw std::invalid_argument("Tipo de transporte inválido");
    }
}

void createTableTransports(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS transports (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL UNIQUE,
            type TEXT NOT NULL,
            capacity INTEGER NOT NULL,
            speed REAL NOT NULL,
            distance_between_rest REAL NOT NULL,
            rest_time REAL NOT NULL,
            current_rest_time REAL NOT NULL,
            current_place TEXT,
            transport_in_progress INTEGER NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    // Create the transports table
    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela transports: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

bool addTransportInTransports(sqlite3* db, const std::string& transportName, const std::string& type, const int capacity, const float speed,
    const float distanceBetweenRest, const float restTime, const std::string currentPlace, const bool inProgress) {

    const char* sql_insert = R"(
        INSERT INTO transports (name, type, capacity, speed, distance_between_rest, rest_time, current_rest_time, current_place, transport_in_progress)
        VALUES (?, ?, ?, ?, ?, ?, 0, ?, ?);
    )";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Vincula os parâmetros ao comando SQL
    sqlite3_bind_text(stmt, 1, transportName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, type.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, capacity);
    sqlite3_bind_double(stmt, 4, speed);
    sqlite3_bind_double(stmt, 5, distanceBetweenRest);
    sqlite3_bind_double(stmt, 6, restTime);
    sqlite3_bind_text(stmt, 7, currentPlace.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 8, inProgress ? 1 : 0); 

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir o transporte: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

Transport* findTransportByName(sqlite3* db, const std::string& transportName) {
    const char* sql_select = "SELECT name, type, capacity, speed, distance_between_rest, rest_time, current_rest_time, current_place, transport_in_progress FROM transports WHERE name = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, transportName.c_str(), -1, SQLITE_STATIC);

    Transport* transport = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string transportName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string typeString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        int capacity = sqlite3_column_int(stmt, 2);
        float speed = static_cast<float>(sqlite3_column_double(stmt, 3));
        float distanceBetweenRest = static_cast<float>(sqlite3_column_double(stmt, 4));
        float restTime = static_cast<float>(sqlite3_column_double(stmt, 5));
        float currentRestTime = static_cast<float>(sqlite3_column_double(stmt, 6));
        const unsigned char* cityNameText = sqlite3_column_text(stmt, 7);
        std::string currentPlace = cityNameText ? reinterpret_cast<const char*>(cityNameText) : "";
        int inProgressInt = sqlite3_column_int(stmt, 8);
        bool inProgress = (inProgressInt == 1);

        // Converte a string para TransportTypeEnum
        TransportTypeEnum type = stringToTransportType(typeString);

        transport = new Transport(transportName, type, capacity, speed, distanceBetweenRest, restTime, currentRestTime, findCityByName(db, currentPlace));
        transport->isInProgress();
    }

    sqlite3_finalize(stmt);
    return transport;
}

bool removeTransportInTransports(sqlite3* db, const std::string& transportName) {

    Transport* transport = findTransportByName(db, transportName);
    if (transport == nullptr) {
        std::cout << "O transporte informado não existe." << std::endl;
        return false;
    } 
    delete transport;

    const char* sql_remove = R"(
        DELETE FROM transports WHERE name = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_remove, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de remoção: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, transportName.c_str(), -1, SQLITE_STATIC) != SQLITE_OK) {
        std::cerr << "Erro ao vincular o nome do transporte: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao remover o transporte: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool editTransportInTransports(sqlite3* db, const Transport& newTransport) {

    const char* sql_edit = R"(
        UPDATE transports 
        SET name = ?, type = ?, capacity = ?, speed = ?, distance_between_rest = ?, rest_time = ?, current_rest_time = ?, current_place = ?, transport_in_progress = ?
        WHERE name = ?;
    )";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql_edit, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL de edição: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    const std::string transportName = newTransport.getTransportName();
    const std::string transportTypeStr = transportTypeToString(newTransport.getTransportType());
    const int transportCapacity = newTransport.getCapacity();
    const double transportSpeed = newTransport.getSpeed();
    const double transportDistanceBetweenRest = newTransport.getDistanceBetweenRest();
    const double transportRestTime = newTransport.getRestTime();
    const double transportCurrentRestTime = newTransport.getCurrentRestTime();
    const std::string transportCurrentPlaceStr = newTransport.getCurrentPlace()->getCityName();
    const int transportInProgress = newTransport.isInProgress() ? 1 : 0;

    sqlite3_bind_text(stmt, 1, transportName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, transportTypeStr.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, transportCapacity);
    sqlite3_bind_double(stmt, 4, transportSpeed);
    sqlite3_bind_double(stmt, 5, transportDistanceBetweenRest);
    sqlite3_bind_double(stmt, 6, transportRestTime);
    sqlite3_bind_double(stmt, 7, transportCurrentRestTime);
    sqlite3_bind_text(stmt, 8, transportCurrentPlaceStr.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 9, transportInProgress);
    sqlite3_bind_text(stmt, 10, transportName.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Erro ao alterar o transporte: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}


bool listTransportInTransports(sqlite3* db, std::list<Transport>& transports) {
    const char* sql_select = "SELECT name, type, capacity, speed, distance_between_rest, rest_time, current_rest_time, current_place, transport_in_progress FROM transports;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    transports.clear();

    // Para cada linha retornada, os dados do transporte são recuperados e um objeto Transport é criado e adicionado à lista de transportes.
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string typeString(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        int capacity = sqlite3_column_int(stmt, 2);
        float speed = static_cast<float>(sqlite3_column_double(stmt, 3));
        float distanceBetweenRest = static_cast<float>(sqlite3_column_double(stmt, 4));
        float restTime = static_cast<float>(sqlite3_column_double(stmt, 5));
        float currentRestTime = static_cast<float>(sqlite3_column_double(stmt, 6));
        std::string currentPlace(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));
        int inProgressInt = sqlite3_column_int(stmt, 8);
        bool inProgress = (inProgressInt == 1);

        // Converte a string para TransportTypeEnum
        TransportTypeEnum type = stringToTransportType(typeString);

        // Cria o objeto Transport e adiciona à lista
        transports.emplace_back(name, type, capacity, speed, distanceBetweenRest, restTime, currentRestTime, findCityByName(db, currentPlace));
        transports.back().isInProgress(); // Assume a setter method exists
    }

    sqlite3_finalize(stmt);
    return true;
}

std::list<Transport*> findAllTransports(sqlite3* db) {
    std::list<Transport*> transports;

    const char* sql_select_all = "SELECT name FROM transports;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select_all, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return transports;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string transportName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        Transport* transport = findTransportByName(db, transportName);
        if (transport) {
            transports.push_back(transport);
        }
    }

    sqlite3_finalize(stmt);
    return transports;
}

