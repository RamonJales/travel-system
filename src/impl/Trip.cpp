#include "../include/Trip.hpp"

Trip::Trip(Transport* transport, std::list<Passenger*> passenger, City* origin, City* destination) {
    this->transport = transport;
    this->passenger = passenger;
    this->origin = origin;
    this->destination = destination;
    this->nextTrip = nullptr;
    this->hoursInRoute = 0;
    this->tripInProgess = false;
}

int Trip::getId() const {
    return tripId;
}

Transport* Trip::getTransport() const{
    return transport;
}

std::list<Passenger*> Trip::getPassenger() {
    return passenger;
}

City* Trip::getOrigin() const{
    return origin;
}

City* Trip::getDestination() const{
    return destination;
}

Trip* Trip::getNextTrip() const{
    return nextTrip;
}

int Trip::getHoursInRoute() const{
    return hoursInRoute;
}

bool Trip::getTripInProgress() const{
    return tripInProgess;
}

void Trip::setId(int tripId) {
    this->tripId = tripId;
}

void Trip::setTransport(Transport* transport) {
    this->transport = transport;
}

void Trip::setPassenger(std::list<Passenger*> passenger) {
    this->passenger = passenger;
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

void Trip::setHoursInRoute(int hoursInRoute) {
    this->hoursInRoute = hoursInRoute;
}

void Trip::setTripInProgress(bool tripInProgress) {
    this->tripInProgess = tripInProgress;
}

void Trip::addPassenger(Passenger* passenger) {
    this->passenger.push_back(passenger);
}

void Trip::removePassenger(Passenger* passenger) {
    this->passenger.remove(passenger);
}

void Trip::startTrip() {
    this->tripInProgess = true;
}

void Trip::endTrip() {
    this->tripInProgess = false;
}

void Trip::tripRelatory() {
    std::cout << "Trip from " << origin->getCityName() << " to " << destination->getCityName() << std::endl;
    std::cout << "Transport: " << transport->getTransportName() << std::endl;
    std::cout << "Passengers: " << std::endl;
    for (Passenger* p : passenger) {
        std::cout << "- " << p->getName() << std::endl;
    }
    std::cout << "Hours in Route: " << hoursInRoute << std::endl;
    std::cout << "Trip in Progress: " << (tripInProgess ? "Yes" : "No") << std::endl;
}