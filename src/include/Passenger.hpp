/**
 * @file Passenger.hpp
 * @brief Declaração da classe Passenger.
 */

#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include <iostream>
#include <string>
#include "City.hpp"

/**
 * @class Passenger
 * @brief Representa um passageiro com um nome e uma localização atual.
 */
class Passenger {
    private:
        std::string name; ///< Nome do passageiro.
        City* currentLocation; ///< Ponteiro para a cidade atual onde o passageiro está.

    public:
        /**
         * @brief Construtor da classe Passenger.
         * @param name Nome do passageiro.
         * @param currentLocation Ponteiro para a cidade onde o passageiro está atualmente.
         */
        Passenger(std::string name, City* currentLocation);

        /**
         * @brief Obtém o nome do passageiro.
         * @return Nome do passageiro.
         */
        std::string getName() const;

        /**
         * @brief Obtém a cidade atual onde o passageiro está.
         * @return Ponteiro para a cidade atual.
         */
        City* getCurrentLocation() const;

        /**
         * @brief Define a cidade atual onde o passageiro está.
         * @param newLocation Novo ponteiro para a cidade onde o passageiro deve estar.
         */
        void setCurrentLocation(City* newLocation);
};

#endif
