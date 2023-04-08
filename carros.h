#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct carro
{
    int idCarro;
    int tempoMax;
    int dias;
    bool prioritario; // false não é, true é
    string marca;
    string modelo;
};