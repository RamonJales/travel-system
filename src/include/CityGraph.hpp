/**
 * @file CityGraph.hpp
 * @brief Declaração da classe CityGraph.
 */

#ifndef CITY_GRAPH_HPP
#define CITY_GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

/**
 * @class CityGraph
 * @brief Representa um grafo de cidades onde os vértices são cidades e as arestas representam as distâncias entre elas.
 */
class CityGraph {
    private:
        std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph; ///< Mapa de cidades para suas vizinhas e distâncias.

    public:
        /**
         * @brief Construtor da classe CityGraph.
         * @param cityGraph Mapa de cidades para suas vizinhas e distâncias.
         */
        CityGraph(std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph);
        
        /**
         * @brief Adiciona uma aresta ao grafo.
         * @param source Cidade de origem.
         * @param destiny Cidade de destino.
         * @param distance Distância entre a cidade de origem e a cidade de destino.
         */
        void addEdge(const std::string source, const std::string destiny, double distance);

        /**
         * @brief Encontra o caminho mais curto entre duas cidades usando o algoritmo de Dijkstra.
         * @param start Cidade de início.
         * @param end Cidade de destino.
         * @return Vetor contendo as cidades no caminho mais curto da cidade de início à cidade de destino.
         */
        std::vector<std::string> findShortestPath(const std::string start, const std::string end);
};

#endif
