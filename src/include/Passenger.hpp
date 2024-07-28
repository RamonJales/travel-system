#ifndef PASSENGER_HPP
#define PASSENGER_HPP
#include <iostream>
#include <string>

#include "City.hpp"

class Passenger {
    private:
        std::string name;
        City* currentLocation;
    public:
        Passenger(std::string name, City* currentLocation);
        std::string getName();

        City* getCurrentLocation();
        void setCurrentLocation(City* newLocation);
};

#endif