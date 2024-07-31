#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include <iostream>
#include "enums/TransportTypeEnum.hpp"
#include "City.hpp"

class Transport {
    private:
        std::string transportName;
        TransportTypeEnum transportType;
        int capacity;
        float speed;
        float distanceBetweenRest;
        float restTime;
        float currentRestTime;
        City* currentPlace;
    public:
        Transport(std::string transportName, TransportTypeEnum transportType, int capacity, float speed, 
        float distanceBetweenRest, float restTime, float currentRestTime,  City* currentPlace);
        std::string getTransportName();
        TransportTypeEnum getTransportType();
        int getCapacity();
        float getSpeed();
        float getDistanceBetweenRest();
        float getRestTime();
        float getCurrentRestTime();
        City* getCurrentPlace();
        void setCurrentPlace(City* place);

};

#endif
