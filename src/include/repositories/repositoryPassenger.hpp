/**
 * @file repositoryPassenger.hpp
 * @brief Declaração das funções para manipulação de passageiros no banco de dados SQLite.
 */

#ifndef REPOSITORYPASSENGER_HPP
#define REPOSITORYPASSENGER_HPP

#include "../../../sqlite3/sqlite3.h"
#include "./repositoryCity.hpp"
#include "../Passenger.hpp"
#include "../City.hpp"
#include <iostream>

/**
 * @brief Cria a tabela de passageiros no banco de dados.
 *
 * Esta função cria a tabela necessária para armazenar as informações de passageiros no banco de dados SQLite.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 */
void createTablePassengers(sqlite3* db);

/**
 * @brief Adiciona um novo passageiro na tabela de passageiros.
 *
 * Esta função adiciona um novo passageiro com base nas informações fornecidas.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param passengerName Nome do passageiro.
 * @param cityName Nome da cidade onde o passageiro está localizado.
 * @return Verdadeiro se o passageiro foi adicionado com sucesso, falso caso contrário.
 */
bool addPassengerInPassengers(sqlite3* db, const std::string& passengerName, const std::string& cityName);

/**
 * @brief Encontra um passageiro pelo nome.
 *
 * Esta função localiza um passageiro específico com base no nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param passengerName Nome do passageiro a ser encontrado.
 * @return Ponteiro para o objeto Passenger encontrado, ou nullptr se não encontrado.
 */
Passenger* findPassengerByName(sqlite3* db, const std::string& passengerName);

/**
 * @brief Remove um passageiro da tabela de passageiros.
 *
 * Esta função exclui um passageiro com base no nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param passengerName Nome do passageiro a ser removido.
 * @return Verdadeiro se o passageiro foi removido com sucesso, falso caso contrário.
 */
bool removePassengerInPassengers(sqlite3* db, const std::string& passengerName);

/**
 * @brief Atualiza as informações de um passageiro existente.
 *
 * Esta função atualiza um passageiro existente com base nas novas informações fornecidas.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param newPassenger Objeto Passenger contendo as novas informações do passageiro.
 * @return Verdadeiro se o passageiro foi atualizado com sucesso, falso caso contrário.
 */
bool editPassengerInPassengers(sqlite3* db, Passenger& newPassenger);

/**
 * @brief Lista todos os passageiros registrados no banco de dados.
 *
 * Esta função retorna uma lista de todos os passageiros presentes na tabela de passageiros.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param passengers Lista onde os passageiros encontrados serão armazenados.
 * @return Verdadeiro se a lista de passageiros foi preenchida com sucesso, falso caso contrário.
 */
bool listPassengerInPassengers(sqlite3* db, std::list<Passenger>& passengers);

/**
 * @brief Encontra todos os passageiros registrados no banco de dados.
 *
 * Esta função retorna uma lista de ponteiros para todos os passageiros presentes na tabela de passageiros.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @return Lista de ponteiros para objetos Passenger.
 */
std::list<Passenger*> findAllPassengers(sqlite3* db);

#endif // REPOSITORYPASSENGER_HPP
