#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>

class City {
    private:
        std::string cityName;
    public:
        City(std::string name);
        std::string getCityName();
};

#endif