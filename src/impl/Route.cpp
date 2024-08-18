#include "../include/Route.hpp"

Route::Route(std::string originCity, std::string destinationCity, RouteTypeEnum routeType, float distance) {
    this->originCity = originCity;
    this->destinationCity = destinationCity;
    this->routeType = routeType;
    this->distance = distance;
}

std::string Route::getOriginCity() {
    return originCity;
}

std::string Route::getDestinationCity() {
    return destinationCity;
}

RouteTypeEnum Route::getRouteType() {
    return routeType;
}

float Route::getDistance() {
    return distance;
}

int Route::getId() {
    return id;
}

void Route::setOriginCity(std::string originCity) {
    this->originCity = originCity;
}

void Route::setDestinationCity(std::string destinationCity) {
    this->destinationCity = destinationCity;
}

void Route::setRouteType(RouteTypeEnum routeType) {
    this->routeType = routeType;
}

void Route::setDistance(float distance) {
    this->distance = distance;
}
