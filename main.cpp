#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "carros.h"


using namespace std;

//função que lê os ficheiros, recebe o nome do ficheiro e o numero de palavras lidas

string *lerFicheiro(const string& nomeFicheiro, int &numeroPalavras) {
    ifstream ficheiro(nomeFicheiro); // dá um nome ao ficheiro aberto
    string *palavras = nullptr; 
    string linha;
    numeroPalavras = 0;

    while (getline(ficheiro, linha)) { //equanto tiver linhas faz estas operações
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

void ciclo(carro carros[], int &numCarros, int &numeroPalavras, int &numCiclos, estacoes estacao[], int &numEstacoes){

    int maxCarros = 200;

    if(numCarros >= maxCarros){
        return;
    }

    if(numCiclos < 1){
        for (int i = 0; i < 10; i++) 
        {
            string *marcas = lerFicheiro("marcas.txt", numeroPalavras);
            string marcaRandom = escolhePalavraRandom(marcas, numeroPalavras);
            string *modelos = lerFicheiro("modelos.txt", numeroPalavras);
            string modeloRandom = escolhePalavraRandom(modelos, numeroPalavras);

            delete[] marcas;
            delete[] modelos;

            carro novoCarro = {numCarros + 1, rand() % 4 + 2, 0, rand() % 100 < 5, 0, marcaRandom, modeloRandom};
            carros[numCarros] = novoCarro;
            numCarros++;
        }
    }else{
        int numNovoCarro = 0;

        while (numNovoCarro < 10) 
        {
            string *marcas = lerFicheiro("marcas.txt", numeroPalavras);
            string marcaRandom = escolhePalavraRandom(marcas, numeroPalavras);
            string *modelos = lerFicheiro("modelos.txt", numeroPalavras);
            string modeloRandom = escolhePalavraRandom(modelos, numeroPalavras);

            delete[] marcas;
            delete[] modelos;

            for(int i = 0; i < numEstacoes; i++){
                if(estacao[i].marcaEspecializada == marcaRandom){
                    carro novoCarro = {numCarros + 1, rand() % 4 + 2, 0, rand() % 100 < 5, 0,marcaRandom, modeloRandom};
                    carros[numCarros] = novoCarro;
                    numCarros++;
                    numNovoCarro++;
                }
            }
        }
        for (int i = 0; i < numEstacoes; i++)
        {
            if (estacao[i].carroNaEt->idCarro == carros[i].idCarro){ //se tiver dentro da et
                carros[i].dias++;
            }
            // if(estacao[i].carroNaEt->dias >= estacao[i].carroNaEt->tempoMax){
            //     remove(estacao[i].carroNaEt);
            // }
        }
        
    }
}

void adicionaCarroET(carro carros[], int &numEstacoes, int &numCarros, estacoes estacao[])
{

    int carroAdicionado = 0;
    int naoAdicionados = 0;
    int estacaoAtual = 0;
    bool sair = false;

    carro* carrosNaoAdicionados = new carro[numCarros];

    do{
        for (int i = 0; i < numEstacoes; i++){
    
            if(estacao[i].marcaEspecializada == carros[i].marca){ 
                if(estacao[i].quantidadeCarros < estacao[i].capacidade){
                    
                    estacao[i].carroNaEt[estacao[i].quantidadeCarros++] = carros[estacaoAtual++];
                    carroAdicionado++;
                    break;
                }
            }
            if(i == (numEstacoes - 1)){
                carrosNaoAdicionados[naoAdicionados++] = carros[estacaoAtual];
            }
            if(estacaoAtual == numCarros){
                sair = true;
                break;
            }
        }
    }while (carroAdicionado != 8 && !sair);
           
    for (int i = estacaoAtual; i < numCarros; i++){
        carrosNaoAdicionados[naoAdicionados++] = carros[i];
    }

    delete[] carros;
    carros = carrosNaoAdicionados;
    numCarros -= carroAdicionado;
}
 
void estacaoTrabalho(estacoes estacao[], int &numET, int &numEstacoes, int &numeroPalavras, int &numCiclos){  

    string nome;
    getline(cin,nome);

    // fazer um if como no ciclo para so criar as variaveis uma vez e armazená-las em vez de criar novas.

    if (numCiclos < 1){
        for (int i = 0; i < numET; i++)
        {
            string *marcas = lerFicheiro("marcas.txt", numeroPalavras);
            string marcaRandom = escolhePalavraRandom(marcas, numeroPalavras);

            delete[] marcas;

            cout << "Dá um nome ao mecânico " << i + 1 << ": \n";
            getline(cin,nome);

            int capacidade = rand() % 4 + 2;

            estacoes novaET = {numEstacoes + 1, capacidade, 0, nome, marcaRandom, new carro[capacidade], new registo[1]};

            estacao[numEstacoes] = novaET;
            numEstacoes++;
        }
    }
}

void printCars(carro carros[], int comprimento) {

    cout << "\nLista de espera: \n";
    for (int i = 0; i < comprimento; i++) 
    {
        cout << "Carro ID: " << carros[i].idCarro << " | "
             << "Marca: " << carros[i].marca << " | "
             << "Modelo: " << carros[i].modelo << " | " 
             << "Prioridade: " << carros[i].prioritario << " | "
             << "Tempo de Reparacao: " << carros[i].tempoMax << " | "
             << "Dias na oficina: " << carros[i].dias << "\n";
    }
    cout << "\n\n";
}

void printETs(estacoes estacao[], int comprimento){

    for (int i = 0; i < comprimento; i++)
    {
        cout << "\nEstação ";
        cout << "ID: " << estacao[i].idET << " | "
             << "Mecânico: " << estacao[i].mecanico << " | "
             << "Capacidade: " << estacao[i].capacidade << " | "
             << "Carros: " << estacao[i].quantidadeCarros << " | "
             << "Marca: " << estacao[i].marcaEspecializada << " | "
             << "Total Faturação: \n";

        for(int j = 0; j < estacao[i].quantidadeCarros; j++){
            cout <<"Carro: ID: " << estacao[i].carroNaEt[j].idCarro << " | "
                 << estacao[i].carroNaEt[j].marca << "-" << estacao[i].carroNaEt[j].modelo
                 << " | Prioritário: " << estacao[i].carroNaEt[j].prioritario << " | Tempo Reparação: " 
                 << estacao[i].carroNaEt[j].tempoMax << " | Dias na ET: " << estacao[i].carroNaEt[j].dias << "\n";  
        }
        cout << "-------------------------- \n";
    }
}

int main(){

    srand (time(NULL));

    bool ficheiros = true;
    bool sair = false;
    char escolha;
    int numeroPalavras = 0;
    int numCarros = 0;
    int numEstacoes = 0;
    int numET = rand () % 6 + 3;
    int numCiclos = 0;

    carro carros[200];

    estacoes estacao[8];

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

            break;
        
        default:

            cout << "Escolha uma das opções, s ou n\n";

            break;
        }
    }
    while(!sair){

        if(numCiclos == 0){
            estacaoTrabalho(estacao, numET, numEstacoes, numeroPalavras, numCiclos);

            ciclo(carros, numCarros, numeroPalavras, numCiclos, estacao, numEstacoes);
            
            printETs(estacao, numEstacoes);

            printCars(carros, numCarros);

            numCiclos++;
        }

        char opcao;

        cout << "Dia (s)eguinte ********* (g)estão\n"
             << "       (e)scapar às contas\n"
             << "Selecione a sua opção:\n";
        cin >> opcao;

        switch (opcao)
        {
        case 's':

            estacaoTrabalho(estacao, numET, numEstacoes, numeroPalavras, numCiclos);

            ciclo(carros, numCarros, numeroPalavras, numCiclos, estacao, numEstacoes);

            adicionaCarroET(carros, numEstacoes, numCarros, estacao);

            printETs(estacao, numEstacoes);

            printCars(carros, numCarros);

            numCiclos++;
            
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
    delete[] carros;
    delete[] estacao;
return 0;
}