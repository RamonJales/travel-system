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
    int tripId;
    Transport* transport;
    std::list<Passenger*> passengers;
    City* origin;
    City* destination;
    Trip* nextTrip;
    double hoursInRoute;
    bool tripInProgress;

public:
    // Construtor
    Trip(Transport* transport, std::list<Passenger*> passengers, City* origin, City* destination);

    // Getters
    int getId() const;
    Transport* getTransport() const;
    std::list<Passenger*> getPassengers() const;
    City* getOrigin() const;
    City* getDestination() const;
    Trip* getNextTrip() const;
    double getHoursInRoute() const;
    bool isTripInProgress() const;

    // Setters
    void setId(int tripId);
    void setTransport(Transport* transport);
    void setPassengers(std::list<Passenger*> passengers);
    void setOrigin(City* origin);
    void setDestination(City* destination);
    void setNextTrip(Trip* nextTrip);
    void setHoursInRoute(double hoursInRoute);
    void setTripInProgress(bool tripInProgress);

    // Methods to manage passengers
    void addPassenger(Passenger* passenger);
    void removePassenger(Passenger* passenger);

    // Methods to manage trip status
    void startTrip();
    void endTrip();
};

// Função auxiliar para relatar viagens em andamento
void reportOngoingTrips(const std::list<Trip*>& trips);

#endif // TRIP_HPP
