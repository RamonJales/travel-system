#include "../../include/repositories/repositoryRoute.hpp"

#include "../../include/Route.hpp"

void createTableRoutes(sqlite3* db) {
    const char* sql_create = R"(
        CREATE TABLE IF NOT EXISTS routes (
            id INTEGER PRIMARY KEY,
            originCity TEXT NOT NULL,
            destinationCity TEXT NOT NULL,
            routeType TEXT NOT NULL,
            distance REAL NOT NULL CHECK(routeType IN ('LAND', 'AQUATIC'))
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

    sqlite3_bind_text(stmt, 1, route.getOriginCity().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, route.getDestinationCity().c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, routeTypeToString(route.getRouteType()).c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 4, route.getDistance());

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
    const char* sql_select = "SELECT id, routeName, originCity, destinationCity, routeType, distance FROM routes WHERE originCity = ? AND destinationCity = ?;";

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
        std::string routeName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string originCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::string destinationCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        RouteTypeEnum routeType = stringToRouteType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        double distance = sqlite3_column_double(stmt, 5);
        route = new Route(id, routeName, originCity, destinationCity, routeType, distance);
    }

    sqlite3_finalize(stmt);
    return route;
}

Route* findRouteById(sqlite3* db, const int id) {
    const char* sql_select = "SELECT id, routeName, originCity, destinationCity, routeType, distance FROM routes WHERE id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar consulta: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }

    sqlite3_bind_int(stmt, 1, id);

    Route* route = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string routeName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string originCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        std::string destinationCity(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        RouteTypeEnum routeType = stringToRouteType(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
        double distance = sqlite3_column_double(stmt, 5);
        route = new Route(id, routeName, originCity, destinationCity, routeType, distance);
    }

    sqlite3_finalize(stmt);
    return route;
}

bool deleteRouteByIdInRoutes(sqlite3* db, const int id) {
    const char* sql_delete = "DELETE FROM routes WHERE id = ?;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql_delete, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erro ao preparar o SQL: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, id);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Erro ao deletar a rota: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}
