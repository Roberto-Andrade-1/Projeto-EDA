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

//função que lê os ficheiros, recebe o nome do ficheiro e o numero de palavras lidas

string* lerFicheiro(const string& nomeFicheiro, int& numeroPalavras) {
    ifstream ficheiro(nomeFicheiro); // dá um nome ao ficheiro aberto
    string* palavras = nullptr;
    string linha;
    numeroPalavras = 0;

    while (getline(ficheiro, linha)) { //equanto tiver linhas faz estas operações
        istringstream linhaStream(linha);
        string palavra;
        while (linhaStream >> palavra) {
            string* temp = new string[numeroPalavras + 1];
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

string escolhePalavraRandom(const string* palavras, int numeroPalavras) {
    int randomIndex = rand() % numeroPalavras;
    return palavras[randomIndex];
}

void removeDaET(estacoes*& estacao, carro*& carrosET, int capacidadeET, int quantidadeET, int indiceCarro) {
    // Allocate a new array with one less element than the current one
    carro* novaLista = new carro[capacidadeET-1];
    // Initialize a variable to keep track of the new quantity of cars in the station
    int novaQuantidadeET = 0;
    // Iterate over the current cars in the station
    for(int i = 0; i < quantidadeET; i++){
        // If the car at the current index is not the one to be removed, add it to the new array
        if(i != indiceCarro) {
            novaLista[novaQuantidadeET] = carrosET[i];
            // Increment the counter for the new quantity of cars in the station
            novaQuantidadeET++;
        }
    }
    // Update the car array pointer in the station to point to the new array
    carrosET = novaLista;
    // Update the number of cars in the station in the station struct
    estacao->quantidadeCarros = novaQuantidadeET;
    // Update the car array in the station struct to point to the new car array
    estacao->carroNaEt = carrosET;
}

void adicionaDias(estacoes*& estacao,int& numEstacoes){
    // Iterate over all the stations
    for (int i = 0; i < numEstacoes; i++)
    {
        // Iterate over all the cars in the current station
        for(int j = 0; j < estacao[i].quantidadeCarros; j++){ 
            // Add one day to the repair time of the current car
            estacao[i].carroNaEt[j].dias++;
            // If the repair time of the current car has reached the maximum allowed time
            if(estacao[i].carroNaEt[j].dias == estacao[i].carroNaEt[j].tempoMax){
                // Remove the current car from the station
                removeDaET(estacao, estacao[i].carroNaEt, estacao[i].capacidade, estacao[i].quantidadeCarros, j);
            }
        }
    }
}

void inserirNaListaEspera(carro*& carros, const carro& novoCarro, int numCarros) {
    if(novoCarro.prioritario){
        int index = 0;
        while (carros[index].idCarro != -1 && carros[index].prioritario && novoCarro.prioritario) {
            index++;
        }
        for (int i = numCarros; i > index; i--) {
            carros[i] = carros[i - 1];
        }
        carros[index] = novoCarro;
    }else{
        carros[numCarros]=novoCarro;
    }
}

void criarCarro(carro*& carros, int& numCarros, int& numCarrosTotal, int& numeroPalavrasMarcas, int& numeroPalavrasModelos, estacoes*& estacao, int& numEstacoes, string marcas[], string modelos[]) {
    
    if (numCarros >= 200) {
        return;
    }

    int numNovoCarro = 0;

    while (numNovoCarro < 10)
    {
        string marcaRandom = escolhePalavraRandom(marcas, numeroPalavrasMarcas);
        string modeloRandom = escolhePalavraRandom(modelos, numeroPalavrasModelos);

        for (int i = 0; i < numEstacoes; i++) {
            if (estacao[i].marcaEspecializada == marcaRandom) {
                carro novoCarro = { numCarrosTotal + 1, rand() % 4 + 2, 0, rand() % 100 < 5, 0, marcaRandom, modeloRandom };
                inserirNaListaEspera(carros, novoCarro, numCarros);
                numNovoCarro++;
                numCarros++;
                numCarrosTotal++;
            }
        }
    }
}

void removeDaListaEspera(carro*& carros, int& numCarros, int j) {
    carro* novaLista = new carro[200];//nova lista para adicionar todos os carros menos o que vai ser retirado da lista de espera
    numCarros--; //atualiza o numero de carros atual na lista "carros", reduz conforme os carros que forem adicionados nas ETS
    for(int i = 0; i < j; i++){ //loop para percorrer todos os carros ate chegar ao que vai ser retirado
        novaLista[i] = carros[i]; //adiciona esse carro à nova lista
    }
    for(int k = j + 1 ;k <= numCarros; k++){ //loop para percorrer todos os carros depois do carro a ser removido e consegue chegar ao ultimo carro da lista devido ao <=
        novaLista[k-1] = carros[k]; // adiciona o carro à nova lista 
    }
    carros = novaLista; // iguala a lista antiga a esta nova criada
}

void adicionaCarroET(carro*& carros, int numEstacoes, int& numCarros, estacoes*& estacao) {
    int carroAdicionado = 0;
    int a = numCarros;
    for (int j = 0; j < a; j++) {
        for (int i = 0; i < numEstacoes; i++) {
            if (estacao[i].marcaEspecializada == carros[j].marca && estacao[i].quantidadeCarros < estacao[i].capacidade && carroAdicionado < 8) {
                estacao[i].carroNaEt[estacao[i].quantidadeCarros++] = carros[j];
                removeDaListaEspera(carros, numCarros, j);
                carroAdicionado++;
                break;
            }
        }
    }
}

void primeirosCarros(carro*& carros, string marcas[], string modelos[], int& numeroPalavrasMarcas, int& numeroPalavrasModelos, int& numCarros, int& numCarrosTotal){
    for (int i = 0; i < 10; i++)
    {
        string marcaRandom = escolhePalavraRandom(marcas, numeroPalavrasMarcas);
        string modeloRandom = escolhePalavraRandom(modelos, numeroPalavrasModelos);

        carro novoCarro = { numCarrosTotal + 1, rand() % 4 + 2, 0, rand() % 100 < 5, 0, marcaRandom, modeloRandom };
        carros[numCarros] = novoCarro;
        numCarros++;
        numCarrosTotal++;
    }
}

void estacaoTrabalho(estacoes*& estacao, int& numET, int& numEstacoes, int& numeroPalavrasMarcas, string marcas[]) {

    string nome;
    getline(cin, nome);

    for (int i = 0; i < numET; i++)
    {
        string marcaRandom = escolhePalavraRandom(marcas, numeroPalavrasMarcas);

        cout << "Dá um nome ao mecânico " << i + 1 << ": \n";
        getline(cin, nome);

        int capacidade = rand() % 4 + 2;

        estacoes novaET = { numEstacoes + 1, capacidade, 0, nome, marcaRandom, new carro[capacidade], new registoDaET[1] };

        estacao[numEstacoes] = novaET;
        numEstacoes++;
    }
}

void printCars(carro*& carros, int comprimento) {

    //usar a cena dos ciclos para variar a lista de carros usados

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

void printETs(estacoes*& estacao, int comprimento) {

    for (int i = 0; i < comprimento; i++)
    {
        cout << "\nEstação ";
        cout << "ID: " << estacao[i].idET << " | "
            << "Mecânico: " << estacao[i].mecanico << " | "
            << "Capacidade: " << estacao[i].capacidade << " | "
            << "Carros: " << estacao[i].quantidadeCarros << " | "
            << "Marca: " << estacao[i].marcaEspecializada << " | "
            << "Total Faturação: \n";

        for (int j = 0; j < estacao[i].quantidadeCarros; j++) {
            cout << "Carro: ID: " << estacao[i].carroNaEt[j].idCarro << " | "
                << estacao[i].carroNaEt[j].marca << "-" << estacao[i].carroNaEt[j].modelo
                << " | Prioritário: " << estacao[i].carroNaEt[j].prioritario << " | Tempo Reparação: "
                << estacao[i].carroNaEt[j].tempoMax << " | Dias na ET: " << estacao[i].carroNaEt[j].dias << "\n";
        }
        cout << "-------------------------- \n";
    }
}