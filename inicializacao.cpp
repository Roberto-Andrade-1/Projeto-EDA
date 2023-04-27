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

//método para ler os ficheiros
string* lerFicheiro(const string& nomeFicheiro, int& numeroPalavras) {
    ifstream ficheiro(nomeFicheiro); // dá um nome ao ficheiro aberto
    string* palavras = nullptr; //um apontador a null para obter as palavras
    string linha; //variavel para as linhas
    numeroPalavras = 0; //variavel a zero do numero de palavras lidas

    while (getline(ficheiro, linha)) { //equanto tiver linhas faz estas operações
        istringstream linhaStream(linha); //se for uma linha 
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

//metodo para escolher uma palavra random
string escolhePalavraRandom(const string* palavras, int numeroPalavras) {
    int randomIndex = rand() % numeroPalavras; //obtem o resto da divisao do rand a dividir pelo número de palavras do ficheiro
    return palavras[randomIndex]; //faz o return da palavra nesse index 
}

//método para remover o carro da estação
void removeCarros(estacoes*& estacao, int& numEstacoes){
    for (int i = 0; i < numEstacoes; i++) { //percorre todas as estações

        int quantidadeCarrosNova = 0; //variavel para atualizar a quantidade de carros atualizada

        carro* novaLista = new carro[estacao[i].capacidade]; //criar uma nova lista para adicionar os carros que não vão ser retirados

        for (int j = 0; j < estacao[i].quantidadeCarros; j++) { //loop de todos os carros que estão nessa estação

            estacao[i].carroNaEt[j].dias++; //incrementa os dias desse carro

            if ((estacao[i].carroNaEt[j].dias == estacao[i].carroNaEt[j].tempoMax) || (rand() % 20 <= 2)){ //se os dias chegarem ao maximo ou se a probabilidade for igual a 15%
                estacao[i].faturacao += (estacao[i].carroNaEt[i].dias * 50); //acrescenta à faturação o valor da reparação 
                cout << "\nO carro com ID " << estacao[i].carroNaEt[j].idCarro << " foi removido da ET " << estacao[i].idET << "\n"; //visualização do carro que saiu da ET
            }
            else {
                novaLista[quantidadeCarrosNova] = estacao[i].carroNaEt[j]; //na nova lista adiciona na posição determinada o carro que não foi retirado
                quantidadeCarrosNova++; //incrementa para adicionar carros em posições diferentes
            }
        }
        delete[] estacao[i].carroNaEt; //liberta a memoria do array antigo
        estacao[i].quantidadeCarros = quantidadeCarrosNova; //atualiza a quantidade de carros 
        estacao[i].carroNaEt = novaLista; //adiciona a nova lista criada à lista da estação
    }
}

//método para inserir na lista de espera
void inserirNaListaEspera(carro*& carros, const carro& novoCarro, int numCarros) {
    carros[numCarros] = novoCarro;
    int h;
    for (h = 1; h < numCarros; h = 3 * h + 1);
    do {
        h /= 3;
        for (int i = h; i < numCarros; ++i) {
            int j;
            carro v = carros[i];
            for (j = i - h; j >= 0 && (carros[j].prioritario < v.prioritario || (carros[j].prioritario == v.prioritario && carros[j].idCarro > v.idCarro)); j -= h)
                carros[j + h] = carros[j];
            carros[j + h] = v;
        }
    } while (h > 1);
}

//método para criar os carros quando o (s)eguinte é introduzido
void criarCarro(carro*& carros, int& numCarros, int& numCarrosTotal, int& numeroPalavrasMarcas, int& numeroPalavrasModelos, estacoes*& estacao, int& numEstacoes, string marcas[], string modelos[]) {

    int numNovoCarro = 0; //variavel para contar os novos carros

    while (numNovoCarro < 10) //loop para contar a quantidade de carros gerada
    {
        string marcaRandom = escolhePalavraRandom(marcas, numeroPalavrasMarcas); // vai buscar uma marca random do ficheiro
        string modeloRandom = escolhePalavraRandom(modelos, numeroPalavrasModelos); // vai buscar um modelo random do ficheiro

        for (int i = 0; i < numEstacoes; i++) { //faz loop por todas as estações
            if (estacao[i].marcaEspecializada == marcaRandom) { //se a marca random que foi tirada do ficheiro for igual à da marca de uma das ETs entra na condição
                carro novoCarro = { numCarrosTotal + 1, rand() % 4 + 2, 0, rand() % 100 < 5, marcaRandom, modeloRandom }; //cria um carro novo, dá um id novo com a variavel numCarrosTotal + 1 porque o id nao comeca a 0, tempo maximo random entre 2 e 5, dias na ET a 0, uma marca e um modelo
                inserirNaListaEspera(carros, novoCarro, numCarros); //invoca a função inserirNaListaEspera que põe por ordem de prioridade os carros
                numNovoCarro++; //incrementa a variavel que controla a quantidade de carros que vão ser geridos
                numCarros++; //incrementa a quantidade de carros
                numCarrosTotal++; //incrementa a quantidade de carros total
            }
        }
    }
}

//método para remover o carro da lista de espera
void removeDaListaEspera(carro*& carros, int& numCarros, int j) {
    carro* novaLista = new carro[200];//nova lista para adicionar todos os carros menos o que vai ser retirado da lista de espera
    numCarros--; //atualiza o numero de carros atual na lista "carros", reduz conforme os carros que forem adicionados nas ETS
    for (int i = 0; i < j; i++) { //loop para percorrer todos os carros ate chegar ao que vai ser retirado
        novaLista[i] = carros[i]; //adiciona esse carro à nova lista
    }
    for (int k = j + 1;k <= numCarros; k++) { //loop para percorrer todos os carros depois do carro a ser removido e consegue chegar ao ultimo carro da lista devido ao <=
        novaLista[k - 1] = carros[k]; // adiciona o carro à nova lista 
    }
    delete[] carros; //libertar a memoria do array
    carros = novaLista; // iguala a lista antiga a esta nova criada
}

//método para adicionar carros na ET
void adicionaCarroET(carro*& carros, int& numEstacoes, int& numCarros, estacoes*& estacao) { 
    int carroAdicionado = 0; //cria uma variavel para contar a quantidade de carros adicionados
    for (int j = 0; j < numCarros; j++) { //faz loop pelos carros todos
        for (int i = 0; i < numEstacoes; i++) { //faz loop pelas estacoes todas
            //compara a marca a ver se é a mesma, e se a quantidade de carros é menor que a capacidade da ET e se foram adicionados menos de 8 carros
            if (estacao[i].marcaEspecializada == carros[j].marca && estacao[i].quantidadeCarros < estacao[i].capacidade && carroAdicionado < 8) {
                estacao[i].carroNaEt[estacao[i].quantidadeCarros++] = carros[j]; //adiciona à estacao na proxima posição disponivel o carro
                removeDaListaEspera(carros, numCarros, j); //invoca a função que remove o carro da lista de espera
                carroAdicionado++; //incrementa a quantidade de carros que foram adicionados à ET 
                break; //faz break para não fazer uma cópia do carro caso haja duas ou + ETs com a mesma marca
            }
        }
    }
}

//método para criar os 10 primeiros carros totalmente aleatorios
void primeirosCarros(carro*& carros, string marcas[], string modelos[], int& numeroPalavrasMarcas, int& numeroPalavrasModelos, int& numCarros, int& numCarrosTotal) {
    for (int i = 0; i < 10; i++) //faz um loop de 10 iterações
    {
        string marcaRandom = escolhePalavraRandom(marcas, numeroPalavrasMarcas); //seleciona uma marca random do ficheiro
        string modeloRandom = escolhePalavraRandom(modelos, numeroPalavrasModelos);//seleciona um modelo random do ficheiro

        carro novoCarro = { numCarrosTotal + 1, rand() % 4 + 2, 0, rand() % 100 < 5, marcaRandom, modeloRandom }; //cria um novo carro, o id ve a variavel numCarrosTotal e adiciona 1 para não comecar a 0, da um tempo maximo de arranjo, 0 de dias na ET, e a possibilidade de ser prioritario, marca e modelo
        inserirNaListaEspera(carros, novoCarro, numCarros); //invoca a função que ordena a lista de espera
        numCarros++; //atualiza a variavel numCarros
        numCarrosTotal++; //atualiza a variavel numCarrosTotal
    }
}

//método que cria as estações de trabalho
void estacaoTrabalho(estacoes*& estacao, int& numET, int& numEstacoes, int& numeroPalavrasMarcas, string marcas[]){
    string nome; //variavel para guardar o nome do mecanico
    getline(cin, nome); //recebe o input do usuario

    for (int i = 0; i < numET; i++) //faz loop pela quantidade de ET que foram criadas o main
    {
        string marcaRandom = escolhePalavraRandom(marcas, numeroPalavrasMarcas); //recebe uma marca random do ficheiro

        cout << "Dê um nome ao mecânico " << i + 1 << ": \n"; //põe na consola a mensagem para dar um nome
        getline(cin, nome); //recebe o input do usuario

        int capacidade = rand() % 4 + 2; //gera um número random da capacidade da ET

        estacoes novaET = { numEstacoes + 1, capacidade, 0, 0, nome, marcaRandom, new carro[capacidade] }; //cria a estacao com id que comeca a um
        //da a sua capacidade, a quantidade de carros, a faturação, o nome do mecanico, a marca
        estacao[numEstacoes] = novaET; //adiciona essa estação ao array
        numEstacoes++; //aumenta a variavel do numEstacoes
    }
}

//método que faz o print dos carros 
void printCars(carro*& carros, int comprimento) {
    cout << "\nLista de espera: \n"; //faz output na consola desta mensagem
    for (int i = 0; i < comprimento; i++) //percorre o comprimento que no caso é o numCarros que existe na fila
    {
        //faz o output dos dados necessários
        cout << "Carro ID: " << carros[i].idCarro << " | " 
            << "Marca: " << carros[i].marca << " | "
            << "Modelo: " << carros[i].modelo << " | "
            << "Prioridade: " << carros[i].prioritario << " | "
            << "Tempo de Reparacao: " << carros[i].tempoMax << " | "
            << "Dias na oficina: " << carros[i].dias << "\n";
    }
    cout << "\n";
}

//método que faz o print das ETs
void printETs(estacoes*& estacao, int comprimento) {

    for (int i = 0; i < comprimento; i++) //percorre o comprimento da quantidade de ETs
    {
        //faz o output necessário para ter as informações pedidas
        cout << "\nEstação ";
        cout << "ID: " << estacao[i].idET << " | "
            << "Mecânico: " << estacao[i].mecanico << " | "
            << "Capacidade: " << estacao[i].capacidade << " | "
            << "Carros: " << estacao[i].quantidadeCarros << " | "
            << "Marca: " << estacao[i].marcaEspecializada << " | "
            << "Total Faturação: "<< estacao[i].faturacao << "$\n";

        //percorre o array interno da struct estacao para fazer output dos carros que estão lá dentro
        for (int j = 0; j < estacao[i].quantidadeCarros; j++) {
            cout << "Carro ID: " << estacao[i].carroNaEt[j].idCarro << " | "
                << estacao[i].carroNaEt[j].marca << "-" << estacao[i].carroNaEt[j].modelo
                << " | Prioridade: " << estacao[i].carroNaEt[j].prioritario << " | Tempo de Reparação: "
                << estacao[i].carroNaEt[j].tempoMax << " | Dias na oficina: " << estacao[i].carroNaEt[j].dias << "\n";
        }
        cout << "-------------------------- \n";
    }
}

//método que faz o output inicial a pedir os ficheiros, e pede os inputs para fazer os ciclos ou a gestao
void menu(int& numeroPalavrasMarcas, int& numeroPalavrasModelos, string marcas[], string modelos[], carro*& carros, estacoes*& estacao) {
    
    char escolha;
    int numCarros = 0;
    int numCarrosTotal = 0;
    int numEstacoes = 0;
    int numET = rand() % 6 + 3;
    bool ficheiros = true;
    bool sair = false;

    while (ficheiros)
    {
        cout << "Pretende inserir dados de ET's e carros guardados em ficheiros? (s/n)\n";
        cin >> escolha;

        switch (escolha)
        {
        case 's':
            
            uploadEstacao(estacao, numEstacoes, numCarrosTotal);
            uploadFilaDeEspera(numCarros, carros, numCarrosTotal);
            printETs(estacao, numEstacoes);
            printCars(carros, numCarros);
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

        cout << "\n\nDia (s)eguinte ********* (g)estão\n"
            << "       (e)scapar às contas\n"
            << "Selecione a sua opção:\n";
        cin >> opcao;

        switch (opcao)
        {
        case 's':

            adicionaCarroET(carros, numEstacoes, numCarros, estacao);
            
            criarCarro(carros, numCarros, numCarrosTotal, numeroPalavrasMarcas, numeroPalavrasModelos, estacao, numEstacoes, marcas, modelos);

            removeCarros(estacao, numEstacoes);

            printETs(estacao, numEstacoes);

            printCars(carros, numCarros);

            break;

        case 'g':

            gestao(estacao, numEstacoes, marcas, numeroPalavrasMarcas, numCarros, carros, numCarrosTotal);

            break;

        case 'e':

            sair = true;
            break;

        default:

            cout << "Não selecionou uma opção valida\n";

            break;
        }
    }
}