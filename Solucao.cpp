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
        // o getDistance(x, y) é o matrizAdj[x][y]
}