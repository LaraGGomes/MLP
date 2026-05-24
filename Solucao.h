#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <iostream>
#include <vector>
#include "leitor-instancias/src/Data.h"

using namespace std;

typedef struct Solucao {
    vector<int> sequence;
    double cost;
} Solucao;

typedef struct Subsequence {
    // valores auxiliares
    double T, C;    // duração, custo acumulado
    int W;          // custo de atraso
    int first, last;

    // função Concatenate()
    inline static Subsequence Concatenate(Data& data, Subsequence &sigma_1, Subsequence &sigma_2) {
        Subsequence sigma;
        double temp = data.getDistance(sigma_1.last,sigma_2.first);
        sigma.W = sigma_1.W + sigma_2.W;
        sigma.T = sigma_1.T + temp + sigma_2.T;
        sigma.C = sigma_1.C + sigma_2.W * (sigma_1.T + temp) + sigma_2.C;
        sigma.first = sigma_1.first;
        sigma.last = sigma_2.last;

        return sigma;
    }
} Subsequence;

void exibirSolucao(Solucao *s);
void calcularCusto(Data& data, Solucao *s);
void updateAllSubseq(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix);
void updateSubseq(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix);

#define d(x, y) getDistance(x, y)
// pra simplificar o getDistance, que calcula o custo entre dois vértices

#endif