#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include "structs.h"
#include "gestao.h"

using namespace std;

void gestao() {

    int options;

    cout << "***** Bem vindo gestor *****\n";
    cout << "(1).Reparação Manual\n";
    cout << "(2).Atualizar tempo de reparação\n";
    cout << "(3).Adicionar Prioridade\n";
    cout << "(4).Remover Mecânico\n";
    cout << "(5).Gravar Oficina\n";
    cout << "(6).Carregar Oficina\n";
    cout << "(7).Imprimir Oficina\n";
    cout << "Selecione a sua opção:\n";
    cin >> options;

    switch (options)
    {
    case 1:

        //fazer um cout a pedir a marca e o modelo, depois comparar com os que tem na fila de espera e nas ets depois retirar de lá
        //mandar para o registo e acrescentar à faturção da ET

        break;

    case 2:

        //pedir tambem a marca e o modelo, pedir para quantos dias para atualizar e atualizar todos os que tem na fila de espera

        break;

    case 3:

        break;

    case 4:

        break;

    case 5:

        break;

    case 6:

        break;

    case 7:

        break;

    default:

        cout << "Não selecionou uma opção válida\n";

        break;
    }
}