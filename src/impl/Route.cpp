#include "../include/Route.hpp"

Route::Route(std::string routeName, std::string originCity, std::string destinationCity, RouteTypeEnum routeType, float distance) {
    this->routeName = routeName;
    this->originCity = originCity;
    this->destinationCity = destinationCity;
    this->routeType = routeType;
    this->distance = distance;
}

std::string Route::getRouteName() {
    return routeName;
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

void Route::setRouteName(std::string routeName) {
    this->routeName = routeName;
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
