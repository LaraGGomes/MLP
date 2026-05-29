# MLP
Resolução do Problema da Mínima Latência (Minimum Latency Problem) pela abordagem meta-heurística.

---

## Mudanças

* Mudar construção
* Adicionar a estrutura Subsequence
* Adicionar matriz de subsequências
* Adaptação da busca local
* MaxIter = 10, MaxIterILS = min{100,n}
* R = {0.00, 0.01, 0.02, ... , 0.25}

Compilar o programa: 

    g++ -O3 -std=c++17 *.cpp etapas/*.cpp leitor-instancias/src/Data.cpp -o programa.exe

Rodar uma instância:

    ./programa.exe leitor-instancias/instances/nomedainstancia.tsp