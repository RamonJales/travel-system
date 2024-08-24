/**
 * @file repositoryTransport.hpp
 * @brief Declaração das funções para manipulação de transportes no banco de dados SQLite.
 */

#ifndef REPOSITORYTRANSPORT_HPP
#define REPOSITORYTRANSPORT_HPP

#include "../../../sqlite3/sqlite3.h"
#include "../enums/TransportTypeEnum.hpp"
#include "../Transport.hpp"
#include "./repositoryCity.hpp"
#include <iostream>
#include <list>
#include <unordered_map>

/**
 * @brief Converte uma string para o tipo de enumeração TransportTypeEnum.
 *
 * Esta função converte uma string que representa o tipo de transporte em um valor do enum `TransportTypeEnum`.
 *
 * @param typeString String que representa o tipo de transporte.
 * @return Valor do enum TransportTypeEnum correspondente à string fornecida.
 */
TransportTypeEnum stringToTransportType(const std::string& typeString);

/**
 * @brief Converte um valor do tipo de enumeração TransportTypeEnum para uma string.
 *
 * Esta função converte um valor do enum `TransportTypeEnum` em uma string que representa o tipo de transporte.
 *
 * @param type Valor do enum TransportTypeEnum a ser convertido.
 * @return String que representa o tipo de transporte.
 */
std::string transportTypeToString(TransportTypeEnum type);

/**
 * @brief Cria a tabela de transportes no banco de dados.
 *
 * Esta função cria a tabela necessária para armazenar as informações de transportes no banco de dados SQLite.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 */
void createTableTransports(sqlite3* db);

/**
 * @brief Adiciona um novo transporte na tabela de transportes.
 *
 * Esta função adiciona um novo transporte com base nas informações fornecidas.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param transportName Nome do transporte.
 * @param type Tipo de transporte, representado como uma string.
 * @param capacity Capacidade do transporte (número de passageiros).
 * @param speed Velocidade do transporte em km/h.
 * @param distanceBetweenRest Distância entre períodos de descanso em km.
 * @param restTime Tempo de descanso em horas.
 * @param currentPlace Nome da cidade onde o transporte está localizado.
 * @param inProgress Indica se o transporte está em uma viagem.
 * @return Verdadeiro se o transporte foi adicionado com sucesso, falso caso contrário.
 */
bool addTransportInTransports(sqlite3* db, const std::string& transportName, const std::string& type, const int capacity, const float speed,
    const float distanceBetweenRest, const float restTime, const std::string currentPlace, const bool inProgress);

/**
 * @brief Encontra um transporte pelo nome.
 *
 * Esta função localiza um transporte específico com base no nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param transportName Nome do transporte a ser encontrado.
 * @return Ponteiro para o objeto Transport encontrado, ou nullptr se não encontrado.
 */
Transport* findTransportByName(sqlite3* db, const std::string& transportName);

/**
 * @brief Remove um transporte da tabela de transportes.
 *
 * Esta função exclui um transporte com base no nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param transportName Nome do transporte a ser removido.
 * @return Verdadeiro se o transporte foi removido com sucesso, falso caso contrário.
 */
bool removeTransportInTransports(sqlite3* db, const std::string& transportName);

/**
 * @brief Atualiza as informações de um transporte existente.
 *
 * Esta função atualiza um transporte existente com base nas novas informações fornecidas.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param newTransport Objeto Transport contendo as novas informações do transporte.
 * @return Verdadeiro se o transporte foi atualizado com sucesso, falso caso contrário.
 */
bool editTransportInTransports(sqlite3* db, const Transport& newTransport);

/**
 * @brief Lista todos os transportes registrados no banco de dados.
 *
 * Esta função retorna uma lista de todos os transportes presentes na tabela de transportes.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param transports Lista onde os transportes encontrados serão armazenados.
 * @return Verdadeiro se a lista de transportes foi preenchida com sucesso, falso caso contrário.
 */
bool listTransportInTransports(sqlite3* db, std::list<Transport>& transports);

/**
 * @brief Encontra todos os transportes registrados no banco de dados.
 *
 * Esta função retorna uma lista de ponteiros para todos os transportes presentes na tabela de transportes.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @return Lista de ponteiros para objetos Transport.
 */
std::list<Transport*> findAllTransports(sqlite3* db);

#endif // REPOSITORYTRANSPORT_HPP
