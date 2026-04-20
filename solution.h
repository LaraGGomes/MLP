#include <iostream>     // cout
#include <vector>       // vetor 
#include <algorithm>    // sort
#include "leitor-instancias/src/Data.h"

using namespace std;
/*uso ou não?? não afeta performance, afeta miiiiinimamente tempo de execução, 
mas a pira mesmo seria eu considerar o que ficaria mais bonitinho
*/

typedef struct Solucao {
    vector<int> sequencia;
    double custo;
} Solucao;

// protótipos das funções de solução
void exibirSolucao(Solucao *s);
void calcularCusto(Data *data, Solucao *s);

void exibirSolucao(Solucao *s) {
    for (int i = 0; i < s->sequencia.size() - 1; i++) 
        cout << s->sequencia[i] << " -> ";

    cout << s->sequencia.back() << endl;
}

void calcularCusto(Data *data, Solucao *s) {
    s->custo = 0;
    for (int i = 0; i < s->sequencia.size() - 1; i++)
        s->custo += data->getDistance(s->sequencia[i], s->sequencia[i+1]);
        // o getDistance(x, y) é o matrizAdj[x][y]
}