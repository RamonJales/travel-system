/**
 * @file Transport.hpp
 * @brief Declaração da classe Transport.
 */

#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <iostream>
#include "enums/TransportTypeEnum.hpp"
#include "City.hpp"

/**
 * @brief Classe que representa um meio de transporte.
 *
 * A classe Transport armazena informações sobre um meio de transporte, incluindo
 * seu nome, tipo, capacidade, velocidade, e parâmetros relacionados ao descanso.
 */
class Transport {
private:
    std::string transportName;              ///< Nome do transporte
    TransportTypeEnum transportType;        ///< Tipo de transporte (enum)
    int capacity;                           ///< Capacidade do transporte (número de passageiros)
    float speed;                            ///< Velocidade do transporte em km/h
    float distanceBetweenRest;              ///< Distância entre períodos de descanso em km
    float restTime;                         ///< Tempo de descanso em horas
    float currentRestTime;                  ///< Tempo atual de descanso em horas
    City* currentPlace;                     ///< Cidade onde o transporte está localizado

    bool tripInProgress;                    ///< Indica se o transporte está em uma viagem
    double hoursRemaining;                  ///< Horas restantes na viagem atual

public:
    /**
     * @brief Construtor para inicializar um transporte.
     *
     * @param transportName Nome do transporte.
     * @param transportType Tipo do transporte.
     * @param capacity Capacidade do transporte (número de passageiros).
     * @param speed Velocidade do transporte em km/h.
     * @param distanceBetweenRest Distância entre períodos de descanso em km.
     * @param restTime Tempo de descanso em horas.
     * @param currentRestTime Tempo atual de descanso em horas.
     * @param currentPlace Ponteiro para a cidade onde o transporte está localizado.
     */
    Transport(std::string transportName, TransportTypeEnum transportType, int capacity, float speed, float distanceBetweenRest, float restTime, float currentRestTime, City* currentPlace);

    /**
     * @brief Obtém o nome do transporte.
     * @return Nome do transporte.
     */
    std::string getTransportName() const;

    /**
     * @brief Obtém o tipo de transporte.
     * @return Tipo do transporte (enum TransportTypeEnum).
     */
    TransportTypeEnum getTransportType() const;

    /**
     * @brief Obtém a capacidade do transporte.
     * @return Capacidade do transporte (número de passageiros).
     */
    int getCapacity() const;

    /**
     * @brief Obtém a velocidade do transporte.
     * @return Velocidade do transporte em km/h.
     */
    float getSpeed() const;

    /**
     * @brief Obtém a distância entre períodos de descanso.
     * @return Distância entre períodos de descanso em km.
     */
    float getDistanceBetweenRest() const;

    /**
     * @brief Obtém o tempo de descanso.
     * @return Tempo de descanso em horas.
     */
    float getRestTime() const;

    /**
     * @brief Obtém o tempo atual de descanso.
     * @return Tempo atual de descanso em horas.
     */
    float getCurrentRestTime() const;

    /**
     * @brief Obtém a cidade onde o transporte está localizado.
     * @return Ponteiro para a cidade atual.
     */
    City* getCurrentPlace() const;

    /**
     * @brief Define a cidade onde o transporte está localizado.
     * @param place Ponteiro para a cidade onde o transporte deve ser localizado.
     */
    void setCurrentPlace(City* place);

    /**
     * @brief Verifica se o transporte está em viagem.
     * @return Verdadeiro se o transporte está em viagem, falso caso contrário.
     */
    bool isInTrip() const;

    /**
     * @brief Obtém o tempo restante da viagem atual.
     * @return Horas restantes na viagem atual.
     */
    double getHoursRemaining() const;

    /**
     * @brief Define se o transporte está em viagem e as horas restantes.
     * @param inProgress Verdadeiro se a viagem está em progresso, falso caso contrário.
     * @param hours Horas restantes na viagem atual.
     */
    void setTripStatus(bool inProgress, double hours);
};

#endif // TRANSPORT_HPP
