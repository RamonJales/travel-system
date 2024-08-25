/**
 * @file repositoryTrip.hpp
 * @brief Declaração das funções para manipulação de viagens no banco de dados SQLite.
 */

#ifndef REPOSITORYTRIP_HPP
#define REPOSITORYTRIP_HPP

#include "../../../sqlite3/sqlite3.h"
#include "../Trip.hpp"
#include "../Route.hpp"
#include "./repositoryCity.hpp"
#include "./repositoryPassenger.hpp"
#include "./repositoryTransport.hpp"
#include "./repositoryRoute.hpp"
#include "../CityGraph.hpp"
#include <iostream>
#include <list>

/**
 * @brief Cria a tabela de viagens no banco de dados.
 *
 * Esta função cria a tabela necessária para armazenar as informações de viagens no banco de dados SQLite.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 */
void createTableTrips(sqlite3* db);

/**
 * @brief Adiciona uma nova viagem na tabela de viagens.
 *
 * Esta função adiciona uma nova viagem com base nos parâmetros fornecidos.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param transportName Nome do transporte utilizado na viagem.
 * @param originCityName Nome da cidade de origem da viagem.
 * @param destinationCityName Nome da cidade de destino da viagem.
 * @param hoursInRoute Horas no percurso da viagem.
 * @param passengers Lista de ponteiros para passageiros na viagem.
 * @param inProgress Indica se a viagem está em andamento.
 * @return Identificador da viagem recém-adicionada.
 */
int addTripInTrips(sqlite3* db, const std::string& transportName, const std::string& originCityName, const std::string& destinationCityName, const double hoursInRoute, const std::list<Passenger*> passengers, const bool inProgress);

/**
 * @brief Encontra uma viagem pelo seu identificador.
 *
 * Esta função localiza uma viagem específica com base no seu identificador.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param tripId Identificador da viagem a ser encontrada.
 * @return Ponteiro para a viagem encontrada, ou nullptr se não encontrada.
 */
Trip* findTripById(sqlite3* db, int tripId);

/**
 * @brief Encontra os passageiros de uma viagem específica.
 *
 * Esta função recupera a lista de passageiros associados a uma viagem com base no seu identificador.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param tripId Identificador da viagem.
 * @return Lista de ponteiros para os passageiros encontrados.
 */
std::list<Passenger*> findPassengersInTrip(sqlite3* db, int tripId);

/**
 * @brief Adiciona passageiros a uma viagem no banco de dados.
 *
 * Esta função associa passageiros a uma viagem específica no banco de dados.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param tripId Identificador da viagem.
 * @param passengers Lista de ponteiros para passageiros a serem adicionados.
 * @return Verdadeiro se os passageiros foram adicionados com sucesso, falso caso contrário.
 */
bool addPassengersInTripDB(sqlite3* db, const int tripId, const std::list<Passenger*> passengers);

/**
 * @brief Remove uma viagem da tabela de viagens.
 *
 * Esta função exclui uma viagem com base no seu identificador.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param tripId Identificador da viagem a ser removida.
 * @return Verdadeiro se a viagem foi removida com sucesso, falso caso contrário.
 */
bool removeTripInTrips(sqlite3* db, const int tripId);

/**
 * @brief Edita os detalhes de uma viagem existente.
 *
 * Esta função atualiza as informações de uma viagem com base nos dados fornecidos.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param trip Ponteiro para o objeto Trip com as novas informações.
 * @return Verdadeiro se a viagem foi editada com sucesso, falso caso contrário.
 */
bool editTripInTrips(sqlite3* db, Trip* trip);

/**
 * @brief Atualiza o status de uma viagem (em andamento ou não).
 *
 * Esta função modifica o status de uma viagem para indicar se está em andamento ou não.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param tripId Identificador da viagem.
 * @param inProgress Indica se a viagem está em andamento.
 * @return Verdadeiro se o status foi atualizado com sucesso, falso caso contrário.
 */
bool updateTripInProgress(sqlite3* db, int tripId, bool inProgress);

/**
 * @brief Lista todas as viagens registradas no banco de dados.
 *
 * Esta função retorna uma lista de todas as viagens presentes na tabela de viagens.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @return Lista de ponteiros para as viagens.
 */
std::list<Trip*> listTripInTrips(sqlite3* db);

/**
 * @brief Lista todas as viagens que estão em andamento.
 *
 * Esta função retorna uma lista de viagens que estão atualmente em andamento.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @return Lista de ponteiros para as viagens em andamento.
 */
std::list<Trip*> listTripsInProgress(sqlite3* db);

/**
 * @brief Avança as horas de todas as viagens.
 *
 * Esta função avança o tempo de todas as viagens registradas, atualizando seus status e informações conforme necessário.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param hours Horas a serem avançadas.
 * @param g Objeto CityGraph utilizado para verificar e atualizar informações relacionadas às cidades e viagens.
 * @return Verdadeiro se o avanço das horas foi realizado com sucesso, falso caso contrário.
 */
bool advanceHours(sqlite3* db, double hours, CityGraph g);

/**
 * @brief Obtém o identificador do transporte associado a uma viagem.
 *
 * Esta função recupera o identificador do transporte utilizado em uma viagem específica.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param tripId Identificador da viagem.
 * @return Identificador do transporte associado à viagem.
 */
int getTransportIdByTripId(sqlite3* db, int tripId);

/**
 * @brief Atualiza o status de um transporte (em andamento ou não).
 *
 * Esta função modifica o status de um transporte para indicar se está em andamento, e atualiza as horas restantes se necessário.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param transportId Identificador do transporte.
 * @param inProgress Indica se o transporte está em andamento.
 * @param hoursRemaining Horas restantes no percurso do transporte.
 * @return Verdadeiro se o status do transporte foi atualizado com sucesso, falso caso contrário.
 */
bool updateTransportInProgress(sqlite3* db, int transportId, bool inProgress, double hoursRemaining);

#endif // REPOSITORYTRIP_HPP
