#include "Framework.h"
#include "leitor-instancias/src/Data.h"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char** argv) {
    int t = 10;
    double custoM = 0, tempoM = 0;

    while (t--) {
        auto inicio = std::chrono::high_resolution_clock::now();
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

        melhorSolucao.sequence.push_back(1);
        calcularCusto(data, &melhorSolucao);

        auto fim = std::chrono::high_resolution_clock::now();
        chrono::duration<double> duracao = fim - inicio;

        custoM += melhorSolucao.cost;
        tempoM += duracao.count();
    }

    std::cout << "\nCusto medio: " << custoM/10 << endl;
    std::cout << "Tempo de execucao: " << tempoM/10 << " segundos.\n";

    return 0;
}
