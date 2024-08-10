#ifndef REPOSITORYCITY_HPP
#define REPOSITORYCITY_HPP

#include "../../../sqlite3/sqlite3.h"
#include <iostream>
#include <list>
#include "../City.hpp"

void createTableCities(sqlite3* db);
bool addCityInCities(sqlite3* db, const std::string& cityName);
City* findCityByName(sqlite3* db, const std::string& name);
bool removeCityInCities(sqlite3* db, const std::string& cityName);
bool editCityInCities(sqlite3* db, const std::string& cityName, const City* newCity);
bool listCityInCities(sqlite3* db, std::list<City>& cities);

#endif