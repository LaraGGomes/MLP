#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <iostream>     // cout
#include <vector>       // vetor 
#include "leitor-instancias/src/Data.h"

using namespace std;

typedef struct Solucao {
    vector<int> sequence;
    double cost;
} Solucao;

// protótipos das funções de solução
void exibirSolucao(Solucao *s);
void calcularCusto(Data& data, Solucao *s);

#define d(x, y) getDistance(x, y)
// pra simplificar o getDistance, que calcula o custo entre dois vértices

#endif