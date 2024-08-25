/**
 * @file repositoryCity.hpp
 * @brief Declaração das funções para manipulação de cidades no banco de dados SQLite.
 */

#ifndef REPOSITORYCITY_HPP
#define REPOSITORYCITY_HPP

#include "../../../sqlite3/sqlite3.h"
#include <iostream>
#include <list>
#include "../City.hpp"
#include <unordered_map>

/**
 * @brief Cria a tabela de cidades no banco de dados.
 *
 * Esta função cria a tabela necessária para armazenar as informações de cidades no banco de dados SQLite.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 */
void createTableCities(sqlite3* db);

/**
 * @brief Adiciona uma nova cidade na tabela de cidades.
 *
 * Esta função adiciona uma nova cidade com base no nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param cityName Nome da cidade a ser adicionada.
 * @return Verdadeiro se a cidade foi adicionada com sucesso, falso caso contrário.
 */
bool addCityInCities(sqlite3* db, const std::string& cityName);

/**
 * @brief Encontra uma cidade pelo nome.
 *
 * Esta função localiza uma cidade específica com base no nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param name Nome da cidade a ser encontrada.
 * @return Ponteiro para o objeto City encontrado, ou nullptr se não encontrado.
 */
City* findCityByName(sqlite3* db, const std::string& name);

/**
 * @brief Remove uma cidade da tabela de cidades.
 *
 * Esta função exclui uma cidade com base no nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param cityName Nome da cidade a ser removida.
 * @return Verdadeiro se a cidade foi removida com sucesso, falso caso contrário.
 */
bool removeCityInCities(sqlite3* db, const std::string& cityName);

/**
 * @brief Atualiza as informações de uma cidade existente.
 *
 * Esta função atualiza uma cidade existente com base nas novas informações fornecidas.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param cityName Nome da cidade a ser atualizada.
 * @param newCity Ponteiro para o objeto City contendo as novas informações.
 * @return Verdadeiro se a cidade foi atualizada com sucesso, falso caso contrário.
 */
bool editCityInCities(sqlite3* db, const std::string& cityName, const City* newCity);

/**
 * @brief Lista todas as cidades registradas no banco de dados.
 *
 * Esta função retorna uma lista de todas as cidades presentes na tabela de cidades.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param cities Lista onde as cidades encontradas serão armazenadas.
 * @return Verdadeiro se a lista de cidades foi preenchida com sucesso, falso caso contrário.
 */
bool listCityInCities(sqlite3* db, std::list<City>& cities);

/**
 * @brief Incrementa o número de visitas para uma cidade específica.
 *
 * Esta função atualiza o contador de visitas para a cidade com o nome fornecido.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 * @param cityName Nome da cidade para a qual o contador de visitas deve ser incrementado.
 */
void incrementCityVisit(sqlite3* db, const std::string& cityName);

/**
 * @brief Encontra e exibe as cidades mais frequentes.
 *
 * Esta função localiza as cidades que foram mais visitadas e exibe as informações.
 *
 * @param db Ponteiro para o banco de dados SQLite.
 */
void findMostFrequentCities(sqlite3* db);

#endif // REPOSITORYCITY_HPP
