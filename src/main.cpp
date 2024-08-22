#include <iostream>
#include "include/enums/RouteTypeEnum.hpp"
#include "include/interface.hpp"
#include "include/City.hpp"
#include "include/Controller.hpp"
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

// #include "include/Travel.hpp"
#include <list>
#include <cstdlib>
#include <limits>

int main() {
    //iniciar banco de dados e criar as tabelas
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

    // Buscar to das as rotas no banco com um findAllRoutes, e adicionar no grafo
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
                    Transport* transport = findTransportByName(db, transportName);
                    if (transport != nullptr) {
                        std::cout << "O transporte \"" << transportName << "\" já está cadastrado no banco de dados." << std::endl;
                        break;
                    }

                    std::string transportTypeString;
                    std::cout << "Digite o tipo do transporte (GROUND or WATER): ";
                    std::getline(std::cin, transportTypeString);
                    TransportTypeEnum transportType = stringToTransportType(transportTypeString);

                    int capacity;
                    std::cout << "Digite a capacidade: ";
                    std::cin >> capacity;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(capacity <= 0){
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
                        std::cout << "Tempo inválida." << std::endl;
                        break;
                    }

                    std::string currentPlace;
                    std::cout << "Digite o nome da cidade atual: ";
                    std::getline(std::cin, currentPlace);
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

                    // Get the passenger's name
                    std::cout << "Digite o nome do passageiro: ";
                    std::getline(std::cin, passengerName);

                    // Check if the passenger's name is empty
                    if (passengerName.empty()) {
                        std::cerr << "Erro: O nome do passageiro não pode ser vazio." << std::endl;
                        break;
                    }

                    // Get the name of the origin city
                    std::cout << "Digite o nome da cidade de origem: ";
                    std::getline(std::cin, cityName);

                    // Check if the city name is empty
                    if (cityName.empty()) {
                        std::cerr << "Erro: O nome da cidade de origem não pode ser vazio." << std::endl;
                        break;
                    }

                    // Find the passenger by name in the database
                    Passenger* passenger = findPassengerByName(db, passengerName);
                    if (passenger != nullptr) {
                        std::cout << "O passageiro \"" << passengerName << "\" já está cadastrado no banco de dados." << std::endl;
                    } else {
                        // Find the city by name in the database
                        City* cityPtr = findCityByName(db, cityName);
                        if (cityPtr == nullptr) {
                            std::cerr << "Erro: A cidade de origem \"" << cityName << "\" não foi encontrada no banco de dados." << std::endl;
                            break;
                        }

                        // Dereference the pointer to get the City object
                        City originCity = *cityPtr;

                        // Add the passenger along with the origin city
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

                    //Verificar se a rota entre as cidades já existe no tipo de rota escolhido
                    Route* possibleRoute = findRouteByCities(db, originCityName, destinationCityName);
                    if(possibleRoute != nullptr){
                        if(possibleRoute->getRouteType() == routeType){
                            std::cout << "Rota já existente." << std::endl;
                            break;
                        }
                    }

                    std:: cout << "Digite a distância da rota: (em km) ";
                    std::cin >> routeDistance;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if(routeDistance < 0){
                        std::cout << "Distância inválida." << std::endl;
                        break;
                    }

                    Route* route = new Route(originCityName, destinationCityName, routeType, routeDistance);
                    g.addEdge(originCityName, destinationCityName, routeDistance);

                    addRouteInRoutes(db, *route);
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

                    possibleTransport->setCurrentPlace(possibleOriginCity); // Temporário para ajustar a localização

                    int opt = 1;
                    while (opt != 0) {
                        std::cout << "0 - Se deseja parar de adicionar passageiros" << std::endl;
                        std::cout << "1 - Se deseja adicionar um passageiro" << std::endl;
                        std::cin >> opt;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        switch (opt) {
                            case 0:
                                break;
                            case 1:
                            {
                                std::string passengerName;
                                std::cout << "Digite o nome do passageiro: ";
                                std::getline(std::cin, passengerName);
                                Passenger* passenger = findPassengerByName(db, passengerName);
                                if (passenger == nullptr) {
                                    std::cout << "Passageiro " << passengerName << " não existe." << std::endl;
                                    break;
                                } else {
                                    passengers.push_back(passenger);
                                    std::cout << "Passageiro " << passengerName << " adicionado com sucesso." << std::endl;
                                    std::cout << "Pressione Enter para continuar...";
                                    getchar();
                                    std::system("clear");
                                }
                                break;
                            }
                            default:
                                std::cout << "Opção inválida." << std::endl;
                                break;
                        }
                    }

                    if (possibleTransport->getCurrentPlace()->getCityName() != originCity) {
                        std::cout << "O transporte " << transportName << " não está na cidade de origem." << std::endl;
                        break;
                    }

                    std::vector<std::string> path = g.CityGraph::findShortestPath(originCity, destinationCity);
                    double totalDuration = 0.0;
                    int tripId = -1;

                    if (!path.empty()) {
                        for (int i = 0; i < path.size() - 1; i++) {
                            std::string start = path[i];
                            std::string end = path[i + 1];
                            Route* route = findRouteByCities(db, start, end);
                            if (route == nullptr) {
                                std::cout << "Erro no sistema! Não existe trajeto entre " << start << " e " << end << std::endl;
                                break;
                            }
                            double duration = route->getDistance() / possibleTransport->getSpeed();
                            totalDuration += duration;
                            totalDuration += possibleTransport->getRestTime();
                            possibleTransport->setTransportStatus(true, totalDuration);
                            tripId = addTripInTrips(db, transportName, start, end, duration, passengers, false); // Cria a viagem inicialmente com trip_in_progress = false
                        }
                        std::cout << "A viagem levará um total de " << totalDuration << " horas." << std::endl;
                    } else {
                        std::cout << "Não existe trajeto entre " << originCity << " e " << destinationCity << std::endl;
                        break;
                    }
                

                    // Atualiza a viagem para marcar como em andamento
                    if(tripId != -1){
                        bool updateTrip = updateTripInProgress(db, tripId, true);
                        if (!updateTrip) {
                            std::cerr << "Erro ao atualizar a viagem para 'em andamento'." << std::endl;
                        }
                    } else {
                        break;
                    }

                     // Atualiza o status do transporte para em viagem
                    editTransportInTransports(db, *possibleTransport);

                    break;
                }


           case 6:
                {
                    int hoursToAdvance;
                    std::cout << "Digite a quantidade de horas para avançar: ";
                    std::cin >> hoursToAdvance;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (advanceHours(db, hoursToAdvance)) {
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
                            std::cout << "======================================" << std::endl;
                            std::cout << "Nome: " << transport->getTransportName() << std::endl;
                            std::cout << "Tipo: " << transportTypeToString(transport->getTransportType()) << std::endl;
                            std::cout << "Capacidade: " << transport->getCapacity() << std::endl;
                            std::cout << "Velocidade: " << transport->getSpeed() << " km/h" << std::endl;

                            if (transport->isInProgress()) {
                                std::cout << "Localização Atual: No caminho" << std::endl;
                            } else {
                                std::cout << "Localização Atual: " << transport->getCurrentPlace()->getCityName() << std::endl;
                            }

                            std::cout << "======================================" << std::endl;
                        }
                    }
                    break;
                }

            
            case 8:
                {
                    std::list<Passenger*> passengers = findAllPassengers(db);
                    if(passengers.empty()) {
                        std::cout << "Não há passageiros cadastrados." << std::endl;
                    } else {
                        for(Passenger* passenger : passengers) {
                            std::cout << "======================================" << std::endl;
                            std::cout << "Nome: " << passenger->getName() << std::endl;
                            std::cout << "Localização Atual: " << passenger->getCurrentLocation().getCityName() << std::endl;
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

                    // Limpeza dos objetos Trip após o uso
                    for (Trip* trip : trips) {
                        delete trip; // Certifique-se de que Trip foi alocado com `new` e não é gerenciado por outro lugar
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

