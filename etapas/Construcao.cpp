#include "Construcao.h"

vector<int> nosRestantes(Data& data) {
    vector<int> CL;

    for (int i = 2; i <= data.getDimension(); i++) 
        CL.push_back(i);

    return CL;
}

void ordenarEmOrdemCrescente(Data& data, vector<int>& CL, int r) {

    sort(CL.begin(), CL.end(), [&](int a, int b) { 
        return data.d(r, a) < data.d(r, b);
    });
}

vector<int> melhoresCL(vector<int>& CL, double alpha) {

    vector<int> RCL;
    double x = alpha*CL.size();

    if (x < 1) x = 1;

    for (int i = 0; i < x; i++) 
        RCL.push_back(CL[i]);

    return RCL;
}


void inserirNaSequencia(Data& data, Solucao *s, int c) {
    s->sequence.push_back(c);
    //s->cost += latencia(data, s, s->sequence.size());
}

/*
Nova Construção!!

alpha escolhido random em R
sequencia inicializada como {1}
CL inicializada {2 ,.., n}
r = 1

while (!CL.empty()) {
    ordernar CL por distancia em referencia a r
    RCL recebe random melhores (assumindo menores) do CL
    escolho c de RCL random
    insiro c na sequencia
    r = c
    tiro r de CL
}

*/

Solucao Construcao(Data& data, vector<double>& R) {
    int index = rand()% R.size();
    double alpha = R[index];

    Solucao s;
    s.sequence = {1};
    s.cost = 0;

    vector<int> CL = nosRestantes(data);

    int r = 1;

    while (!CL.empty()) {
        ordenarEmOrdemCrescente(data, CL, r);

        vector<int> RCL = melhoresCL(CL, alpha);

        index = rand()% RCL.size();
        int c = RCL[index];

        inserirNaSequencia(data, &s, c);

        r = c;

        CL.erase(CL.begin() + index);
    }

    // s.sequence.push_back(1);
    calcularCusto(data, &s);

    /*
    Modificações:
    - não usa mais insertation info, nem as primeiras duas funções
    - escolhi os alpha porcento melhores de CL, verificar sse é isso mesmo 
    - verificar tb se o index tá correto na remoção de CL
    - fazendo cálculo de custo durante inserção
    */

    return s;
}