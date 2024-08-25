/**
 * @file Trip.hpp
 * @brief Declaração da classe Trip.
 */

#ifndef TRIP_HPP
#define TRIP_HPP

#include <iostream>
#include <list>
#include "City.hpp"
#include "Passenger.hpp"
#include "Transport.hpp"

/**
 * @brief Classe que representa uma viagem.
 *
 * A classe Trip gerencia os detalhes de uma viagem, incluindo o transporte, passageiros,
 * cidade de origem, cidade de destino, e o status da viagem.
 */
class Trip {
private:
    int tripId;                             ///< Identificador único da viagem
    Transport* transport;                   ///< Ponteiro para o transporte utilizado na viagem
    std::list<Passenger*> passengers;       ///< Lista de passageiros na viagem
    City* origin;                           ///< Cidade de origem da viagem
    City* destination;                      ///< Cidade de destino da viagem
    Trip* nextTrip;                         ///< Ponteiro para a próxima viagem na cadeia de viagens (se houver)
    double hoursInRoute;                    ///< Horas no percurso da viagem
    bool tripInProgress;                    ///< Indica se a viagem está em andamento

public:
    /**
     * @brief Construtor para inicializar uma viagem.
     *
     * @param transport Ponteiro para o transporte utilizado na viagem.
     * @param passengers Lista de ponteiros para os passageiros da viagem.
     * @param origin Ponteiro para a cidade de origem da viagem.
     * @param destination Ponteiro para a cidade de destino da viagem.
     */
    Trip(Transport* transport, std::list<Passenger*> passengers, City* origin, City* destination);

    /**
     * @brief Obtém o identificador da viagem.
     * @return Identificador da viagem.
     */
    int getId() const;

    /**
     * @brief Obtém o transporte utilizado na viagem.
     * @return Ponteiro para o transporte.
     */
    Transport* getTransport() const;

    /**
     * @brief Obtém a lista de passageiros da viagem.
     * @return Lista de ponteiros para passageiros.
     */
    std::list<Passenger*> getPassengers() const;

    /**
     * @brief Obtém a cidade de origem da viagem.
     * @return Ponteiro para a cidade de origem.
     */
    City* getOrigin() const;

    /**
     * @brief Obtém a cidade de destino da viagem.
     * @return Ponteiro para a cidade de destino.
     */
    City* getDestination() const;

    /**
     * @brief Obtém o ponteiro para a próxima viagem na cadeia de viagens.
     * @return Ponteiro para a próxima viagem (ou nullptr se não houver próxima viagem).
     */
    Trip* getNextTrip() const;

    /**
     * @brief Obtém as horas no percurso da viagem.
     * @return Horas no percurso.
     */
    double getHoursInRoute() const;

    /**
     * @brief Verifica se a viagem está em andamento.
     * @return Verdadeiro se a viagem está em andamento, falso caso contrário.
     */
    bool isTripInProgress() const;

    /**
     * @brief Obtém o total de horas da viagem.
     * @return Total de horas da viagem.
     */
    double getTotalHours() const;

    /**
     * @brief Define o identificador da viagem.
     * @param tripId Identificador da viagem.
     */
    void setId(int tripId);

    /**
     * @brief Define o transporte utilizado na viagem.
     * @param transport Ponteiro para o transporte.
     */
    void setTransport(Transport* transport);

    /**
     * @brief Define a lista de passageiros da viagem.
     * @param passengers Lista de ponteiros para passageiros.
     */
    void setPassengers(std::list<Passenger*> passengers);

    /**
     * @brief Define a cidade de origem da viagem.
     * @param origin Ponteiro para a cidade de origem.
     */
    void setOrigin(City* origin);

    /**
     * @brief Define a cidade de destino da viagem.
     * @param destination Ponteiro para a cidade de destino.
     */
    void setDestination(City* destination);

    /**
     * @brief Define o ponteiro para a próxima viagem na cadeia de viagens.
     * @param nextTrip Ponteiro para a próxima viagem (ou nullptr se não houver próxima viagem).
     */
    void setNextTrip(Trip* nextTrip);

    /**
     * @brief Define as horas no percurso da viagem.
     * @param hoursInRoute Horas no percurso.
     */
    void setHoursInRoute(double hoursInRoute);

    /**
     * @brief Define se a viagem está em andamento.
     * @param tripInProgress Verdadeiro se a viagem está em andamento, falso caso contrário.
     */
    void setTripInProgress(bool tripInProgress);

    /**
     * @brief Adiciona um passageiro à viagem.
     * @param passenger Ponteiro para o passageiro a ser adicionado.
     */
    void addPassenger(Passenger* passenger);

    /**
     * @brief Remove um passageiro da viagem.
     * @param passenger Ponteiro para o passageiro a ser removido.
     */
    void removePassenger(Passenger* passenger);

    /**
     * @brief Inicia a viagem.
     */
    void startTrip();

    /**
     * @brief Finaliza a viagem.
     */
    void endTrip();
};

/**
 * @brief Função auxiliar para relatar viagens em andamento.
 *
 * Esta função percorre uma lista de viagens e relata aquelas que estão em andamento.
 *
 * @param trips Lista de ponteiros para viagens a serem verificadas.
 */
void reportOngoingTrips(const std::list<Trip*>& trips);

#endif // TRIP_HPP
