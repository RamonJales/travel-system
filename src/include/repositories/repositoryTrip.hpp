#ifndef REPOSITORYTRIP_HPP
#define REPOSITORYTRIP_HPP

#include "../../../sqlite3/sqlite3.h"
#include "../Trip.hpp"
#include "./repositoryCity.hpp"
#include "./repositoryPassenger.hpp"
#include "./repositoryTransport.hpp"
#include <iostream>
#include <list>

void createTableTrips(sqlite3* db);
bool addTripInTrips(sqlite3* db, const std::string& transportName, const std::string& originCityName, const std::string& destinationCityName, const double hoursInRoute, const std::list<Passenger*> passengers);
Trip* findTripById(sqlite3* db, int tripId);
std::list<Passenger*> findPassengersInTrip(sqlite3* db, int tripId);
bool addPassengersInTripDB (sqlite3* db, const int tripId, const std::list<Passenger*> passengers);
bool removeTripInTrips(sqlite3* db, const int tripId);
bool editTripInTrips(sqlite3* db, const int tripId, const Trip* newTrip);
bool listTripInTrips(sqlite3* db, std::list<Trip*>& trips);

#endif