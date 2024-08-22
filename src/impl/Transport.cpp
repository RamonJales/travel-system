#include "../include/Transport.hpp"

/**
 * @brief Construtor para inicializar um transporte.
 *
 * @param transportName Nome do transporte.
 * @param transportType Tipo do transporte.
 * @param capacity Capacidade do transporte (número de passageiros).
 * @param speed Velocidade do transporte em km/h.
 * @param distanceBetweenRest Distância entre períodos de descanso em km.
 * @param restTime Tempo de descanso em horas.
 * @param currentRestTime Tempo atual de descanso em horas.
 * @param currentPlace Ponteiro para a cidade onde o transporte está localizado.
 * @param transportInProgress Indica se o transporte está em uma viagem.
 * @param hoursRemaining Horas restantes na viagem atual.
 */
Transport::Transport(std::string transportName, TransportTypeEnum transportType, int capacity, float speed, float distanceBetweenRest, 
                     float restTime, float currentRestTime, City* currentPlace, bool transportInProgress, double hoursRemaining)
    : transportName(std::move(transportName)), 
      transportType(transportType), 
      capacity(capacity), 
      speed(speed), 
      distanceBetweenRest(distanceBetweenRest), 
      restTime(restTime), 
      currentRestTime(currentRestTime), 
      currentPlace(currentPlace), 
      transportInProgress(transportInProgress), 
      hoursRemaining(hoursRemaining) {}

/**
 * @brief Obtém o nome do transporte.
 * @return Nome do transporte.
 */
std::string Transport::getTransportName() const {
    return transportName;
}

/**
 * @brief Obtém o tipo de transporte.
 * @return Tipo do transporte (enum TransportTypeEnum).
 */
TransportTypeEnum Transport::getTransportType() const {
    return transportType;
}

/**
 * @brief Obtém a capacidade do transporte.
 * @return Capacidade do transporte (número de passageiros).
 */
int Transport::getCapacity() const {
    return capacity;
}

/**
 * @brief Obtém a velocidade do transporte.
 * @return Velocidade do transporte em km/h.
 */
float Transport::getSpeed() const {
    return speed;
}

/**
 * @brief Obtém a distância entre períodos de descanso.
 * @return Distância entre períodos de descanso em km.
 */
float Transport::getDistanceBetweenRest() const {
    return distanceBetweenRest;
}

/**
 * @brief Obtém o tempo de descanso.
 * @return Tempo de descanso em horas.
 */

float Transport::getRestTime() const {
    return restTime;
}

// Método para definir o tempo de descanso
void Transport::setRestTime(float time) {
    restTime = time;
}

/**
 * @brief Obtém o tempo atual de descanso.
 * @return Tempo atual de descanso em horas.
 */
float Transport::getCurrentRestTime() const {
    return currentRestTime;
}

/**
 * @brief Obtém a cidade onde o transporte está localizado.
 * @return Ponteiro para a cidade atual.
 */
City* Transport::getCurrentPlace() const {
    return currentPlace;
}

/**
 * @brief Define a cidade onde o transporte está localizado.
 * @param place Ponteiro para a cidade onde o transporte deve ser localizado.
 */
void Transport::setCurrentPlace(City* place) {
    currentPlace = place;
}

/**
 * @brief Verifica se o transporte está em viagem.
 * @return Verdadeiro se o transporte está em viagem, falso caso contrário.
 */
bool Transport::isInProgress() const {
    return transportInProgress;
}

/**
 * @brief Obtém o tempo restante da viagem atual.
 * @return Horas restantes na viagem atual.
 */
double Transport::getHoursRemaining() const {
    return hoursRemaining;
}

void Transport::setHoursRemaining(double hours) {
    hoursRemaining = hours;
}
/**
 * @brief Define se o transporte está em viagem e as horas restantes.
 * @param inProgress Verdadeiro se a viagem está em progresso, falso caso contrário.
 * @param hours Horas restantes na viagem atual.
 */
void Transport::setTransportStatus(bool inProgress, double hours) {
    transportInProgress = inProgress;
    hoursRemaining = hours;
}
