/* Definição de todas as funções necessárias ao algoritmo de Kruskal. 
 *
 * Cada vértice é um conjunto disjunto (nenhum vértice se liga). 
 * O vértice de início é o de menor peso. */

#include <stdio.h>

#include "graph.h"

// Factores = Pesos.
void kruskal(Graph graph, double *factors) {
    if (graph == NULL) return;
}