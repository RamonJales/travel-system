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
    int tripId;                      ///< Id da viagem
    Transport* transport;            ///< Transporte usado na viagem
    std::list<Passenger*> passenger; ///< Lista de passageiros na viagem
    City* origin;                    ///< Cidade de origem da viagem
    City* destination;               ///< Cidade de destino da viagem
    Trip *nextTrip;                  ///< Próxima viagem, caso exista uma sequência
    int hoursInRoute;                ///< Duração da viagem em horas
    bool tripInProgess;              ///< Status da viagem (em andamento ou concluída)

public:
    /**
     * @brief Construtor para inicializar uma viagem.
     * 
     * @param transport Ponteiro para o transporte usado na viagem.
     * @param passenger Lista de ponteiros para os passageiros que participarão da viagem.
     * @param origin Ponteiro para a cidade de origem da viagem.
     * @param destination Ponteiro para a cidade de destino da viagem.
     */
    Trip(Transport* transport, std::list<Passenger*> passenger, City* origin, City* destination);

    /**
     * @brief Obtém o id da viagem.
     * @return Id da viagem no banco de dados.
     */
    int getId() const;

    /**
     * @brief Obtém o transporte usado na viagem.
     * @return Ponteiro para o transporte.
     */
    Transport* getTransport() const;

    /**
     * @brief Obtém a lista de passageiros na viagem.
     * @return Lista de ponteiros para os passageiros.
     */
    std::list<Passenger*> getPassenger();

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
     * @brief Obtém a próxima viagem na sequência.
     * @return Ponteiro para a próxima viagem.
     */
    Trip* getNextTrip() const;

    /**
     * @brief Obtém o número de horas em rota.
     * @return Duração da viagem em horas.
     */
    int getHoursInRoute() const;

    /**
     * @brief Verifica se a viagem está em andamento.
     * @return true se a viagem está em andamento, false se foi concluída.
     */
    bool getTripInProgress() const;

    /**
     * @brief Define o id da viagem.
     * @param tripId Id da viagem no banco de dados.
     */
    void setId(int tripId);
    
    /**
     * @brief Define o transporte a ser usado na viagem.
     * @param transport Ponteiro para o transporte.
     */
    void setTransport(Transport* transport);

    /**
     * @brief Define a lista de passageiros na viagem.
     * @param passenger Lista de ponteiros para os passageiros.
     */
    void setPassenger(std::list<Passenger*> passenger);

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
     * @brief Define a próxima viagem na sequência.
     * @param nextTrip Ponteiro para a próxima viagem.
     */
    void setNextTrip(Trip* nextTrip);

    /**
     * @brief Define o número de horas em rota.
     * @param hoursInRoute Duração da viagem em horas.
     */
    void setHoursInRoute(int hoursInRoute);

    /**
     * @brief Define o status da viagem.
     * @param tripInProgress true para indicar que a viagem está em andamento, false para concluída.
     */
    void setTripInProgress(bool tripInProgress);

    /**
     * @brief Adiciona um passageiro à lista de passageiros.
     * @param passenger Ponteiro para o passageiro a ser adicionado.
     */
    void addPassenger(Passenger* passenger);

    /**
     * @brief Remove um passageiro da lista de passageiros.
     * @param passenger Ponteiro para o passageiro a ser removido.
     */
    void removePassenger(Passenger* passenger);

    /**
     * @brief Inicia a viagem, marcando-a como em andamento.
     */
    void startTrip();

    /**
     * @brief Encerra a viagem, marcando-a como concluída.
     */
    void endTrip();

    /**
     * @brief Gera um relatório da viagem.
     *
     * Esta função pode ser utilizada para coletar informações detalhadas sobre
     * a viagem, como transporte utilizado, passageiros, cidades de origem e destino, etc.
     */
    void tripRelatory();
};

#endif // TRIP_HPP
