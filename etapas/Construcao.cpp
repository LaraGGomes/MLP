#include "Construcao.h"

// vai receber um subtour aleatório, e CL são os vértices restantes não inclusos no subtour
vector<InsertionInfo> calcularCustoInsercao(Data& data, Solucao& s, vector<int>& CL) {

    vector<InsertionInfo> custoInsercao((s.sequence.size() - 1) * CL.size());
    int l = 0;

    for (int a = 0; a < s.sequence.size() - 1; a++) {
        int i = s.sequence[a];
        int j = s.sequence[a+1];

        // para cada nó restante, vamos registrar as informações de inserção em uma posição do vetor 
        for (auto k : CL) {
            // novo custo é calculado adicionando as distância entre a nova aresta e os vértices e removendo a distância entre os dois vértices
            custoInsercao[l].custo = data.d(i, k) + data.d(j, k) - data.d(i, j);
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;

            l++;
        }
    }
    return custoInsercao;   
}

vector<int> escolher3NosAleatorios(Data& data) {
    vector<int> s;

    s.push_back(1);

    for(int i = 0; i < 3; i++) {
        int no;
        bool rep = true;    // checagem de repetição de vértice

        while(rep) {
            no = rand() % data.getDimension() + 1; 

            // vai procurar o no aleatorizado no vetor, se não encontra retorna s.end() 
            if (find(s.begin(), s.end(), no) == s.end()) {
                rep = false;
            }
        }
        s.push_back(no);
    }

    s.push_back(1);
    return s;
}

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

    for (int i = 0; i < x; i++) 
        RCL.push_back(CL[i]);

    return RCL;
}

// aqui eu to recebendo como parâmetro o insertionInfo completo do nó selecionado porque eu vou precisar saber
// em qual posição eu insiro o nó na solução
void inserirNaSolucao(Solucao& s, InsertionInfo selecionado) {
    s.sequence.insert(s.sequence.begin() + selecionado.arestaRemovida + 1, selecionado.noInserido);
}

void inserirNaSequencia(Data& data, Solucao &s, int c) {
    s.cost += data.d(s.sequence.back(), c);
    s.sequence.push_back(c);
}

Solucao Construcao(Data& data) {
    // vamos criar uma solução parcial com 3 nós aleatórios e guardar os nós restantes em CL
    Solucao s;

    s.sequence = escolher3NosAleatorios(data);
    vector<int> CL = nosRestantes(data, s.sequence);

    // enquanto houverem nós restantes, vamos randomizar qual nó será inserido na solução um por um
    while(!CL.empty()) {
        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(data, s, CL);

        ordenarEmOrdemCrescente(custoInsercao);

        double alpha = 0;
        while(!alpha) alpha = (double)rand()/RAND_MAX;
        int selecionado = rand()%((int)ceil(alpha * custoInsercao.size()));

        inserirNaSolucao(s, custoInsercao[selecionado]);

        auto pos = find(CL.begin(), CL.end(), custoInsercao[selecionado].noInserido);
        CL.erase(pos); // removendo o nó selecionado do CL
    }

    //calcularCusto(data, &s);
    // talvez ao invés de calcular o custo aqui eu posso só adicionar o custo ao inserir na solucao

    return s;
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

        index = rand()%RCL.size();
        int c = RCL[index];

        inserirNaSequencia(data, s, c);

        r = c;

        CL.erase(CL.begin() + index);
    }

    /*
    Modificações:
    - não usa mais insertation info, nem as primeiras duas funções
    - escolhi os alpha porcento melhores de CL, verificar sse é isso mesmo 
    - verificar tb se o index tá correto na remoção de CL
    - fazendo cálculo de custo durante inserção
    */

    return s;
}