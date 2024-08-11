/**
 * @file Route.hpp
 * @brief Declaração da classe Route.
 */

#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <iostream>
#include "enums/RouteTypeEnum.hpp"

/**
 * @class Route
 * @brief Representa uma rota com informações sobre o nome, cidade de origem, cidade de destino, tipo de rota e distância.
 */
class Route {
    private:
        int id; ///< Id da rota.
        std::string routeName; ///< Nome da rota.
        std::string originCity; ///< Cidade de origem.
        std::string destinationCity; ///< Cidade de destino.
        RouteTypeEnum routeType; ///< Tipo da rota.
        float distance; ///< Distância da rota em quilômetros.

    public:
        /**
         * @brief Construtor da classe Route.
         * @param routeName Nome da rota.
         * @param originCity Cidade de origem.
         * @param destinationCity Cidade de destino.
         * @param routeType Tipo da rota.
         * @param distance Distância da rota em quilômetros.
         */
        Route(std::string routeName, std::string originCity, std::string destinationCity, RouteTypeEnum routeType, float distance);

        /**
         * @brief Obtém o nome da rota.
         * @return Nome da rota.
         */
        std::string getRouteName();

        /**
         * @brief Obtém a cidade de origem.
         * @return Cidade de origem.
         */
        std::string getOriginCity();

        /**
         * @brief Obtém a cidade de destino.
         * @return Cidade de destino.
         */
        std::string getDestinationCity();

        /**
         * @brief Obtém o tipo da rota.
         * @return Tipo da rota.
         */
        RouteTypeEnum getRouteType();

        /**
         * @brief Obtém a distância da rota.
         * @return Distância da rota em quilômetros.
         */
        float getDistance();

        /**
         * @brief Obtém o id da rota.
         * @return Id da rota.
         */
        int getId();

        /**
         * @brief Define o nome da rota.
         * @param routeName Novo nome da rota.
         */
        void setRouteName(std::string routeName);

        /**
         * @brief Define a cidade de origem.
         * @param originCity Nova cidade de origem.
         */
        void setOriginCity(std::string originCity);

        /**
         * @brief Define a cidade de destino.
         * @param destinationCity Nova cidade de destino.
         */
        void setDestinationCity(std::string destinationCity);

        /**
         * @brief Define o tipo da rota.
         * @param routeType Novo tipo da rota.
         */
        void setRouteType(RouteTypeEnum routeType);

        /**
         * @brief Define a distância da rota.
         * @param distance Nova distância da rota em quilômetros.
         */
        void setDistance(float distance);
};

#endif
