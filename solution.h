#include <vector>       // pra vetor 
#include <algorithm>    // pra sort

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
void calcularCusto(Solucao *s);