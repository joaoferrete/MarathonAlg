#include <bits/stdc++.h>
using namespace std;

class edge{
    public:
    int src, dest, weight;
};

class Graph{
    public:
    int V, E;   // V = numero de vertices, E = numero de arestas
    edge *edgeList; // Lista de arestas
};

Graph* createGraph(int V, int E){
    /* Função que cria um novo grafo */

    Graph *g = new Graph;
    g->V = V;
    g->E = E;
    g->edgeList = new edge[E];
    return g;
}

class subset{ // Classe que representa um conjunto
    public:
    int parent, rank;
};

int find (subset subsets[], int i){
    /* Função que encontra o conjunto que o elemento pertence */

    if (subsets[i].parent != i){
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(subset subsets[], int x, int y){
    /* Função que une dois conjuntos */

    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank){
        subsets[xroot].parent = yroot;
    }
    else if (subsets[xroot].rank > subsets[yroot].rank){
        subsets[yroot].parent = xroot;
    }
    else{
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void *a, const void *b){
    /* Função que compara dois elementos de uma lista de arestas */

    edge *a1 = (edge *) a;
    edge *b1 = (edge *) b;
    return a1->weight > b1->weight;
}

void KruskalMST(Graph * graph){
    /* Função que calcula o MST de um grafo */

    int V = graph->V, E = graph->E;
    edge result[V];
    int e = 0; // e = numero de arestas do MST
    int i = 0; // 

    qsort(graph->edgeList, graph->E, sizeof(graph->edgeList[0]), myComp);

    subset *subsets = new subset[V * sizeof(subset)];

    for (int v = 0; v < V; ++v){
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1){
        edge next_edge = graph->edgeList[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y){
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    cout << "Arestas do MST: " << endl;
    for (i = 0; i < e; ++i){
        cout << result[i].src << " - " << result[i].dest << " : " << result[i].weight << endl;
    }

}

int main(){
    /* Let us create following weighted graph
            10
        0--------1
        | \ |
    6| 5\ |15
        | \ |
        2--------3
            4 */
    int V = 4; // Number of vertices in graph
    int E = 5; // Number of edges in graph
    Graph* graph = createGraph(V, E);
 
    // add edge 0-1
    graph->edgeList[0].src = 0;
    graph->edgeList[0].dest = 1;
    graph->edgeList[0].weight = 10;
 
    // add edge 0-2
    graph->edgeList[1].src = 0;
    graph->edgeList[1].dest = 2;
    graph->edgeList[1].weight = 6;
 
    // add edge 0-3
    graph->edgeList[2].src = 0;
    graph->edgeList[2].dest = 3;
    graph->edgeList[2].weight = 5;
 
    // add edge 1-3
    graph->edgeList[3].src = 1;
    graph->edgeList[3].dest = 3;
    graph->edgeList[3].weight = 15;
 
    // add edge 2-3
    graph->edgeList[4].src = 2;
    graph->edgeList[4].dest = 3;
    graph->edgeList[4].weight = 4;
 
   
    // Function call
    KruskalMST(graph);
 
    return 0;
}
