#include "../../include/enums/RouteTypeEnum.hpp"

std::string routeTypeToString(RouteTypeEnum routeType) {
    switch (routeType) {
        case LAND: return "LAND";
        case AQUATIC: return "AQUATIC";
        default: return "UNKNOWN";
    }
}

RouteTypeEnum stringToRouteType(const std::string& routeTypeStr) {
    if (routeTypeStr == "LAND") {
        return RouteTypeEnum::LAND;
    } else if (routeTypeStr == "AQUATIC") {
        return RouteTypeEnum::AQUATIC;
    } else {
        return RouteTypeEnum::UNKNOWN;
    }
}
