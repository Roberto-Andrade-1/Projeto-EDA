#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include "structs.h"
#include "gestao.h"

using namespace std;

string* lerFicheiro(const string& nomeFicheiro, int& numeroPalavras);

string escolhePalavraRandom(const string* palavras, int numeroPalavras);

void removeDaET(estacoes*& estacao, carro*& carrosET, int capacidadeET, int quantidadeET, int indiceCarro);

void adicionaDias(estacoes*& estacao,int& numEstacoes);

void inserirNaListaEspera(carro*& carros, const carro& novoCarro, int numCarros);

void criarCarro(carro*& carros, int& numCarros, int& numCarrosTotal, int& numeroPalavrasMarcas, int& numeroPalavrasModelos, estacoes*& estacao, int& numEstacoes, string marcas[], string modelos[]);

void removeDaListaEspera(carro*& carros, int& numCarros, int j);

void adicionaCarroET(carro*& carros, int numEstacoes, int& numCarros, estacoes*& estacao);

void primeirosCarros(carro*& carros, string marcas[], string modelos[], int& numeroPalavrasMarcas, int& numeroPalavrasModelos, int& numCarros, int& numCarrosTotal);

void estacaoTrabalho(estacoes*& estacao, int& numET, int& numEstacoes, int& numeroPalavrasMarcas, string marcas[]);

void printCars(carro*& carros, int comprimento);

void printETs(estacoes*& estacao, int comprimento);
