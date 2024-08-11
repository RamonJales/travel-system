#include "../include/Passenger.hpp"
#include "../include/City.hpp"

Passenger::Passenger(std::string name, City currentLocation) : id(id), name(name), currentLocation(currentLocation) {}

int Passenger::getId() const{
    return id;
}

std::string Passenger::getName() const{
    return name;
}

City Passenger::getCurrentLocation() const{
    return currentLocation;
}

void Passenger::setCurrentLocation(City newLocation) {
    currentLocation = newLocation;
}

void Passenger::setId(int id){
    this->id = id;
}
