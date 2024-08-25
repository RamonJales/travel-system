#include "../../include/repositories/repositoryRoute.hpp"

#include "../../include/Route.hpp"

void createTableRoutes(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS routes (
            id INTEGER PRIMARY KEY,
            originCity TEXT NOT NULL,
            destinationCity TEXT NOT NULL,
            routeType TEXT NOT NULL CHECK(routeType IN ('LAND', 'AQUATIC')),
            distance REAL NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    if (sqlite3_exec(db, sql_create, nullptr, 0, &errorMessage) != SQLITE_OK) {
        std::cerr << "Erro ao criar a tabela routes: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
}

bool addRouteInRoutes(sqlite3* db, Route& route) {
    const char* sql_insert = R"(
        INSERT INTO routes (originCity, destinationCity, routeType, distance) VALUES (?, ?, ?, ?);
    )";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    const std::string originCity = route.getOriginCity();
    const std::string destinationCity = route.getDestinationCity();
    const std::string routeTypeStr = routeTypeToString(route.getRouteType());
    const float distance = route.getDistance();

    sqlite3_bind_text(stmt, 1, originCity.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, destinationCity.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, routeTypeStr.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, distance);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao inserir a rota: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool updateRouteInRoutes(sqlite3* db, Route newRoute) {
    const char* sql_update = R"(
        UPDATE routes SET originCity = ?, destinationCity = ?, routeType = ?, distance = ? WHERE id = ?;
    )";

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql_update, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, newRoute.getOriginCity().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, newRoute.getDestinationCity().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, routeTypeToString(newRoute.getRouteType()).c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, newRoute.getDistance());
    sqlite3_bind_int(stmt, 5, newRoute.getId());

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao atualizar a rota: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

Route* findRouteByCities(sqlite3* db, const std::string& originCity, const std::string& destinationCity) {
    const char* sql_select = "SELECT id, originCity, destinationCity, routeType, distance FROM routes WHERE originCity = ? AND destinationCity = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_text(stmt, 1, originCity.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, destinationCity.c_str(), -1, SQLITE_STATIC);

    Route* route = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string originCityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string destinationCityName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        RouteTypeEnum routeType = stringToRouteType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        float distance = sqlite3_column_double(stmt, 4);
        route = new Route(originCityName, destinationCityName, routeType, distance);
    }

    sqlite3_finalize(stmt);
    return route;
}

Route* findRouteById(sqlite3* db, const int id) {
    const char* sql_select = "SELECT id, originCity, destinationCity, routeType, distance FROM routes WHERE id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    Route* route = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string originCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string destinationCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        RouteTypeEnum routeType = stringToRouteType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        float distance = sqlite3_column_double(stmt, 4);
        route = new Route(originCity, destinationCity, routeType, distance);
    }

    sqlite3_finalize(stmt);
    return route;
}

bool deleteRouteByIdInRoutes(sqlite3* db, const std::string originCityName, const std::string destinationCityName) {
    const char* sql_delete = "DELETE FROM routes WHERE originCity = ? AND destinationCity = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_delete, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, originCityName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, destinationCityName.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao deletar a rota: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

std::vector<Route> findAllRoutesInRoutes(sqlite3* db) {
    const char* sql_select = "SELECT originCity, destinationCity, routeType, distance FROM routes;";

    sqlite3_stmt* stmt;
    std::vector<Route> routes;

    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return routes;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string originCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
        std::string destinationCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        RouteTypeEnum routeType = stringToRouteType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        float distance = sqlite3_column_double(stmt, 3);

        Route route(originCity, destinationCity, routeType, distance);
        routes.push_back(route);
    }

    sqlite3_finalize(stmt);
    return routes;
}
