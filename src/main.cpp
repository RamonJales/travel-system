#include <iostream>
#include "include/enums/RouteTypeEnum.hpp"
#include "include/interface.hpp"
#include "include/City.hpp"
#include "include/Passenger.hpp"
#include "include/Route.hpp"
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
            }
            case 2:
                {
                    std::cout << "Opção 2" << std::endl;
                }
            case 3:
                {
                    std::cout << "Opção 3" << std::endl;
                }
            case 4:
                {
                    std::cout << "Opção 4" << std::endl;
                }
            default:
                std::cout << "Escolha inválida. Por favor, tente novamente." << std::endl;
                break;
        }
        std::cout << "Pressione Enter para continuar...";
        getchar();
    } while (option != 0);

    return 0;
}
