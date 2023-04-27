#pragma once
#include <stdlib.h>
#include "structs.h"
#include "gestao.h"

using namespace std;

void reparacaoManual(estacoes*& estacao, int numEstacoes, int numCarros, carro*& carros);

void tempoDeReparacao(carro*& carros, int numCarros, int numEstacoes, estacoes*& estacao);

void adicionarPrioridade(carro*& carros, int numCarros, int numEstacoes, estacoes*& estacao);

void removerTodosCarros(int numEstacoes, estacoes*& estacao, int indice);

void removerMecanico(estacoes*& estacao, int numEstacoes, string marcas[], int& numeroPalavrasMarcas, int numCarros, carro*& carros);

void gravarEstacao(estacoes*& estacao, int numEstacoes);

void gravarFilaDeEspera(carro*& carros, int numCarros);

void uploadEstacao(estacoes*& estacao, int& numEstacoes, int& numCarrosTotal);

void uploadFilaDeEspera(int& numCarros, carro*& carros, int& numCarrosTotal);

void imprimirEstacoes(estacoes* estacao, int numEstacoes);

void imprimirListaEspera(carro carros[], int numCarros);

void gestao(estacoes*& estacao, int numEstacoes, string marcas[], int& numeroPalavrasMarcas, int numCarros, carro*& carros, int& numCarrosTotal);
