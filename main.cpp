#include "Framework.h"
#include "leitor-instancias/src/Data.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);

    data.read();

    int maxIter = 10, maxIterILS;
    int V = data.getDimension();
    vector<double> R(25);

    double xi = 0.00, xf = 0.25, pulo = 0.01;
    for (int i = 0; i < 25; i++) R[i] = xi + i*pulo;
    
    srand(time(NULL));

    maxIterILS = min(100, V);

    Solucao melhorSolucao = ILS(data, maxIter, maxIterILS, R);

    cout << "\nCusto da melhor solucao encontrada: " << melhorSolucao.cost << endl;

    return 0;
}