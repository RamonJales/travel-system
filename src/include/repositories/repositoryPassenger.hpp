#ifndef REPOSITORYPASSENGER_HPP
#define REPOSITORYPASSENGER_HPP

#include "../../../sqlite3/sqlite3.h"
#include "./repositoryCity.hpp"
#include "../Passenger.hpp"
#include "../City.hpp"
#include <iostream>

void createTablePassengers(sqlite3* db);
bool addPassengerInPassengers(sqlite3* db, const std::string& passengerName);
Passenger* findPassengerByName(sqlite3* db, const std::string& passengerName);
bool removePassengerInPassengers(sqlite3* db, const std::string& passengerName);
bool editPassengerInPassengers(sqlite3* db, const std::string& passengerName, const Passenger* newPassenger);
bool listPassengerInPassengers(sqlite3* db, std::list<Passenger>& passengers);

#endif