#include "Solucao.h"
#include <cstdlib>

bool bestImprovementSwap(Data& data, Solucao *s);
bool bestImprovement2Opt(Data &data, Solucao *s);
bool bestImprovementOrOpt(Data &data, Solucao *s, char tipo);   // coloquei o tipo como char pra ocupar menos
void BuscaLocal(Data& data, Solucao *s);

bool bestImprovementSwap(Data& data, Solucao *s) {
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i < s->sequence.size() - 1; i++) {
        int vi = s->sequence[i];
        int vi_prox = s->sequence[i+1];
        int vi_ante = s->sequence[i-1];

        for(int j = i + 1; j < s->sequence.size() - 1; j++) {
            int vj = s->sequence[j];
            int vj_prox = s->sequence[j+1];
            int vj_ante = s->sequence[j-1];

            double delta = -data.d(vi_ante, vi) - data.d(vi, vi_prox) + data.d(vi_ante, vj)
                            + data.d(vj, vi_prox) - data.d(vj_ante, vj) - data.d(vj, vj_prox)
                            + data.d(vj_ante, vi) + data.d(vi, vj_prox);

            if(delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0) {
        swap(s->sequence[best_i], s->sequence[best_j]);
        s->cost = s->cost + bestDelta;
        return true;
    }

    return false;
}

void BuscaLocal(Data& data, Solucao *s) {
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false) {
        // aleatorizar a operação a ser feita
        int n = rand()% NL.size();
        switch (NL[n]) {
        case 1:
            improved = bestImprovementSwap(data, s);
            break;        
        case 2:
            improved = bestImprovement2Opt(data, s);
            break;        
        case 3:
            improved = bestImprovementOrOpt(data, s, '1');
            break;        
        case 4:
            improved = bestImprovementOrOpt(data, s, '2');
            break;        
        case 5:
            improved = bestImprovementOrOpt(data, s, '3');
            break;        
        }

        if(improved) 
            NL = {1, 2, 3, 4, 5};
        else    // vai realizar novas operações enquanto não houver melhora
            NL.erase(NL.begin() + n);
    }
}
