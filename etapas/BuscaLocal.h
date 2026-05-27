#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "../Solucao.h"
#include <cstdlib>

bool bestImprovementSwap(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix);
bool bestImprovement2Opt(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix);
bool bestImprovementOrOpt(Data& data, Solucao *s, int tipo, vector<vector<Subsequence>>& subseq_matrix);
void BuscaLocal(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix);

#endif