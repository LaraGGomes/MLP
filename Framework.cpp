#include "Framework.h"

Solucao ILS(Data& data, int maxIter, int maxIterIls) {
    Solucao bestOfAll;
    bestOfAll.cost = INFINITY;

    for (int i = 0; i < maxIter; i++) {
        Solucao s = Construcao(data);
        Solucao best = s;

        int iterIls = 0;

        while(iterIls <= maxIterIls) {
            BuscaLocal(data, &s);

            if(s.cost < best.cost) {
                best = s;
                iterIls = 0;
            }

            s = Pertubacao(data, best);
            iterIls++;
        }

        if(best.cost < bestOfAll.cost) 
            bestOfAll = best;
    }

    return bestOfAll;
}