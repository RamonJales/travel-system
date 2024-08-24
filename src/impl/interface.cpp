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
    std::cout << "7. Listar todos os transportes" << std::endl;
    std::cout << "8. Listar todas as pessoas" << std::endl;
    std::cout << "9. Listar as cidades" << std::endl;
    std::cout << "10. Listar as cidades mais frequentadas" << std::endl;
    std::cout << "11. Listar todas as viagens em andamento" << std::endl;
    std::cout << "12. Listar todas as viagens finalizadas" << std::endl;
    std::cout << "13. Deletar cidade por nome" << std::endl;
    std::cout << "14. Deletar transporte por nome" << std::endl;
    std::cout << "15. Deletar passageiro por nome" << std::endl;
    std::cout << "16. Deletar trajeto por nome da cidade de origem e destino" << std::endl;
    std::cout << "17. Listar todas as rotas" << std::endl;
    std::cout << "0. Sair" << std::endl;
    std::cout << "======================================" << std::endl;
}
