#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include "../Solucao.h"
#include <cstdlib>

bool bestImprovementSwap(Data& data, Solucao *s);
bool bestImprovement2Opt(Data& data, Solucao *s);
bool bestImprovementOrOpt(Data& data, Solucao *s, int tipo);
void BuscaLocal(Data& data, Solucao *s);

#endif