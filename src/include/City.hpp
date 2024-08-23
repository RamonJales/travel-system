/**
 * @file City.hpp
 * @brief Declaração da classe City.
 */

#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>

/**
 * @class City
 * @brief Representa uma cidade com um nome.
 */
class City {
    private:
        std::string cityName; ///< Nome da cidade.

    public:
        /**
         * @brief Construtor da classe City.
         * @param name Nome da cidade.
         */
        City(std::string name);

        /**
         * @brief Construtor da classe City.
         * @param name Nome da cidade.
         */
        City();

        /**
         * @brief Obtém o nome da cidade.
         * @return Nome da cidade.
         */
        std::string getCityName() const;

        void setCityName(std::string name);
};

#endif
