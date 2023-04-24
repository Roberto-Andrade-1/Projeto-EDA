#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "structs.h"
#include "inicializacao.h"
#include "gestao.h"

using namespace std;

int main() {

    srand(time(NULL));

    bool ficheiros = true;
    bool sair = false;
    char escolha;
    int numeroPalavrasMarcas = 0;
    int numeroPalavrasModelos = 0;
    int numCarros = 0;
    int numCarrosTotal = 0;
    int numEstacoes = 0;
    int numET = rand() % 6 + 3;

    string* marcas = lerFicheiro("marcas.txt", numeroPalavrasMarcas);
    string* modelos = lerFicheiro("modelos.txt", numeroPalavrasModelos);

    carro* carros = new carro[200];

    estacoes* estacao = new estacoes[8];

    //usar uma variavel numCiclos para saber quantos tem e bloquear funções

    while (ficheiros)
    {
        cout << "Pretende inserir dados de ET's e carros guardados em ficheiros? (s/n)\n";
        cin >> escolha;

        switch (escolha)
        {
        case 's':
            /* code */

            ficheiros = false;

            break;

        case 'n':

            ficheiros = false;

            primeirosCarros(carros, marcas, modelos, numeroPalavrasMarcas, numeroPalavrasModelos, numCarros, numCarrosTotal);

            estacaoTrabalho(estacao, numET, numEstacoes, numeroPalavrasMarcas, marcas);

            printETs(estacao, numEstacoes);

            printCars(carros, numCarros);

            break;

        default:

            cout << "Escolha uma das opções, s ou n\n";

            break;
        }
    }
    while (!sair) {
        char opcao;

        cout << "Dia (s)eguinte ********* (g)estão\n"
            << "       (e)scapar às contas\n"
            << "Selecione a sua opção:\n";
        cin >> opcao;

        switch (opcao)
        {
        case 's':

            adicionaCarroET(carros, numEstacoes, numCarros, estacao);

            criarCarro(carros, numCarros, numCarrosTotal, numeroPalavrasMarcas, numeroPalavrasModelos, estacao, numEstacoes, marcas, modelos);

            adicionaDias(estacao, numEstacoes);

            printETs(estacao, numEstacoes);

            printCars(carros, numCarros);

            break;

        case 'g':

            gestao();

            break;

        case 'e':

            sair = true;
            delete[] marcas;
            delete[] modelos;
            break;

        default:

            cout << "Não selecionou uma opção valida\n";

            break;
        }
    }
    return 0;
}