#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include "../sqlite3/sqlite3.h"
#include <iostream>

void createTables(sqlite3* db);

#endif