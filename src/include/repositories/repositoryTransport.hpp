#ifndef REPOSITORYTRANSPORT_HPP
#define REPOSITORYTRANSPORT_HPP

#include "../../../sqlite3/sqlite3.h"
#include "../enums/TransportTypeEnum.hpp"
#include "../Transport.hpp"
#include "./repositoryCity.hpp"
#include <iostream>
#include <list>
#include <unordered_map>

TransportTypeEnum stringToTransportType(const std::string& typeString);
std::string transportTypeToString(TransportTypeEnum type);
void createTableTransports(sqlite3* db);
bool addTransportInTransports(sqlite3* db, const std::string& transportName, const std::string& type, const int capacity, const float speed,
const float distanceBetweenRest, const float restTime, std::string currentPlace);
Transport* findTransportByName(sqlite3* db, const std::string& transportName);
bool removeTransportInTransports(sqlite3* db, const std::string& transportName);
bool editTransportInTransports(sqlite3* db, const Transport& newTransport);
bool listTransportInTransports(sqlite3* db, std::list<Transport>& transports);
std::list<Transport*> findAllTransports(sqlite3* db);

#endif