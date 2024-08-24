/**
 * @file route_type_enum.hpp
 * @brief Declaração do enum RouteTypeEnum e funções auxiliares para conversão de tipo de rota.
 */

#ifndef ROUTE_TYPE_ENUM_HPP
#define ROUTE_TYPE_ENUM_HPP

#include <string>

/**
 * @enum RouteTypeEnum
 * @brief Enumeração que representa os diferentes tipos de rotas.
 *
 * Este enum é utilizado para categorizar as rotas com base no seu tipo.
 */
enum RouteTypeEnum {
    LAND,      ///< Rota terrestre.
    AQUATIC,   ///< Rota aquática.
    UNKNOWN    ///< Tipo de rota desconhecido.
};

/**
 * @brief Converte um valor de RouteTypeEnum para uma representação de string.
 *
 * Esta função converte um valor de RouteTypeEnum para uma string correspondente que representa o tipo de rota.
 *
 * @param routeType Valor do tipo RouteTypeEnum a ser convertido.
 * @return String que representa o tipo de rota.
 */
std::string routeTypeToString(RouteTypeEnum routeType);

/**
 * @brief Converte uma string para o valor correspondente de RouteTypeEnum.
 *
 * Esta função converte uma string que representa um tipo de rota para o valor correspondente de RouteTypeEnum.
 *
 * @param routeTypeStr String que representa o tipo de rota.
 * @return Valor correspondente do tipo RouteTypeEnum. Retorna UNKNOWN se a string não corresponder a um tipo de rota válido.
 */
RouteTypeEnum stringToRouteType(const std::string& routeTypeStr);

#endif // ROUTE_TYPE_ENUM_HPP
