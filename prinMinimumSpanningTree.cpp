#include <bits/stdc++.h>
using namespace std;

//Numero de vertices
#define V 5

int minKey(int key[], bool mstSet[]){
    /* Função que retorna o indice do elemento com menor key */

    //inicializando o menor valor como infinito
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[], int graph[V][V]){
    /* Função que imprime o MST */

    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << "\n";
}

void primMST(int graph[V][V]){
    /* Implementação do algoritmo de PRIN para
    encontrar a árvore geradora mínima */

    int parent[V]; //parent[i] = pai do vertice i

    int key[V]; //key[i] = custo do vertice i

    bool mstSet[V]; //mstSet[i] = true se o vertice i está no MST

    //inicializando os vetores
    for(int i = 0; i < V; i++){
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    //inicializando o primeiro vertice como 0
    key[0] = 0;
    parent[0] = -1;

    //enquanto o MST não estiver completo
    for(int count = 0; count < V-1; ++count){
        //encontra o vertice com menor key
        int u = minKey(key, mstSet);

        //marca o vertice como visitado
        mstSet[u] = true;

        //atualiza o custo do vertice
        for(int v = 0; v < V; v++){
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    //imprime o MST
    printMST(parent, graph);
}

int main()
{
    /* Let us create the following graph
        2 3
    (0)--(1)--(2)
    | / \ |
    6| 8/ \5 |7
    | / \ |
    (3)-------(4)
            9     */
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };
 
    // Print the solution
    primMST(graph);
 
    return 0;
}
