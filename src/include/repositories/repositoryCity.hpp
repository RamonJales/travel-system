#ifndef REPOSITORYCITY_HPP
#define REPOSITORYCITY_HPP

#include "../../../sqlite3/sqlite3.h"
#include <iostream>
#include <list>
#include "../City.hpp"

void createTableCities(sqlite3* db);
bool addCityInCities(sqlite3* db, const std::string& cityName);
bool cityExistsInDatabase(sqlite3* db, const std::string& cityName);
bool removeCityInCities(sqlite3* db, int cityId);
bool editCityInCities(sqlite3* db, int cityId, const std::string& newName);
bool listCityInCities(sqlite3* db, std::list<City>& cities);

#endif