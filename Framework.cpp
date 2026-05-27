#include "Framework.h"

Solucao ILS(Data& data, int maxIter, int maxIterIls, vector<double>& R) {
    Solucao bestOfAll;
    bestOfAll.cost = INFINITY;

    for (int i = 0; i < maxIter; i++) {
        Solucao s = Construcao(data, R);
        Solucao best = s;
        int n = s.sequence.size();

        vector<vector<Subsequence>> subseq_matrix(n, vector<Subsequence>(n));

        updateAllSubseq(data, &s, subseq_matrix);

        int iterIls = 0;

        while(iterIls <= maxIterIls) {
            BuscaLocal(data, &s, subseq_matrix);

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