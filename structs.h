#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct ET
{
    int id;
    int capacidade;
    int quantidadeCarros;
    string mecanico;
    string marcaEspecializada;
};

struct carro
{
    int id;
    int tempoMax;
    int dias;
    bool prioritario; // false não é, true é
    string marca;
    string modelo;
};
