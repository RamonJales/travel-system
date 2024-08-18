#ifndef REPOSITORYROUTE_HPP
#define REPOSITORYROUTE_HPP

#include "../../../sqlite3/sqlite3.h"
#include <iostream> 
#include <list>
#include <vector>
#include "../Route.hpp"

void createTableRoutes(sqlite3* db);
bool addRouteInRoutes(sqlite3* db, Route& route);
bool updateRouteInRoutes(sqlite3* db, const Route newRoute);
Route* findRouteByCities(sqlite3* db, const std::string& originCity, const std::string& destinationCity);
Route* findRouteById(sqlite3* db, const int id);
bool deleteRouteByIdInRoutes(sqlite3* db, const int id);
std::vector<Route> findAllRoutesInRoutes(sqlite3* db);

#endif
