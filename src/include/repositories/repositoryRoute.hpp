/**
 * @file repositoryRoute.hpp
 * @brief Declaração das funções para manipulação de rotas no banco de dados SQLite.
 */

#ifndef REPOSITORYROUTE_HPP
#define REPOSITORYROUTE_HPP

#include "../../../sqlite3/sqlite3.h"
#include <iostream> 
#include <list>
#include <vector>
#include "../Route.hpp"

/**
 * @brief Cria a tabela de rotas no banco de dados.
 *
 * Esta função cria a tabela necessária para armazenar as informações de rotas no banco de dados SQLite.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 */
void createTableRoutes(sqlite3* db);

/**
 * @brief Adiciona uma nova rota na tabela de rotas.
 *
 * Esta função adiciona uma nova rota com base no objeto `Route` fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param route Objeto Route contendo as informações da nova rota.
 * @return Verdadeiro se a rota foi adicionada com sucesso, falso caso contrário.
 */
bool addRouteInRoutes(sqlite3* db, Route& route);

/**
 * @brief Atualiza uma rota existente na tabela de rotas.
 *
 * Esta função atualiza as informações de uma rota existente com base no novo objeto `Route` fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param newRoute Objeto Route contendo as novas informações da rota.
 * @return Verdadeiro se a rota foi atualizada com sucesso, falso caso contrário.
 */
bool updateRouteInRoutes(sqlite3* db, const Route newRoute);

/**
 * @brief Encontra uma rota pelo nome das cidades de origem e destino.
 *
 * Esta função localiza uma rota específica com base nos nomes das cidades de origem e destino.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param originCity Nome da cidade de origem da rota.
 * @param destinationCity Nome da cidade de destino da rota.
 * @return Ponteiro para o objeto Route encontrado, ou nullptr se não encontrada.
 */
Route* findRouteByCities(sqlite3* db, const std::string& originCity, const std::string& destinationCity);

/**
 * @brief Encontra uma rota pelo seu identificador.
 *
 * Esta função localiza uma rota específica com base no seu identificador.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param id Identificador da rota a ser encontrada.
 * @return Ponteiro para o objeto Route encontrado, ou nullptr se não encontrada.
 */
Route* findRouteById(sqlite3* db, const int id);

/**
 * @brief Remove uma rota da tabela de rotas.
 *
 * Esta função exclui uma rota com base nos nomes das cidades de origem e destino.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param originCityName Nome da cidade de origem da rota.
 * @param destinationCityName Nome da cidade de destino da rota.
 * @return Verdadeiro se a rota foi removida com sucesso, falso caso contrário.
 */
bool deleteRouteByIdInRoutes(sqlite3* db, const std::string originCityName, const std::string destinationCityName);

/**
 * @brief Encontra todas as rotas registradas no banco de dados.
 *
 * Esta função retorna uma lista de todas as rotas presentes na tabela de rotas.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @return Vetor de objetos Route.
 */
std::vector<Route> findAllRoutesInRoutes(sqlite3* db);

#endif // REPOSITORYROUTE_HPP
