#include "../include/City.hpp"

City::City(std::string name) : cityName(name) {}

std::string City::getCityName() const {
    return cityName;
}