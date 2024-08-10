#ifndef REPOSITORYTRANSPORT_HPP
#define REPOSITORYTRANSPORT_HPP

#include "../../../sqlite3/sqlite3.h"
#include "../enums/TransportTypeEnum.hpp"
#include "../Transport.hpp"
#include <iostream>
#include <list>

void createTableTransports(sqlite3* db);
bool addTransportInTransports(sqlite3* db, const std::string& transportName, const std::string& type, const int capacity, const float speed,
    const float distanceBetweenRest, const float restTime);
Transport* findTransportById(sqlite3* db, int transportId);
bool removeTransportInTransports(sqlite3* db, const int transportId);
bool editTransportInTransports(sqlite3* db, const int transportId, const Transport* newTransport);
bool listTransportInTransports(sqlite3* db, std::list<Transport>& transports);

#endif