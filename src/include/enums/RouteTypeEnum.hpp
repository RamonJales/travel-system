#ifndef ROUTE_TYPE_ENUM_HPP
#define ROUTE_TYPE_ENUM_HPP

#include <string>

enum RouteTypeEnum {
    LAND,
    AQUATIC,
    UNKNOWN
};

std::string routeTypeToString(RouteTypeEnum routeType);

RouteTypeEnum stringToRouteType(const std::string& routeTypeStr);

#endif
