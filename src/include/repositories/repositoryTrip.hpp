#ifndef REPOSITORYTRIP_HPP
#define REPOSITORYTRIP_HPP

#include "../../../sqlite3/sqlite3.h"
#include "../Trip.hpp"
#include "../Route.hpp"
#include "./repositoryCity.hpp"
#include "./repositoryPassenger.hpp"
#include "./repositoryTransport.hpp"
#include <iostream>
#include <list>

#include "../../include/repositories/repositoryTrip.hpp"

void createTableTrips(sqlite3* db);
int addTripInTrips(sqlite3* db, const std::string& transportName, const std::string& originCityName, const std::string& destinationCityName, const double hoursInRoute, const std::list<Passenger*> passengers, const bool inProgress);
Trip* findTripById(sqlite3* db, int tripId);
std::list<Passenger*> findPassengersInTrip(sqlite3* db, int tripId);
bool addPassengersInTripDB(sqlite3* db, const int tripId, const std::list<Passenger*> passengers);
bool removeTripInTrips(sqlite3* db, const int tripId);
bool editTripInTrips(sqlite3* db, Trip* trip);
bool updateTripInProgress(sqlite3* db, int tripId, bool inProgress);
std::list<Trip*> listTripInTrips(sqlite3* db);
std::list<Trip*> listTripsInProgress(sqlite3* db);
bool advanceHours(sqlite3* db, double hours);
int getTransportIdByTripId(sqlite3* db, int tripId);
bool updateTransportInProgress(sqlite3* db, int transportId, bool inProgress, double hoursRemaining);

#endif