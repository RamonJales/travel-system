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
 *
 * A classe City armazena o nome de uma cidade e fornece métodos para acessar e modificar este nome.
 */
class City {
private:
    std::string cityName; ///< Nome da cidade.

public:
    /**
     * @brief Construtor da classe City.
     *
     * Este construtor inicializa a cidade com um nome fornecido.
     *
     * @param name Nome da cidade.
     */
    City(std::string name);

    /**
     * @brief Construtor padrão da classe City.
     *
     * Este construtor inicializa a cidade com um nome vazio.
     */
    City();

    /**
     * @brief Obtém o nome da cidade.
     *
     * Este método retorna o nome da cidade armazenado na instância da classe.
     *
     * @return Nome da cidade.
     */
    std::string getCityName() const;

    /**
     * @brief Define o nome da cidade.
     *
     * Este método define o nome da cidade para o valor fornecido.
     *
     * @param name Nome da cidade.
     */
    void setCityName(std::string name);
};

#endif // CITY_HPP
