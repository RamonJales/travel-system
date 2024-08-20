/**
 * @file Transport.cpp
 * @brief Implementação da classe Transport.
 */

#include "../include/Transport.hpp"

Transport::Transport(std::string transportName, TransportTypeEnum transportType, int capacity, float speed, float distanceBetweenRest, float restTime, float currentRestTime, City* currentPlace)
    : transportName(transportName), transportType(transportType), capacity(capacity), speed(speed),
      distanceBetweenRest(distanceBetweenRest), restTime(restTime), currentRestTime(currentRestTime), currentPlace(currentPlace),
      tripInProgress(false), hoursRemaining(0.0) {}

std::string Transport::getTransportName() const {
    return transportName;
}

TransportTypeEnum Transport::getTransportType() const {
    return transportType;
}

int Transport::getCapacity() const {
    return capacity;
}

float Transport::getSpeed() const {
    return speed;
}

float Transport::getDistanceBetweenRest() const {
    return distanceBetweenRest;
}

float Transport::getRestTime() const {
    return restTime;
}

float Transport::getCurrentRestTime() const {
    return currentRestTime;
}

City* Transport::getCurrentPlace() const {
    return currentPlace;
}

void Transport::setCurrentPlace(City* place) {
    currentPlace = place;
}

bool Transport::isInTrip() const {
    return tripInProgress;
}

double Transport::getHoursRemaining() const {
    return hoursRemaining;
}

void Transport::setTripStatus(bool inProgress, double hours) {
    tripInProgress = inProgress;
    hoursRemaining = hours;
}
