#include <iostream>
#include "../include/interface.hpp"


void print_menu() {
    std::cout << "======================================" << std::endl;
    std::cout << "           MENU DE OPÇÕES             " << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "1. Cadastrar Cidade" << std::endl;
    std::cout << "2. Cadastrar Transporte" << std::endl;
    std::cout << "3. Cadastrar Passageiro" << std::endl;
    std::cout << "4. Cadastrar Trajeto" << std::endl;
    std::cout << "5. Iniciar viagem" << std::endl;
    std::cout << "6. Avançar horas" << std::endl;
    std::cout << "7. Relatar todas as viagens em andamento" << std::endl;
    std::cout << "8. Relatar todas as pessoas" << std::endl;
    std::cout << "9. Relatar todos os transportes" << std::endl;
    std::cout << "10. Relatar as cidades mais frequentadas" << std::endl;
    std::cout << "11. Relatar as cidades" << std::endl;
    std::cout << "12. Relatar todas as viagens finalizadas" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "======================================" << std::endl;
}
