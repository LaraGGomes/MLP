#include "Solucao.h"

void exibirSolucao(Solucao *s) {
    for (int i = 0; i < s->sequence.size() - 1; i++) 
        cout << s->sequence[i] << " -> ";

    cout << s->sequence.back() << endl;
}

void calcularCusto(Data& data, Solucao *s) {
    s->cost = 0;
    for (int i = 0; i < s->sequence.size() - 1; i++)
        s->cost += data.d(s->sequence[i], s->sequence[i+1]);
}

void updateAllSubseq(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix) {
    int n = s->sequence.size(); // num de subsequências formadas por apenas 1 nó

    // subsequências de nó único
    for (int i = 0; i < n; i++) {
        int v = s->sequence[i];
        subseq_matrix[i][i].C = 0;
        subseq_matrix[i][i].T = 0;
        subseq_matrix[i][i].W = (i > 0);
        subseq_matrix[i][i].first = s->sequence[i];
        subseq_matrix[i][i].last = s->sequence[i];
    }

    // concatenações de subsequências
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++)
            subseq_matrix[i][j] = Subsequence::Concatenate(data, subseq_matrix[i][j-1], subseq_matrix[j][j]);
    }

    // subsequências invertidas
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--)
            subseq_matrix[i][j] = Subsequence::Concatenate(data, subseq_matrix[i][j+1], subseq_matrix[j][j]);
    }
}

// função pra atualizar apenas as subsequências que mudaram após um movimento
void updateSubseq(Data& data, Solucao *s, vector<vector<Subsequence>>& subseq_matrix);