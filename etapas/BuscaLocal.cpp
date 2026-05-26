#include "BuscaLocal.h"

bool bestImprovementSwap(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix) {
    double bestC = 0;
    int best_i, best_j;
    int n = data.getDimension();

    for(int i = 1; i < s->sequence.size() - 1; i++) {

        for(int j = i + 1; j < s->sequence.size() - 1; j++) {
            Subsequence sigma_1 = Subsequence::Concatenate(data, subseq_matrix[0][i-1], subseq_matrix[j][j]);
            Subsequence sigma_2 = Subsequence::Concatenate(data, sigma_1, subseq_matrix[i+1][j-1]);
            Subsequence sigma_3 = Subsequence::Concatenate(data, sigma_2, subseq_matrix[i][i]);
            Subsequence sigma_4 = Subsequence::Concatenate(data, sigma_3, subseq_matrix[j+1][n]);

            double C = sigma_4.C;

            if(C < s->cost && C < bestC) {
                bestC = C;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestC < 0) {
        swap(s->sequence[best_i], s->sequence[best_j]);

        s->cost = bestC;

        updateSubseq(data, s, subseq_matrix, best_i, best_j);

        return true;
    }

    return false;
}

// seleciona dois vértices não adjacentes, remove as arestas,
// inverter todos os segmentos entre elas, e colocar arestas novas
bool bestImprovement2Opt(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix) {
    double bestC = 0;
    int best_i, best_j;
    int n = data.getDimension();

    for (int i = 1; i < s->sequence.size() - 1; i++) {

        // segunda condição garante que não vão haver arestas adjacentes
        for (int j = i + 2; j < s->sequence.size() - 1 && s->sequence[j+1] != s->sequence[i]; j++) {
            Subsequence sigma_1 = Subsequence::Concatenate(data, subseq_matrix[0][i-1], subseq_matrix[j][i]);
            Subsequence sigma_2 = Subsequence::Concatenate(data, sigma_1, subseq_matrix[j+1][n]);

            double C = sigma_2.C;

            if(C < s->cost && C < bestC) {
                bestC = C;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestC < 0) {
        swap(s->sequence[best_i+1], s->sequence[best_j]);

        // inversão do segmento entre as arestas
        for (int i = best_i+2, j = best_j - 1; i < best_j && j > i; i++, j--) {
            swap(s->sequence[i], s->sequence[j]);
        }

        s->cost = bestC;

        updateSubseq(data, s, subseq_matrix, best_i, best_j);

        return true;
    }

    return false;
}

// seleciona x vértices adjacentes, remove e então reensere em uma nova posição
bool bestImprovementOrOpt(Data &data, Solucao *s, int tipo, vector<vector<Subsequence>>& subseq_matrix) {
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 1; i <= s->sequence.size() - 1 - tipo; i++) {
        int vi = s->sequence[i];
        int vi_prox = s->sequence[i+tipo];
        int vi_ante = s->sequence[i-1];
        int vi_last = s->sequence[i+tipo-1];

        for(int j = 1; j < s->sequence.size() - 1; j++) {
            if (j - i <= tipo + 1 && j - i >= 0) continue;

            int vj = s->sequence[j];
            int vj_ante = s->sequence[j-1];

            double delta = -data.d(vi_ante, vi) + data.d(vi_ante, vi_prox) - data.d(vj_ante, vj) + data.d(vj_ante, vi) - data.d(vi_last, vi_prox) + data.d(vi_last, vj);

            if(delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0) {
        vector<int> segmento(s->sequence.begin() + best_i, s->sequence.begin() + best_i + tipo);

        s->sequence.erase(s->sequence.begin() + best_i, s->sequence.begin() + best_i + tipo);

        if(best_i < best_j) 
            s->sequence.insert(s->sequence.begin() + best_j - tipo, segmento.begin(), segmento.end());
        else 
            s->sequence.insert(s->sequence.begin() + best_j, segmento.begin(), segmento.end());

        s->cost += bestDelta;

        return true;
    }

    return false;  
}

void BuscaLocal(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix) {
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false) {

        int n = rand()% NL.size();
        switch (NL[n]) {
        case 1:
            improved = bestImprovementSwap(data, s, subseq_matrix);
            break;        
        case 2:
            improved = bestImprovement2Opt(data, s, subseq_matrix);
            break;        
        case 3:
            improved = bestImprovementOrOpt(data, s, 1, subseq_matrix);
            break;        
        case 4:
            improved = bestImprovementOrOpt(data, s, 2, subseq_matrix);
            break;        
        case 5:
            improved = bestImprovementOrOpt(data, s, 3, subseq_matrix);
            break;        
        }

        if(improved) 
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}
