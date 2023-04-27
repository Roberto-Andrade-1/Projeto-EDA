#include <iostream>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "structs.h"
#include "gestao.h"
#include "inicializacao.h"

using namespace std;

void reparacaoManual(estacoes*& estacao, int numEstacoes, int numCarros, carro*& carros) {

    string marcaCarro;
    string modeloCarro;

    getline(cin, marcaCarro);
    cout << "\nIntroduza a marca do carro a remover: ";
    getline(cin, marcaCarro);
    getline(cin, modeloCarro);
    cout << "\nIntroduza também o modelo desse carro: ";
    getline(cin, modeloCarro);

    for (int i = 0; i < numEstacoes; i++) {
        for (int j = 0; j < estacao[i].quantidadeCarros; j++) {
            if ((estacao[i].carroNaEt[j].marca == marcaCarro) && (estacao[i].carroNaEt[j].modelo == modeloCarro)) {
                estacao[i].faturacao += (estacao[i].carroNaEt[i].dias * 50);
                cout << "\nO carro com ID " << estacao[i].carroNaEt[j].idCarro << " foi removido da ET " << estacao[i].idET << "\n";
            }
            else {
                cout << "\nA marca ou modelo introduzido não existem presentes nas ETs\n";
            }
        }
    }
    printETs(estacao, numEstacoes);
    printCars(carros, numCarros);
}

void tempoDeReparacao(carro*& carros, int numCarros, int numEstacoes, estacoes*& estacao) {

    string marcaCarro;
    string modeloCarro;
    int tempoReparacao = 0;

    getline(cin, marcaCarro);
    cout << "Introduza a marca do carro: ";
    getline(cin,marcaCarro);

    getline(cin, modeloCarro);
    cout << "Introduza o modelo do carro: ";
    getline(cin, modeloCarro);

    cout << "\nIntroduza o tempo de reparação atualizado: ";
    cin >> tempoReparacao;

    for (int i = 0; i < numCarros; i++) {
        if((carros[i].marca == marcaCarro) && (carros[i].modelo == modeloCarro))
        {
            carros[i].tempoMax = tempoReparacao;
        }
        else {
            cout << "\nA marca ou modelo introduzido não existem na fila de espera\n";
        }
    }
    printETs(estacao, numEstacoes);
    printCars(carros, numCarros);
}

void adicionarPrioridade(carro*& carros, int numCarros, int numEstacoes, estacoes*& estacao) {

    int IDcarro = 0;

    cout << "\nIntroduza o ID do carro que quer alterar a prioridade: ";
    cin >> IDcarro;

    for (int i = 0; i < numCarros; i++) {
        if (carros[i].idCarro == IDcarro) {
            if (carros[i].prioritario == false) {
                carros[i].prioritario = true;
                inserirNaListaEspera(carros, carros[i], numCarros);
                break;
            }
            else {
                cout << "\nEste carro já é prioritário\n";
                break;
            }
        }
    }
    printETs(estacao, numEstacoes);
    printCars(carros, numCarros);
}

void removerTodosCarros(int numEstacoes, estacoes*& estacao, int indice) {
    for (int j = 0; j < estacao[indice].quantidadeCarros; j++) {
        estacao[indice].faturacao += (estacao[indice].carroNaEt->dias * 50); //acrescenta à faturação o valor da reparação 
        cout << "\nO carro com ID " << estacao[indice].carroNaEt[j].idCarro << " foi removido da ET " << estacao[indice].idET << "\n";
    }
}

void removerMecanico(estacoes*& estacao, int numEstacoes, string marcas[], int& numeroPalavrasMarcas, int numCarros, carro*& carros) {

    string nomeMecanico;
    getline(cin, nomeMecanico);

    cout << "Introduza o nome do mecânico a remover: ";
    getline(cin, nomeMecanico);

    estacoes novaEt;
    string novoMecanico;

    for (int i = 0; i < numEstacoes; i++) {
        if (estacao[i].mecanico == nomeMecanico) {
            //remover da et os carros e adicionar ao registo
            removerTodosCarros(numEstacoes, estacao, i);
            //pedir um novo nome para o mecânico a ser introduzido
            cout << "\nDê um nome ao mecânico: ";
            getline(cin, novoMecanico);
            cout << "\n";
            //criar a nova et
            string marcaRandom = escolhePalavraRandom(marcas, numeroPalavrasMarcas);
            int capacidade = rand() % 4 + 2;
            novaEt = {estacao[i].idET, capacidade, 0, 0, novoMecanico, marcaRandom, new carro[capacidade]};
            //substituir a antiga por esta nova
            estacao[i] = novaEt;
        }
    }
    printETs(estacao, numEstacoes);
    printCars(carros, numCarros);
}

//método que grava as oficinas assim como os carros dentro dela
void gravarEstacao(estacoes*& estacao, int numEstacoes) {

    ofstream oficinas("oficinas.txt"); //cria um ficheiro com o nome

    oficinas.clear(); //faz clear para limpar o ficheiro e não ficar guardado informações antigas

    if (oficinas.is_open()) { //verifica se consegue abrir o ficheiro para guardar a informação
        oficinas << "-\n";
        oficinas << numEstacoes << "\n";
        oficinas << "-\n";
        for (int i = 0; i < numEstacoes; i++) { //percorre todas as ETs 
            oficinas << estacao[i].idET << "\n";
            oficinas << estacao[i].capacidade << "\n";
            oficinas << estacao[i].quantidadeCarros << "\n";
            oficinas << estacao[i].faturacao << "\n";
            oficinas << estacao[i].mecanico << "\n";
            oficinas << estacao[i].marcaEspecializada << "\n";
            for (int j = 0; j < estacao[i].quantidadeCarros; j++) { //percorre todos os carros dentro da ET
                oficinas << "--\n";
                oficinas << estacao[i].carroNaEt[j].idCarro << "\n";
                oficinas << estacao[i].carroNaEt[j].tempoMax << "\n";
                oficinas << estacao[i].carroNaEt[j].dias << "\n";
                oficinas << estacao[i].carroNaEt[j].prioritario << "\n";
                oficinas << estacao[i].carroNaEt[j].marca << "\n";
                oficinas << estacao[i].carroNaEt[j].modelo << "\n";
            } oficinas << "-\n";
        }
    }
    else {
        cout << "Não foi possivel abrir o ficheiro oficinas\n";
    }
}

//método que grava a fila de espera
void gravarFilaDeEspera(carro*& carros, int numCarros) {

    ofstream fila("filaEspera.txt"); //cria um ficheiro com o nome

    fila.clear(); //faz o clear do ficheiro


    if (fila.is_open()) { //verifica se o ficheiro pode ser aberto para ser guardada as informações
        fila << "-\n";
        fila << numCarros << "\n";
        for (int i = 0; i < numCarros; i++) { //faz o loop pela quantidade de carros na fila de espera
            fila << "-\n";
            fila << carros[i].idCarro << "\n";
            fila << carros[i].tempoMax << "\n";
            fila << carros[i].dias << "\n";
            fila << carros[i].prioritario << "\n";
            fila << carros[i].marca << "\n";
            fila << carros[i].modelo << "\n";
        }
    }else {
        cout << "Não foi possivel abrir o ficheiro filaEspera\n";
    }
}

//método para dar upload de um ficheiro
void uploadEstacao(estacoes*& estacao, int& numEstacoes, int& numCarrosTotal) {

    delete[] estacao;

    ifstream oficinas("oficinas.txt"); // abre o arquivo para leitura

    if (oficinas.is_open()) { // verifica se o arquivo foi aberto com sucesso
        string linha;
        getline(oficinas, linha); // lê a primeira linha do arquivo (deve ser "-")
        getline(oficinas, linha); // lê a segunda linha do arquivo (número de estações)
        numEstacoes = stoi(linha); // converte a string em um inteiro
        getline(oficinas, linha); // lê a próxima linha (deve ser "-")

        // aloca espaço para o vetor de estações com base no número de estações lido do arquivo
        estacao = new estacoes[numEstacoes];

        for (int i = 0; i < numEstacoes; i++) { // percorre todas as estações
            getline(oficinas, linha); // lê a próxima linha (id da ET)
            estacao[i].idET = stoi(linha); // converte a string em um inteiro
            getline(oficinas, linha); // lê a próxima linha (capacidade da ET)
            estacao[i].capacidade = stoi(linha); // converte a string em um inteiro
            getline(oficinas, linha); // lê a próxima linha (quantidade de carros na ET)
            estacao[i].quantidadeCarros = stoi(linha); // converte a string em um inteiro
            numCarrosTotal += estacao[i].quantidadeCarros;
            getline(oficinas, linha); // lê a próxima linha (faturação da ET)
            estacao[i].faturacao = stoi(linha); // converte a string em um inteiro
            getline(oficinas, linha); // lê a próxima linha (mecânico da ET)
            estacao[i].mecanico = linha; // converte a string em um inteiro
            getline(oficinas, linha); // lê a próxima linha (marca especializada da ET)
            estacao[i].marcaEspecializada = linha; // armazena a linha diretamente

            int index = 0;

            while (getline(oficinas, linha) && linha != "-" && index < estacao[i].quantidadeCarros) { //lê a próxima linha (deve ser "--") e lê as informações de cada carro na ET
                
                getline(oficinas, linha);
                estacao[i].carroNaEt[index].idCarro = stoi(linha);
                getline(oficinas, linha);
                estacao[i].carroNaEt[index].tempoMax = stoi(linha);
                getline(oficinas, linha);
                estacao[i].carroNaEt[index].dias = stoi(linha);
                getline(oficinas, linha);
                estacao[i].carroNaEt[index].prioritario = stoi(linha);
                getline(oficinas, linha);
                estacao[i].carroNaEt[index].marca = linha;
                getline(oficinas, linha);
                estacao[i].carroNaEt[index].modelo = linha;
                index++;
            }
        }
    }
    oficinas.close();
}

void uploadFilaDeEspera(int& numCarros, carro*& carros, int& numCarrosTotal) {

    delete[] carros;

    ifstream filaEspera("filaEspera.txt"); // abre o arquivo para leitura

    if (filaEspera.is_open()) {
        string linha;
        getline(filaEspera, linha); //proximo "-"
        getline(filaEspera, linha);
        numCarros = stoi(linha);
        numCarrosTotal += numCarros;
        getline(filaEspera, linha); //proximo "-"

        carros = new carro[numCarros];

        for (int i = 0; i < numCarros; i++) {
            getline(filaEspera, linha);
            carros[i].idCarro = stoi(linha);
            getline(filaEspera, linha);
            carros[i].tempoMax = stoi(linha);
            getline(filaEspera, linha);
            carros[i].dias = stoi(linha);
            getline(filaEspera, linha);
            carros[i].prioritario = stoi(linha);
            getline(filaEspera, linha);
            carros[i].marca = linha;
            getline(filaEspera, linha);
            carros[i].modelo = linha;
            getline(filaEspera, linha);
        }
    }
    filaEspera.close();
}

//faz output por ordem alfabetica e de dias
void imprimirEstacoes(estacoes* estacao, int numEstacoes) {

    int totalCarros = 0;
    for (int i = 0; i < numEstacoes; i++) {
        totalCarros += estacao[i].quantidadeCarros;
    }

    carro* novaLista = new carro[totalCarros];

    int index = 0;
    for (int i = 0; i < numEstacoes; i++) {
        for (int j = 0; j < estacao[i].quantidadeCarros; j++) {
            novaLista[index++] = estacao[i].carroNaEt[j];
        }
    }

    auto cmp = [](const carro& a, const carro& b) {
        if (a.marca != b.marca) {
            return a.marca < b.marca;
        }
        else {
            return a.tempoMax < b.tempoMax;
        }
    };

    sort(novaLista, novaLista + totalCarros, cmp);

    cout << "\nCarros nas estações de trabalho:\n";
    for (int j = 0; j < totalCarros; j++) {
        cout << "Carro ID: " << novaLista[j].idCarro << " | "
            << novaLista[j].marca << "-" << novaLista[j].modelo
            << " | Prioridade: " << novaLista[j].prioritario << " | Tempo de Reparação: "
            << novaLista[j].tempoMax << " | Dias na oficina: " << novaLista[j].dias << "\n";
    }
}

void imprimirListaEspera(carro carros[], int numCarros) {

    auto cmp = [](const carro& a, const carro& b) {
        if (a.marca != b.marca) {
            return a.marca < b.marca;
        }
        else {
            return a.tempoMax < b.tempoMax;
        }
    };

    sort(carros, carros + numCarros, cmp);

    cout << "\nFila de espera: \n";
    for (int i = 0; i < numCarros; i++) {
        cout << "Carro ID: " << carros[i].idCarro << " | "
            << "Marca: " << carros[i].marca << " | "
            << "Modelo: " << carros[i].modelo << " | "
            << "Prioridade: " << carros[i].prioritario << " | "
            << "Tempo de Reparacao: " << carros[i].tempoMax << " | "
            << "Dias na oficina: " << carros[i].dias << "\n";
    }
}

void gestao(estacoes*& estacao, int numEstacoes, string marcas[], int& numeroPalavrasMarcas, int numCarros, carro*& carros, int& numCarrosTotal) {

    int options;

    cout << "\n***** Bem vindo gestor *****\n";
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

        reparacaoManual(estacao, numEstacoes, numCarros, carros);

        break;

    case 2:

        tempoDeReparacao(carros, numCarros, numEstacoes, estacao);

        break;

    case 3:

        adicionarPrioridade(carros, numCarros, numEstacoes, estacao);

        break;

    case 4:

        removerMecanico(estacao, numEstacoes, marcas, numeroPalavrasMarcas, numCarros, carros);

        break;

    case 5:

        gravarEstacao(estacao, numEstacoes);
        gravarFilaDeEspera(carros, numCarros);

        break;

    case 6:

        uploadEstacao(estacao, numEstacoes, numCarrosTotal);
        uploadFilaDeEspera(numCarros, carros, numCarrosTotal);
        printETs(estacao, numEstacoes);
        printCars(carros, numCarros);

        break;

    case 7:

        imprimirEstacoes(estacao, numEstacoes);
        imprimirListaEspera(carros, numCarros);

        break;

    default:

        cout << "Não selecionou uma opção válida\n";

        break;
    }
}