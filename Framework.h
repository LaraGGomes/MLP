#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "Solucao.h"
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Pertubacao.h"

Solucao ILS(Data& data, int maxIter, int maxIterIls);

#endif