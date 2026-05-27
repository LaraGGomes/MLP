#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "Solucao.h"
#include "etapas/Construcao.h"
#include "etapas/BuscaLocal.h"
#include "etapas/Pertubacao.h"

Solucao ILS(Data& data, int maxIter, int maxIterIls, vector<double>& R);

#endif