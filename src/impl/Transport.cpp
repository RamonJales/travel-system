#include "../include/Transport.hpp"

Transport::Transport(std::string transportName, TransportTypeEnum transportType, int capacity, float speed, float distanceBetweenRest, 
float restTime, float currentRestTime,  City* currentPlace){
    this->transportName = transportName;
    this->transportType = transportType;
    this->capacity = capacity;
    this->speed = speed;
    this->distanceBetweenRest = distanceBetweenRest;
    this->restTime = restTime;
    this->currentRestTime = currentRestTime;
    this->currentPlace = currentPlace;
}

std::string Transport::getTransportName() const{
    return transportName;
}

TransportTypeEnum Transport::getTransportType() const{
    return transportType;
}

int Transport::getCapacity() const{
    return capacity;
}

float Transport::getSpeed() const{
    return speed;
}

float Transport::getDistanceBetweenRest() const{
    return distanceBetweenRest;
}

float Transport::getRestTime() const{
    return restTime;
}

float Transport::getCurrentRestTime() const{
    return currentRestTime;
}

City* Transport::getCurrentPlace() const{
    return currentPlace;
}

void Transport::setCurrentPlace(City* place){
    this->currentPlace = place;
}