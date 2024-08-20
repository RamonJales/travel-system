#include "../include/Trip.hpp"

Trip::Trip(Transport* transport, std::list<Passenger*> passengers, City* origin, City* destination) {
    this->transport = transport;
    this->passengers = passengers;
    this->origin = origin;
    this->destination = destination;
    this->nextTrip = nullptr;
    this->hoursInRoute = 0;
    this->tripInProgress = false;
}

int Trip::getId() const {
    return tripId;
}

Transport* Trip::getTransport() const {
    return transport;
}

std::list<Passenger*> Trip::getPassengers() const {
    return passengers;
}

City* Trip::getOrigin() const {
    return origin;
}

City* Trip::getDestination() const {
    return destination;
}

Trip* Trip::getNextTrip() const {
    return nextTrip;
}

double Trip::getHoursInRoute() const {
    return hoursInRoute;
}

bool Trip::isTripInProgress() const {
    return tripInProgress;
}

void Trip::setId(int tripId) {
    this->tripId = tripId;
}

void Trip::setTransport(Transport* transport) {
    this->transport = transport;
}

void Trip::setPassengers(std::list<Passenger*> passengers) {
    this->passengers = passengers;
}

void Trip::setOrigin(City* origin) {
    this->origin = origin;
}

void Trip::setDestination(City* destination) {
    this->destination = destination;
}

void Trip::setNextTrip(Trip* nextTrip) {
    this->nextTrip = nextTrip;
}

void Trip::setHoursInRoute(double hoursInRoute) {
    this->hoursInRoute = hoursInRoute;
}

void Trip::setTripInProgress(bool tripInProgress) {
    this->tripInProgress = tripInProgress;
}

void Trip::addPassenger(Passenger* passenger) {
    this->passengers.push_back(passenger);
}

void Trip::removePassenger(Passenger* passenger) {
    this->passengers.remove(passenger);
}

void Trip::startTrip() {
    this->tripInProgress = true;
}

void Trip::endTrip() {
    this->tripInProgress = false;
}

void reportOngoingTrips(const std::list<Trip*>& trips) {
    for (const Trip* trip : trips) {
        std::cout << "Viagem ID: " << trip->getId() << std::endl;

        // Exibe o nome das cidades de origem e destino
        City* origin = trip->getOrigin();
        City* destination = trip->getDestination();
        Transport* transport = trip->getTransport();

        std::cout << "Origem: " << (origin ? origin->getCityName() : "Desconhecido") << std::endl;
        std::cout << "Destino: " << (destination ? destination->getCityName() : "Desconhecido") << std::endl;
        std::cout << "Transporte: " << (transport ? transport->getTransportName() : "Desconhecido") << std::endl;
        std::cout << "Duração: " << trip->getHoursInRoute() << " horas" << std::endl;

        // Exibe os nomes dos passageiros
        const std::list<Passenger*>& passengers = trip->getPassengers();
        std::cout << "Passageiros: ";
        for (const Passenger* passenger : passengers) {
            std::cout << passenger->getName() << " ";
        }
        std::cout << std::endl;
    }
}

