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

std::string Transport::getTransportName(){
    return transportName;
}

TransportTypeEnum Transport::getTransportType(){
    return transportType;
}

int Transport::getCapacity(){
    return capacity;
}

float Transport::getSpeed(){
    return speed;
}

float Transport::getDistanceBetweenRest(){
    return distanceBetweenRest;
}

float Transport::getRestTime(){
    return restTime;
}

float Transport::getCurrentRestTime(){
    return currentRestTime;
}

City* Transport::getCurrentPlace(){
    return currentPlace;
}

void Transport::setCurrentPlace(City* place){
    this->currentPlace = place;
}