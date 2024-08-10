#include "../include/Passenger.hpp"
#include "../include/City.hpp"

Passenger::Passenger(std::string name, City* currentLocation) 
    : name(name), currentLocation(currentLocation) {}

std::string Passenger::getName() const{
    return name;
}

City* Passenger::getCurrentLocation() const{
    return currentLocation;
}

void Passenger::setCurrentLocation(City* newLocation) {
    currentLocation = newLocation;
}