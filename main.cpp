#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>


using namespace std;

string *lerFicheiro(const string& nomeFicheiro, int &numeroPalavras) {
    ifstream ficheiro(nomeFicheiro);
    string *palavras = nullptr;
    string linha;
    numeroPalavras = 0;

    while (getline(ficheiro, linha)) {
        istringstream linhaStream(linha);
        string palavra;
        while (linhaStream >> palavra) {
            string *temp = new string[numeroPalavras + 1];
            for (int i = 0; i < numeroPalavras; i++) {
                temp[i] = palavras[i];
            }
            temp[numeroPalavras] = palavra;
            delete[] palavras;
            palavras = temp;
            numeroPalavras++;
        }
    }

    return palavras;
}

string escolhePalavraRandom(const string *palavras, int numeroPalavras) {
    int randomIndex = rand() % numeroPalavras;
    return palavras[randomIndex];
}

void ciclo(){



}

void gestao(){

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
        
        break;

    case 2:

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

int main(){

    bool ficheiros = true;
    bool sair = false;
    char escolha;
    int numeroPalavras = 0;
    string fila [200];

    srand (time(NULL));

    string *marcas = lerFicheiro("marcas.txt", numeroPalavras);
    string randomPalavra = escolhePalavraRandom(marcas, numeroPalavras);
    string *modelos = lerFicheiro("modelos.txt", numeroPalavras);
    string modeloRandom = escolhePalavraRandom(modelos, numeroPalavras);

    delete[] marcas;
    delete[] modelos;

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

            break;
        
        default:

            cout << "Escolha uma das opções, s ou n\n";

            break;
        }
    }
    while(!sair){

        char opcao;

        cout << "Dia (s)eguinte ********* (g)estão\n";
        cout << "Selecione a sua opção:\n";
        cin >> opcao;

        switch (opcao)
        {
        case 's':

            ciclo();
            
            break;

        case 'g':

            gestao();

            break;

        case 'e':

            sair = true;

            break;
        
        default:

            cout << "Não selecionou uma opção valida\n";

            break;
        }
    }
    
return 0;
}