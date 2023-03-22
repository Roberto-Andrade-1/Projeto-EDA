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
    int prioritario; // 0 não é, 1 é
    string marca;
    string modelo;
};
