#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <list>
#include "Trip.hpp"
#include "Route.hpp"

class Controller {
    private:
        std::list<City> cities;
        std::list<Trip> trips;
        std::list<Route> routes;
        std::list<Transport> transports;
        std::list<Passenger> passengers;
    public:
        Controller();
        void addCity(City city);
        void addTrip(Trip trip);
        void addRoute(Route route);
        void addTransport(Transport transport);
        void addPassenger(Passenger passenger);

        void startTrip(std::string transportName, std::list<std::string> passengersNames, std::string originCity, std::string destinationCity);
        void endTrip(std::string transportName, std::string originCity, std::string destinationCity);

        // void advanceHours(int hours);
        // void listTripsByPassengerTripRelatory();
        
};


#endif