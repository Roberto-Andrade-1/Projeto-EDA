#include <string>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "structs.h"
#include "inicializacao.h"
#include "gestao.h"

using namespace std;

int main() {

    srand(time(NULL));
    locale::global(locale(""));

    int numeroPalavrasMarcas = 0;
    int numeroPalavrasModelos = 0;

    string* marcas = lerFicheiro("marcas.txt", numeroPalavrasMarcas);
    string* modelos = lerFicheiro("modelos.txt", numeroPalavrasModelos);

    carro* carros = new carro[200];

    estacoes* estacao = new estacoes[8];

    menu(numeroPalavrasMarcas, numeroPalavrasModelos, marcas, modelos, carros, estacao);

    delete[] marcas;
    delete[] modelos;
    delete[] carros;
    delete[] estacao;

    return 0;
}