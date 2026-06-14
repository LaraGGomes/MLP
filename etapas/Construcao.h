#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include "../Solucao.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

Solucao Construcao(Data& data, vector<double>& R);
vector<int> nosRestantes(Data& data, vector<int> sequencia);
void ordenarEmOrdemCrescente(Data& data, vector<int>& CL, int r);
vector<int> melhoresCL(vector<int>& CL, double alpha);

#endif