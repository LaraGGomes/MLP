#include "Pertubacao.h"

Solucao Pertubacao(Data& data, Solucao& s, vector<vector<Subsequence>>& subseq_matrix) {
    Solucao novaS;
    bool conflito = true;
    int i1, i2;         // intervalos dos segmentos
    int pos1, pos2;     // posição inicial de cada intervalo
    int max = ceil((s.sequence.size() - 1) / 10.0);

    if (max <= 2)
        i1 = i2 = 2;
    else {
        i1 = 2 + rand() % (max - 1);
        i2 = 2 + rand() % (max - 1);
    }

    // garantir que os dois segmentos não se sobreponham
    while (conflito) {
        int limite = s.sequence.size();
        pos1 = 1 + rand() % (limite - i1);
        pos2 = 1 + rand() % (limite - i2);

        // duas condições de não ter conflito
        if (pos1 < pos2 && pos1 + i1 <= pos2) {
            conflito = false;
        }
        // nesse caso, troco as variáveis pra pos1 ser sempre antes
        else if (pos1 > pos2 && pos1 >= pos2 + i2) {
            swap(pos1,pos2);
            swap(i1,i2);

            conflito = false;
        }
    }

    // cálculo do custo da nova solução
    double novoC;
    Subsequence sigma_1, sigma_2, sigma_3;
    sigma_1 = Subsequence::Concatenate(data, subseq_matrix[0][pos1-1], subseq_matrix[pos2][pos2+i2-1]);

    // adjacência
    if (pos1+i1 == pos2) sigma_2 = Subsequence::Concatenate(data, sigma_1, subseq_matrix[pos1][pos1+i1-1]);
    else {
        Subsequence sigma_aux = Subsequence::Concatenate(data, sigma_1, subseq_matrix[pos1+i1][pos2-1]);
        sigma_2 = Subsequence::Concatenate(data, sigma_aux, subseq_matrix[pos1][pos1+i1-1]);
    }

    // segundo segmento termina a sequência
    if (pos2+i2 == s.sequence.size()) novoC = sigma_2.C;
    
    else {
        sigma_3 = Subsequence::Concatenate(data, sigma_2, subseq_matrix[pos2+i2][s.sequence.size()-1]);
        novoC = sigma_3.C;
    }

    novaS.cost = novoC;

    // alocação da nova solução
    vector<int> s1(s.sequence.begin() + pos1, s.sequence.begin() + pos1 + i1); // sequencia 1
    vector<int> s2(s.sequence.begin() + pos2, s.sequence.begin() + pos2 + i2); // sequencia 2
    novaS.sequence.reserve(s.sequence.size());  // definindo tamanho

    novaS.sequence.insert(novaS.sequence.end(), s.sequence.begin(), s.sequence.begin() + pos1);

    novaS.sequence.insert(novaS.sequence.end(), s2.begin(), s2.end());

    novaS.sequence.insert(novaS.sequence.end(), s.sequence.begin() + pos1 + i1, s.sequence.begin() + pos2);

    novaS.sequence.insert(novaS.sequence.end(), s1.begin(), s1.end());

    novaS.sequence.insert(novaS.sequence.end(), s.sequence.begin() + pos2 + i2, s.sequence.end());

    return novaS;
}