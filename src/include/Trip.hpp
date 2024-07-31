#ifndef TRIP_HPP
#define TRIP_HPP

#include <iostream>
#include <list>
#include "City.hpp"
#include "Passenger.hpp"
#include "Transport.hpp"

class Trip {
    private:
        Transport* transport;
        std::list<Passenger*> passenger;
        City* origin;
        City* destination;
        Trip *nextTrip;
        int hoursInRoute;
        bool tripInProgess;
    public:
        Trip(Transport* transport, std::list<Passenger*> passenger, City* origin, City* destination);
        Transport* getTransport();
        std::list<Passenger*> getPassenger();
        City* getOrigin();
        City* getDestination();
        Trip* getNextTrip();
        int getHoursInRoute();
        bool getTripInProgress();

        void setTransport(Transport* transport);
        void setPassenger(std::list<Passenger*> passenger);
        void setOrigin(City* origin);
        void setDestination(City* destination);
        void setNextTrip(Trip* nextTrip);
        void setHoursInRoute(int hoursInRoute);
        void setTripInProgress(bool tripInProgress);
        void addPassenger(Passenger* passenger);
        void removePassenger(Passenger* passenger);
        void startTrip();
        void endTrip();
        void tripRelatory();
};

#endif