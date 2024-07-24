# travel-system
Projeto da disciplina de Linguagens de Programação I. Um sistema de viagens.

## Requisitos:
- C++
- Cmake

## Como compilar, executar e testar o projeto:
- Primeiramente, instale a biblioteca googletest para os testes de software: 
    ```bash
    git clone https://github.com/google/googletest.git
    ```
### Compilar:
- Na pasta principal do projeto rode o comando:
    ```bash
    cmake -B build
    cmake --build build
    ```
  - Será criado um diretório chamado `build`.
### Executar:
- No diretório `build`, execute o comando `make` e, após isso, execute o programa:
    ```bash
    cd build
    make
    ./project
    ```

### Testar:
- Após ter compilado o projeto(ter usado o comando `make` também), no diretório `build`, vá para o diretório `test` e execute binário.
```bash
    cd test
    ./tests-project
    ```
