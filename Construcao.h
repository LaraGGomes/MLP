#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "Solucao.h"
#include <cstdlib>      // rand
#include <algorithm>    // find

using namespace std;

typedef struct InsertionInfo {
    int noInserido;
    int arestaRemovida;
    double custo;
}InsertionInfo;

// protótipo das funções necessárias
Solucao Construcao(Data& data);
vector<InsertionInfo> calcularCustoInsercao(Data& data, Solucao& s, vector<int>& CL);
vector<int> escolher3NosAleatorios(Data& data);
vector<int> nosRestantes(Data& data, vector<int> sequencia);
void ordenarEmOrdemCrescente(vector<InsertionInfo>& custoInsercao);
void inserirNaSolucao(Solucao& s, InsertionInfo selecionado);

#endif