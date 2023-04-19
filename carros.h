#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct carro
{
    int idCarro;
    int tempoMax;
    int dias;
    bool prioritario;
    bool reparado;
    string marca;
    string modelo;
};

struct registoDaET{
    string car = "";
};

struct estacoes
{
    int idET;
    int capacidade;
    int quantidadeCarros;
    string mecanico;
    string marcaEspecializada;
    carro* carroNaEt = new carro;
    registoDaET* registoEt = new registoDaET;
};