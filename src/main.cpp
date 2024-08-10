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

// #include "include/Travel.hpp"
#include <list>
#include <cstdlib>
#include <limits>

int main() {
    std::list<City> cityDatabase;
    std::list<Passenger> passengerDatabase;
    std::list<Route> routeDatabase;
    // std::list<Travel> travelDatabase;
    int cityId = 1;
    int passagerId = 1;
    int routeId = 1;
    int travelId = 1;

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

    //tratar as exceções

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
                    std::cout << "Digite o tipo do transporte: ";
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
                    if(distanceBetweenRest <= 0){
                        std::cout << "Distância inválida." << std::endl;
                        break;
                    }

                    float restTime;
                    std::cout << "Digite o tempo de descanso (em h): ";
                    std::cin >> restTime;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    if(restTime <= 0){
                        std::cout << "Tempo inválida." << std::endl;
                        break;
                    }

                    if(addTransportInTransports(db, transportName, transportTypeToString(transportType), capacity, speed, 
                    distanceBetweenRest, restTime)){
                        std::cout << "Transporte " << transportName << " adicionado com sucesso." << std::endl;
                    }

                    break;
                }
            case 3:
                {
                    std::string passengerName;

                    std::cout << "Digite o nome do passageiro: ";
                    std::getline(std::cin, passengerName);

                    if (passengerName.empty()) {
                        std::cerr << "Erro: O nome do passageiro não pode ser vazio." << std::endl;
                        break;
                    }

                    Passenger* passenger = findPassengerByName(db, passengerName);
                    if (passenger != nullptr) {
                        std::cout << "O passageiro \"" << passengerName << "\" já está cadastrado no banco de dados." << std::endl;
                    } else {
                        if (addPassengerInPassengers(db, passengerName)) {
                            std::cout << "Passageiro cadastrado com sucesso!" << std::endl;
                        } 
                    }

                    break;
                }

            case 4:
                {
                    std::cout << "Opção 4" << std::endl;
                        std::unordered_map<std::string, std::list<std::pair<std::string, double>>> cityGraph;
                        CityGraph g = CityGraph(cityGraph);
                        
                        g.addEdge("A", "X", 5.0);
                        g.addEdge("X", "Y", 10.0);
                        g.addEdge("Y", "B", 3.0);
                        g.addEdge("A", "B", 5.0);

                        std::string start = "A";
                        std::string end = "B";

                        std::vector<std::string> path = g.CityGraph::findShortestPath(start, end);

                        if (!path.empty()) {
                            std::cout << "O melhor trajeto entre " << start << " e " << end << " é:\n";
                            for (const auto& city : path) {
                                std::cout << city << " ";
                            }
                            std::cout << std::endl;
                        } else {
                            std::cout << "Não existe trajeto entre " << start << " e " << end << std::endl;
                        }
                    break;
                }
            case 5:
                {
                    int tripId;
                    std::string originCity;
                    std::string destinationCity;
                    std::string transportName;

                    std::cout << "Digite o id da viagem: ";
                    std::cin >> tripId;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    Trip* possibleTrip = findTripById(db, tripId);
                    if(possibleTrip != nullptr){
                        std::cout << "Viagem com o id " << tripId << " já existe." << std::endl;
                        break;
                    }

                    std::cout << "Digite a cidade de origem: ";
                    std::getline(std::cin, originCity);
                    City* possibleOriginCity = findCityByName(db, originCity);
                    if(possibleOriginCity == nullptr){
                        std::cout << "Cidade " << originCity << " não existe." << std::endl;
                        break;
                    }

                    std::cout << "Digite a cidade de destino: ";
                    std::getline(std::cin, destinationCity);
                    City* possibleDestinationCity = findCityByName(db, destinationCity);
                    if(possibleDestinationCity == nullptr){
                        std::cout << "Cidade " << destinationCity << " não existe." << std::endl;
                        break;
                    }

                    std::cout << "Digite o nome do transporte: ";
                    std::getline(std::cin, transportName);
                    Transport* possibleTransport = findTransportByName(db, transportName);
                    if(possibleTransport == nullptr){
                        std::cout << "Transporte " << transportName << " não existe." << std::endl;
                        break;
                    }

                    if(!(addTripInTrips(db, tripId, transportName, originCity, destinationCity))){
                        break;
                    }

                    int opt = 1;
                    while(opt!=0) {
                        std::cout << "0 - Se deseja parar de adicionar passageiros" << std::endl;
                        std::cout << "1 - Se deseja adicionar um passageiro" << std::endl;
                        std::cin >> opt;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        switch (opt)
                        {
                            case 0:
                            {
                                break;
                            }
                            case 1:
                            {
                                std::string passengerName;
                                std::cout << "Digite o nome do passageiro: ";
                                std::getline(std::cin, passengerName);
                                Passenger* passenger = findPassengerByName(db, passengerName);
                                if(passenger == nullptr){
                                    std::cout << "Passageiro " << passengerName << " não existe." << std::endl;
                                    break;
                                } else {
                                    if(addPassengerInTripDB(db, tripId, passenger)){
                                        std::cout << "Passageiro " << passengerName << " adicionado com sucesso." << std::endl;
                                        std::cout << "Pressione Enter para continuar...";
                                        getchar();
                                    }
                                    std::system("clear");
                                }
                                break;
                            }
                            default:
                                std::cout << "Opção inválida." << std::endl;
                                break;
                        }
                    }

                    /*verify if the trasnport is in the origin city
                    for this, the transport need to has a atribute indacting where it is*/

                    /*record the lef of the transport, for this
                    the trip class need to has a atribute indicating the hour left*/

                    /*record the arrival of the transport, for this
                    the trip class need to has a atribute indicating the hour arrival*/

                    //use the findShortestPath method to find the best route

                    //create a trip with the information above                  

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
