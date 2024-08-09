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
           case 1: {
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
            } case 2: {
                    std::cout << "Opção 2" << std::endl;
                    break;
                }
            case 3:
                {
                    std::cout << "Opção 3" << std::endl;
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
                    std::string originCity;
                    std::string destinationCity;
                    std::string transportName;

                    std::cout << "Digite a cidade de origem: " << std::endl;
                    std::cin >> originCity;
                    //find the city in the database with the name


                    std::cout << "Digite a cidade de destino: " << std::endl;
                    std::cin >> destinationCity;
                    //find the city in the database with the name

                    std::cout << "Digite o nome do transporte: " << std::endl;
                    std::cin >> transportName;
                    //find the transport in the database with the name

                    int opt = 1;
                    while(opt!=0) {
                        std::cout << "0 - Se deseja parar de adicionar passageiros" << std::endl;
                        std::cout << "1 - Se deseja adicionar um passageiro" << std::endl;
                        std::cin >> opt;
                        if(opt == 1) {
                            std::string passengerName;
                            std::cout << "Digite o nome do passageiro: " << std::endl;
                            std::cin >> passengerName;
                            //find the passenger in the database with the name
                            //add the passenger to the list of passengers
                        }
                        //clear terminals
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
