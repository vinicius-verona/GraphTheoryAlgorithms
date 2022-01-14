#include <iostream>
#include "floydwarshall.hpp"

using namespace std;

/**
 * @brief Floyd-Warshall algorithm using the same classes implemented in DFS
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 * @date 28/10/2021
*/
int main() {

    /** 
     * Read input quantities: 
     * - number of vertices, number of edges; 
    */
    int q_vertices, q_edges;
    cin >> q_vertices >> q_edges;

    Graph* graph = new Graph(q_vertices);

    // Read all q_edges edges
    for (int i = 0; i < q_edges; i++){
        int v_source, v_destiny, e_value;
        cin >> v_source >> v_destiny >> e_value;
        graph->insert(v_source, v_destiny, e_value);
    }

    // Generates transitivity_matrix[i][i] so that the Floyd-Warshall can
    // visit the initial vertex even if the edge v0->v0 does not exixts
    for (int i = 0; i < q_vertices; i++){
        graph->insert(i + 1, i + 1, 0);
    }

    // Execute Floyd-Warshall algorithm
    graph->floydwarshall();
    
    // Output vertices distance matrix
    graph->printDistanceMatrix();

    delete graph;
    return 0;
}