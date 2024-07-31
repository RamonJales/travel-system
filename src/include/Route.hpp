#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <iostream>
#include "enums/RouteTypeEnum.hpp"

class Route {
    private:
        std::string routeName;
        std::string originCity;
        std::string destinationCity;
        RouteTypeEnum routeType;
        float distance;
    public:
        Route(std::string routeName, std::string orgiginCity, std::string destinationCity, RouteTypeEnum routeType, float distance);
        std::string getRouteName();
        std::string getOriginCity();
        std::string getDestinationCity();
        RouteTypeEnum getRouteType();
        float getDistance();
        void setRouteName(std::string routeName);
        void setOriginCity(std::string orgiginCity);
        void setDestinationCity(std::string destinationCity);
        void setRouteType(RouteTypeEnum routeType);
        void setDistance(float distance);
};

#endif
