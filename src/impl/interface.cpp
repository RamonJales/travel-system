#include <iostream>
#include "../include/interface.hpp"


void print_menu() {
    std::cout << "======================================" << std::endl;
    std::cout << "           MENU DE OPÇÕES             " << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "Selecione uma opção:" << std::endl;
    std::cout << "1. Cadastrar Cidade" << std::endl;
    std::cout << "2. Cadastrar Transporte" << std::endl;
    std::cout << "3. Cadastrar Rota" << std::endl;
    std::cout << "4. Cadastrar Passageiro" << std::endl;
    std::cout << "5. Cadastrar Viagem" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "======================================" << std::endl;
}
