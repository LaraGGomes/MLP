# MLP
Resolução do Problema da Mínima Latência (Minimum Latency Problem) pela abordagem meta-heurística.

---

## Planejamento:
Similar ao TSP, vou utilizar a meta-heurística ILS, adicionando a estrutura e matriz de subsequências.

Os passos são:
* Construção
* Busca Local
* Pertubação

## Mudanças

* Mudar construção
* Adicionar a estrutura Subsequence !
* Adicionar matriz de subsequências
* Adaptação da busca local
* MaxIter = 10, MaxIterILS = min{100,n}
* R(?) = {0.00, 0.01, 0.02, ... , 0.25}