#include <iostream>
#include "include/enums/RouteTypeEnum.hpp"
#include "include/interface.hpp"
#include "include/City.hpp"
#include "include/Passenger.hpp"
#include "include/Route.hpp"
#include "include/Transport.hpp"
#include "include/Trip.hpp"
#include "include/CityGraph.hpp"
#include <unordered_map>
#include <list>

#include "include/repositories/repositoryCity.hpp"
#include "include/repositories/repositoryTransport.hpp"
#include "include/repositories/repositoryPassenger.hpp"
#include "include/repositories/repositoryTrip.hpp"
#include "include/repositories/repositoryRoute.hpp"

#include <list>
#include <cstdlib>
#include <limits>
#include <algorithm>

int main() {
    sqlite3 *db;
    if (sqlite3_open("travel-system-database.db", &db)) {
        std::cerr << "Erro ao abrir o banco de dados: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    createTableCities(db);
    createTableTransports(db);
    createTablePassengers(db);
    createTableTrips(db);
    createTableRoutes(db);

    std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph;
    CityGraph g = CityGraph(cityGraph);

    std::vector<Route> routes = findAllRoutesInRoutes(db);
    for (Route route : routes) {
        g.addEdge(route.getOriginCity(), route.getDestinationCity(), route.getDistance());
    }

    int option;
    do {
        std::system("clear");
        print_menu();

        std::cout << "Digite a opção: ";
        while (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Digite um número: ";
        }
        getchar();


        switch (option) {
           case 1: 
                {
                    std::string cityName;
                    std::cout << "Digite o nome da cidade: ";
                    std::getline(std::cin, cityName);

                    cityName.erase(0, cityName.find_first_not_of(' '));
                    cityName.erase(cityName.find_last_not_of(' ') + 1);

                    if (cityName.empty() || std::all_of(cityName.begin(), cityName.end(), ::isdigit)) {
                        std::cout << "Nome inválido. O nome da cidade não pode ser vazio nem conter apenas números." << std::endl;
                        break;
                    }

                    City* city = findCityByName(db, cityName);
                    if (city != nullptr) {
                        std::cout << "A cidade \"" << cityName << "\" já está cadastrada no banco de dados." << std::endl;
                    } else {
                        if (addCityInCities(db, cityName)) {
                            std::cout << "Cidade adicionada com sucesso!" << std::endl;
                        }
                    }
                    break;
                } 
            case 2: 
                {
                    std::string transportName;
                    std::cout << "Digite o nome do transporte: ";
                    std::getline(std::cin, transportName);
                    if (transportName.empty()) {
                        std::cerr << "Erro: O nome do transporte não pode ser vazio." << std::endl;
                        break;
                    }

                    Transport* transport = findTransportByName(db, transportName);
                    if (transport != nullptr) {
                        std::cout << "O transporte \"" << transportName << "\" já está cadastrado no banco de dados." << std::endl;
                        break;
                    }

                    std::string transportTypeString;
                    std::cout << "Digite o tipo do transporte (GROUND ou WATER): ";
                    std::getline(std::cin, transportTypeString);
                    if (transportTypeString.empty()) {
                        std::cerr << "Erro: O tipo do transporte não pode ser vazio." << std::endl;
                        break;
                    }

                    TransportTypeEnum transportType = stringToTransportType(transportTypeString);

                    int capacity;
                    std::cout << "Digite a capacidade: ";
                    std::cin >> capacity;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(capacity < 0){
                        std::cout << "Capacidade inválida." << std::endl;
                        break;
                    }

                    float speed;
                    std::cout << "Digite a velocidade (em km/h): ";
                    std::cin >> speed;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(speed <= 0){
                        std::cout << "Velocidade inválida." << std::endl;
                        break;
                    }

                    float distanceBetweenRest;
                    std::cout << "Digite a distância entre descansos (em km): ";
                    std::cin >> distanceBetweenRest;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(distanceBetweenRest < 0){
                        std::cout << "Distância inválida." << std::endl;
                        break;
                    }

                    float restTime;
                    std::cout << "Digite o tempo de descanso (em h): ";
                    std::cin >> restTime;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(restTime < 0){
                        std::cout << "Tempo inválido." << std::endl;
                        break;
                    }

                    std::string currentPlace;
                    std::cout << "Digite o nome da cidade atual: ";
                    std::getline(std::cin, currentPlace);
                    if (currentPlace.empty()) {
                        std::cerr << "Erro: O nome da cidade atual não pode ser vazio." << std::endl;
                        break;
                    }

                    City* city = findCityByName(db, currentPlace);
                    if(city == nullptr){
                        std::cout << "Cidade " << currentPlace << " não existe." << std::endl;
                        break;
                    }

                    if(addTransportInTransports(db, transportName, transportTypeToString(transportType), capacity, speed, 
                    distanceBetweenRest, restTime, currentPlace, 0)){
                        std::cout << "Transporte " << transportName << " adicionado com sucesso." << std::endl;
                    }

                    break;
                }
             case 3:
                {
                    std::string passengerName;
                    std::string cityName;

                    std::cout << "Digite o nome do passageiro: ";
                    std::getline(std::cin, passengerName);

                    if (passengerName.empty() || std::all_of(passengerName.begin(), passengerName.end(), ::isdigit)) {
                        std::cout << "Nome inválido. O nome da passageiro não pode ser vazio nem conter apenas números." << std::endl;
                        break;
                    }

                    std::cout << "Digite o nome da cidade de origem: ";
                    std::getline(std::cin, cityName);

                    if (cityName.empty() || std::all_of(cityName.begin(), cityName.end(), ::isdigit)) {
                        std::cout << "Nome inválido. O nome da cidade não pode ser vazio nem conter apenas números." << std::endl;
                        break;
                    }

                    Passenger* passenger = findPassengerByName(db, passengerName);
                    if (passenger != nullptr) {
                        std::cout << "O passageiro \"" << passengerName << "\" já está cadastrado no banco de dados." << std::endl;
                    } else {
                        City* cityPtr = findCityByName(db, cityName);
                        if (cityPtr == nullptr) {
                            std::cerr << "Erro: A cidade de origem \"" << cityName << "\" não foi encontrada no banco de dados." << std::endl;
                            break;
                        }

                        City originCity = *cityPtr;

                        if (addPassengerInPassengers(db, passengerName, originCity.getCityName())) {
                            std::cout << "Passageiro cadastrado com sucesso!" << std::endl;
                        } else {
                            std::cerr << "Erro ao cadastrar o passageiro." << std::endl;
                        }
                    }

                    break;
                }
            case 4:
                {
                    std::string originCityName;
                    std::string destinationCityName;
                    std::string routeTypeString;
                    RouteTypeEnum routeType;
                    float routeDistance;

                    std::cout << "Digite o nome da cidade de origem: ";
                    std::getline(std::cin, originCityName);

                    if(findCityByName(db, originCityName) == nullptr){
                        std::cout << "Cidade " << originCityName << " não existe." << std::endl;
                        break;
                    }

                    std::cout << "Digite o nome da cidade de destino: ";
                    std::getline(std::cin, destinationCityName);

                    if(findCityByName(db, destinationCityName) == nullptr){
                        std::cout << "Cidade " << destinationCityName << " não existe." << std::endl;
                        break;
                    }

                    std::cout << "Digite o tipo da rota (1 - Terrestre, 2 - Aquatico): ";
                    std::getline(std::cin, routeTypeString);

                    if (routeTypeString == "1") {
                        routeType = RouteTypeEnum::LAND;
                    } else if (routeTypeString == "2") {
                        routeType = RouteTypeEnum::AQUATIC;
                    } else {
                        std::cout << "Tipo de rota inválido." << std::endl;
                        break;
                    }

                    Route* possibleRoute = findRouteByCities(db, originCityName, destinationCityName);
                    if(possibleRoute != nullptr){
                        if(possibleRoute->getRouteType() == routeType){
                            std::cout << "Rota já existente." << std::endl;
                            break;
                        }
                    }

                    std:: cout << "Digite a distância da rota (em km): ";
                    std::cin >> routeDistance;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if(routeDistance < 0){
                        std::cout << "Distância inválida." << std::endl;
                        break;
                    }

                    Route* route = new Route(originCityName, destinationCityName, routeType, routeDistance);
                    g.addEdge(originCityName, destinationCityName, routeDistance);

                    addRouteInRoutes(db, *route);
                    std::cout << "Rota cadastrada com sucesso." << std::endl;
                    break;
                }
            case 5:
                {
                    std::string originCity;
                    std::string destinationCity;
                    std::string transportName;
                    std::list<Passenger*> passengers;

                    std::cout << "Digite a cidade de origem: ";
                    std::getline(std::cin, originCity);
                    City* possibleOriginCity = findCityByName(db, originCity);
                    if (possibleOriginCity == nullptr) {
                        std::cout << "Cidade " << originCity << " não existe." << std::endl;
                        break;
                    }

                    std::cout << "Digite a cidade de destino: ";
                    std::getline(std::cin, destinationCity);
                    City* possibleDestinationCity = findCityByName(db, destinationCity);
                    if (possibleDestinationCity == nullptr) {
                        std::cout << "Cidade " << destinationCity << " não existe." << std::endl;
                        break;
                    }

                    std::cout << "Digite o nome do transporte: ";
                    std::getline(std::cin, transportName);
                    Transport* possibleTransport = findTransportByName(db, transportName);
                    if (possibleTransport == nullptr) {
                        std::cout << "Transporte " << transportName << " não existe." << std::endl;
                        break;
                    }

                    if (possibleTransport->getCurrentPlace()->getCityName() != originCity) {
                        std::cout << "O transporte " << transportName << " não está na cidade de origem." << std::endl;
                        break;
                    }

                    int opt = 1;
                    while (opt != 0) {
                        std::cout << "0 - Parar de adicionar passageiros" << std::endl;
                        std::cout << "1 - Adicionar um passageiro" << std::endl;
                        std::cin >> opt;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        if (opt == 1) {
                            if (passengers.size() >= possibleTransport->getCapacity()) {
                                std::cout << "Erro: O número de passageiros excede a capacidade do transporte." << std::endl;
                                break;
                            }

                            std::string passengerName;
                            std::cout << "Digite o nome do passageiro: ";
                            std::getline(std::cin, passengerName);

                            Passenger* passenger = findPassengerByName(db, passengerName);
                            if (passenger == nullptr) {
                                std::cout << "Passageiro " << passengerName << " não existe." << std::endl;
                            } else {
                                if (passenger->getCurrentLocation().getCityName() != originCity) {
                                    std::cout << "O passageiro " << passengerName << " não está na cidade de origem." << std::endl;
                                } else {
                                    passengers.push_back(passenger);
                                    std::cout << "Passageiro " << passengerName << " adicionado com sucesso." << std::endl;
                                }
                            }
                        } else if (opt != 0) {
                            std::cout << "Opção inválida." << std::endl;
                        }
                    }

                    if (passengers.empty()) {
                        std::cout << "Erro: A viagem precisa de pelo menos um passageiro para iniciar." << std::endl;
                        break;
                    }

                    std::vector<std::string> path = g.CityGraph::findShortestPath(originCity, destinationCity);
                    double totalDuration = 0.0;
                    int tripId = -1;

                    if (!path.empty()) {
                        for (size_t i = 0; i < path.size() - 1; i++) {
                            std::string start = path[i];
                            std::string end = path[i + 1];
                            Route* route = findRouteByCities(db, start, end);
                            if (route == nullptr) {
                                std::cout << "Erro no sistema! Não existe trajeto entre " << start << " e " << end << std::endl;
                                break;
                            }

                            double routeDistance = route->getDistance();
                            double duration = routeDistance / possibleTransport->getSpeed();
                            totalDuration += duration;

                            tripId = addTripInTrips(db, transportName, start, end, totalDuration, passengers, false);
                        }
                        std::cout << "A viagem levará um total de " << (totalDuration + possibleTransport->getRestTime()) << " horas." << std::endl;
                    } else {
                        std::cout << "Não existe trajeto entre " << originCity << " e " << destinationCity << std::endl;
                        break;
                    }

                    if (tripId != -1) {
                        bool updateTrip = updateTripInProgress(db, tripId, true);
                        if (!updateTrip) {
                            std::cerr << "Erro ao atualizar a viagem para 'em andamento'." << std::endl;
                        }
                    }

                    possibleTransport->setTransportStatus(true, totalDuration);
                    editTransportInTransports(db, *possibleTransport);

                    break;
                }


           case 6:
                {
                    double hoursToAdvance;
                    std::cout << "Digite a quantidade de horas para avançar: ";
                    std::cin >> hoursToAdvance;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (advanceHours(db, hoursToAdvance, g)) {
                        std::cout << "Horas avançadas com sucesso." << std::endl;
                    } else {
                        std::cout << "Erro ao avançar as horas." << std::endl;
                    }

                    break;
                }

            case 7:
                {
                    std::list<Transport*> transports = findAllTransports(db);
                    if (transports.empty()) {
                        std::cout << "Não há transportes cadastrados." << std::endl;
                    } else {
                        for (Transport* transport : transports) {
                            if (transport == nullptr) {
                                std::cerr << "Erro: Transporte nulo encontrado na lista." << std::endl;
                                continue;
                            }

                            std::cout << "======================================" << std::endl;
                            std::cout << "Nome: " << transport->getTransportName() << std::endl;
                            std::cout << "Tipo: " << transportTypeToString(transport->getTransportType()) << std::endl;
                            std::cout << "Capacidade: " << transport->getCapacity() << std::endl;
                            std::cout << "Velocidade: " << transport->getSpeed() << " km/h" << std::endl;

                            if (transport->isInProgress()) {
                                std::cout << "Localização Atual: No caminho" << std::endl;
                            } else {
                                City* currentPlace = transport->getCurrentPlace();
                                if (currentPlace) {
                                    std::cout << "Localização Atual: " << currentPlace->getCityName() << std::endl;
                                } else {
                                    std::cout << "Localização Atual: No caminho" << std::endl;
                                }
                            }

                            std::cout << "======================================" << std::endl;
                        }
                    }
                    break;
                }

            case 8:
                {
                    std::list<Passenger*> passengers = findAllPassengers(db);
                    if (passengers.empty()) {
                        std::cout << "Não há passageiros cadastrados." << std::endl;
                    } else {
                        for (Passenger* passenger : passengers) {
                            std::cout << "======================================" << std::endl;
                            std::cout << "Nome: " << passenger->getName() << std::endl;

                            City currentLocation = passenger->getCurrentLocation();
                            if (currentLocation.getCityName().empty()) {
                                std::cout << "Localização Atual: Em caminho" << std::endl;
                            } else {
                                std::cout << "Localização Atual: " << currentLocation.getCityName() << std::endl;
                            }

                            std::cout << "======================================" << std::endl;
                        }
                    }
                    break;
                }

            
            case 9:
                {
                    std::list<City> cities;
                    if(listCityInCities(db, cities)){
                        if (!cities.empty()) {
                            std::cout << "Cidades cadastradas:" << std::endl;
                            for (const City& city : cities) {
                                std::cout << city.getCityName() << std::endl;
                            }
                        } else {
                            std::cout << "Não há cidades cadastradas." << std::endl;
                        }
                    }
                    break;
                }
            case 10: 
                {   
                    std::list<City> cities;
                    if (listCityInCities(db, cities)) {
                        if (cities.empty()) {
                            std::cout << "Não há cidades cadastradas." << std::endl;
                        } else {
                            findMostFrequentCities(db); 
                        }
                    }
                    break;
                }
            
            case 11:
                {
                    std::list<Trip*> trips = listTripsInProgress(db);

                    if(trips.empty()) {
                        std::cout << "Não há viagens em andamento." << std::endl;
                    } else {
                        for(Trip* trip : trips) {
                            if (trip == nullptr) {
                                std::cerr << "Erro: Ponteiro de Trip nulo encontrado." << std::endl;
                                continue;
                            }

                            City* origin = trip->getOrigin();
                            City* destination = trip->getDestination();
                            Transport* transport = trip->getTransport();

                            if (origin == nullptr || destination == nullptr || transport == nullptr) {
                                std::cerr << "Erro: Ponteiro nulo encontrado em Trip." << std::endl;
                                continue;
                            }

                            std::cout << "======================================" << std::endl;
                            std::cout << "Viagem ID: " << trip->getId() << std::endl;
                            std::cout << "Origem: " << origin->getCityName() << std::endl;
                            std::cout << "Destino: " << destination->getCityName() << std::endl;
                            std::cout << "Transporte: " << transport->getTransportName() << std::endl;
                            std::cout << "Duração: " << trip->getHoursInRoute() << " horas" << std::endl;
                            std::cout << "Passageiros: ";
                            
                            std::list<Passenger*> passengers = trip->getPassengers();
                            int countForNames = 0;
                            for(Passenger* passenger : passengers) {
                                if (passenger != nullptr) {
                                    if(countForNames > 0){
                                        std::cout << ", ";
                                    }
                                    std::cout << passenger->getName();
                                } else {
                                    std::cerr << "Erro: Passageiro nulo encontrado." << std::endl;
                                }
                                countForNames++;
                            }
                            std::cout << std::endl;
                            std::cout << "======================================" << std::endl;
                        }
                    }

                    for (Trip* trip : trips) {
                        delete trip; 
                    }

                    break;
                }
            case 12:
                {
                    std::list<Trip*> finishedTrips = listTripInTrips(db);

                    if(finishedTrips.empty()) {
                        std::cout << "Não há viagens finalizadas." << std::endl;
                    } else {
                        for(Trip* trip : finishedTrips) {
                            if (trip == nullptr) {
                                std::cerr << "Erro: Ponteiro de Trip nulo encontrado." << std::endl;
                                continue;
                            }
                            if(!(trip->isTripInProgress())){
                                City* origin = trip->getOrigin();
                                City* destination = trip->getDestination();
                                Transport* transport = trip->getTransport();

                                if (origin == nullptr || destination == nullptr || transport == nullptr) {
                                    std::cerr << "Erro: Ponteiro nulo encontrado em Trip." << std::endl;
                                    continue;
                                }

                                std::cout << "======================================" << std::endl;
                                std::cout << "Viagem ID: " << trip->getId() << std::endl;
                                std::cout << "Origem: " << origin->getCityName() << std::endl;
                                std::cout << "Destino: " << destination->getCityName() << std::endl;
                                std::cout << "Transporte: " << transport->getTransportName() << std::endl;
                                std::cout << "Duração: " << trip->getHoursInRoute() << " horas" << std::endl;
                                std::cout << "======================================" << std::endl;
                            }

                        }
                    }

                    break;
                }
                case 13:
                {
                    std::string cityName;
                    std::cout << "Digite o nome da cidade que deseja deletar: ";
                    std::getline(std::cin, cityName);

                    if(removeCityInCities(db, cityName)){
                        std::cout << "Cidade " << cityName << " removida com sucesso." << std::endl;
                    } else {
                        std::cout << "Cidade " << cityName << " não existe." << std::endl;
                    }
                    break;
                }
                case 14:
                {
                    std::string transportName;
                    std::cout << "Digite o nome do transporte que deseja deletar: ";
                    std::getline(std::cin, transportName);

                    if(removeTransportInTransports(db, transportName)){
                        std::cout << "Transporte " << transportName << " removido com sucesso." << std::endl;
                    } else {
                        std::cout << "Transporte " << transportName << " não existe." << std::endl;
                    }
                    break;
                }
                case 15:
                {
                    std::string passengerName;
                    std::cout << "Digite o nome do passageiro que deseja deletar: ";
                    std::getline(std::cin, passengerName);

                    if(removePassengerInPassengers(db, passengerName)){
                        std::cout << "Passageiro " << passengerName << " removido com sucesso." << std::endl;
                    } else {
                        std::cout << "Passageiro " << passengerName << " não existe." << std::endl;
                    }
                    break;
                }
                case 16:
                {
                    std::string originCityName;
                    std::string destinationCityName;

                    std::cout << "Digite o nome da cidade de origem: ";
                    std::getline(std::cin, originCityName);

                    std::cout << "Digite o nome da cidade de destino: ";
                    std::getline(std::cin, destinationCityName);

                    if(deleteRouteByIdInRoutes(db, originCityName, destinationCityName)){
                        std::cout << "Rota entre " << originCityName << " e " << destinationCityName << " removida com sucesso." << std::endl;
                    } else {
                        std::cout << "Rota entre " << originCityName << " e " << destinationCityName << " não existe." << std::endl;
                    }
                    break;
                }
                case 17:
                {
                    std::vector<Route> routes;
                    routes = findAllRoutesInRoutes(db);
                    if(routes.empty()){
                        std::cout << "Não há rotas cadastradas." << std::endl;
                    } else {
                        for(Route route : routes){
                            std::cout << "======================================" << std::endl;
                            std::cout << "Origem: " << route.getOriginCity() << std::endl;
                            std::cout << "Destino: " << route.getDestinationCity() << std::endl;
                            std::cout << "Distância: " << route.getDistance() << " km" << std::endl;
                            std::cout << "======================================" << std::endl;
                        }
                    }
                    break;
                }

            default:
                if(option != 0) {
                    std::cout << "Escolha inválida. Por favor, tente novamente." << std::endl;
                }
                break;

        }
        std::cout << "Pressione Enter para continuar...";
        getchar();
    } while (option != 0);

    sqlite3_close(db);

    return 0;
}

