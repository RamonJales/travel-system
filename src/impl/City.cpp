#include "../include/City.hpp"

City::City(std::string name) : cityName(std::move(name)) {}
City::City() : cityName() {}

std::string City::getCityName() const {
    return cityName;
}