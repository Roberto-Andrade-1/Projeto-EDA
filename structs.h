#pragma once
#include <string>
#include <stdlib.h>

using namespace std;

struct carro
{
    int idCarro;
    int tempoMax;
    int dias;
    bool prioritario;
    string marca;
    string modelo;
};

struct estacoes
{
    int idET;
    int capacidade;
    int quantidadeCarros;
    int faturacao;
    string mecanico;
    string marcaEspecializada;
    carro* carroNaEt = new carro;
};