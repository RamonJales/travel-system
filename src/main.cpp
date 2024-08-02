#include <iostream>
#include "include/enums/RouteTypeEnum.hpp"
#include "include/interface.hpp"
#include "include/City.hpp"
#include "include/Controller.hpp"
#include "include/Passenger.hpp"
#include "include/Route.hpp"
#include "include/Transport.hpp"
#include "include/Trip.hpp"

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
    if (sqlite3_open("example.db", &db)) {
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
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard invalid input
            std::cout << "Entrada inválida. Digite um número: ";
        }
        getchar();


        switch (option) {
            case 1:
            {
                std::cout << "Opção 1" << std::endl;
                break;
            }
            case 2:
                {
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
