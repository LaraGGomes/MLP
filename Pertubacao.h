#include "Solucao.h"
#include <cstdlib>
#include <ctime>

// Passos:
// - s' <- s
// - escolher aleatoriamente dois segmentos não sobrepostos de s' de tamanhos entre 2 e |V|/10
// - trocar a posição dos elementos
// - retornar s'

// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 1
// min 2 ; max 4(?)
// pos2 = 1 pos1 = 5
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 1
// 2 3 4 5   6 7
// ia = 1 ip = 6
// ja = 5 jp = 8

// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 1
// i_ant = 1, pos1 = 1
// j_ant = 7, pos2 = 7
// insert i2 no pos1
// 1 8 9 2 3 4 5 6 7 8 9 10 11 12 13 14 1
// remove i2 do pos2
// 1 8 9 2 3 4 5 6 7 10 11 12 13 14 1
// find posição i_pos = 3
// find posição j_ant + 1 = 9
// insert i1 no j_ant_pos
// 1 8 9 2 3 4 5 6 7 2 3 4 5 10 11 12 13 14 1
// remove i1 de i_pos
// 1 8 9 6 7 2 3 4 5 10 11 12 13 14 1
//
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 1
// i_ant = 1, pos1 = 1
// j_ant = 4, pos2 = 4
// guardar -> menor pos = 1 e anterior do outro = 4
// remove maior pos (s2)
// 1 2 3 4 8 9 10 11 12 13 14 1
// inserir s2 no pos1
// 1 5 6 7 2 3 4 8 9 10 11 12 13 14 1
// find nova pos s1 (novo_pos1 = 4)
// find anterior (pos_ante = 6)
// insert s1 no pos_ante+1
// 1 5 6 7 2 3 4 2 3 4 8 9 10 11 12 13 14 1
// remove s1 do novo_pos1
// 1 5 6 7 2 3 4 8 9 10 11 12 13 14 1

// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 1
// s1_ant = 2, pos1 = 2
// s2_ant = 9, pos2 = 9
// insert s1 no find(s2_ant)+1
// 1 2 3 4 5 6 7 8 9 3 4 10 11 12 13 14 1
// find(s1_ant) + 1
// remove s1 do pos1
// 1 2 5 6 7 8 9 3 4 10 11 12 13 14 1
// remove s2 do pos2
// 1 2 5 6 7 8 9 3 4 12 13 14 1
// insert s2 no find()
// 1 2 10 11 5 6 7 8 9 3 4 12 13 14 1

// 1 6 7 2 3 4 5 8 9 10 11 12 13 14 1

Solucao Pertubacao(Data& data, Solucao* s) {
    Solucao novaS;
    bool conflito = true;
    int i1, i2;         // intervalos dos segmentos
    int pos1, pos2;     // posição inicial de cada intervalo
    int max = s->sequence.size() - 1 % 10;   // perguntar pra Marcelo se é módulo de 10 ou to interpretando errado

    novaS.sequence = s->sequence;

    srand(time(NULL));
    i1 = 2 + rand() % (max - 1);
    i2 = 2 + rand() % (max - 1);

    // garantir que os dois segmentos não se sobreponham
    while (conflito) {
        int limite = s->sequence.size() - 1;
        pos1 = 1 + rand() % (limite - i1);
        pos2 = 1 + rand() % (limite - i2);

        if (pos1 < pos2 && pos1 + i1 <= pos2 || pos1 > pos2 && pos1 >= pos2 + i2) {
            conflito = false;
        }
        // ou coloco pos1 < pos2 && pos1 + i1 <= pos2, limitando que s1 seja antes de s2
    }

    vector<int> s1(novaS.sequence.begin() + pos1, novaS.sequence.begin() + i1); // sequencia 1
    vector<int> s2(novaS.sequence.begin() + pos2, novaS.sequence.begin() + i2); // sequencia 2

    int s1_ante = novaS.sequence[pos1-1];

    // inserindo s1
    for(int i = s1.size() - 1; i >= 0; i--) {
        novaS.sequence.insert(novaS.sequence.begin() + pos2, s1[i]);
    }

    auto pos_ante = find(novaS.sequence.begin(), novaS.sequence.end(), s1_ante);

    // remove s1 antigo
    for (int i = 0; i < s1.size(); i++) {
        novaS.sequence.erase(novaS.sequence.begin() + pos1);
    }

    // remove s2
    for (int i = 0; i < s2.size(); i++) {
        novaS.sequence.erase(novaS.sequence.begin() + pos2);
    }

    // insere s1
    for(int i = s2.size() - 1; i >= 0; i--) {
        novaS.sequence.insert(pos_ante, s2[i]);
    }

    calcularCusto(data, &novaS);

    return novaS;
}
