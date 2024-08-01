#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <list>
#include "Trip.hpp"
#include "Route.hpp"
#include "City.hpp"


    void addCity(City city);
    void addTrip(Trip trip);
    void addRoute(Route route);
    void addTransport(Transport transport);
    void addPassenger(Passenger passenger);

    void startTrip(std::string transportName, std::list<std::string> passengersNames, std::string originCity, std::string destinationCity);
    void endTrip(std::string transportName, std::string originCity, std::string destinationCity);

    // void advanceHours(int hours);
    // void listTripsByPassengerTripRelatory();
        
#endif
