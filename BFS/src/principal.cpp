#include <iostream>
#include "BFS.hpp"

using namespace std;

/**
 * Description: BFS algorithm
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 * @date 01/10/2021
*/
int main() {

    /** 
     * Read input quantities: 
     * - number of vertices, number of edges; 
     * - graph direction binary & initial vertex
    */
    int q_vertices, q_edges, directed, initial_vertex;
    cin >> q_vertices >> q_edges >> directed >> initial_vertex;

    Graph* graph = new Graph(q_vertices);

    // Read all q_edges edges
    for (int i = 0; i < q_edges; i++){
        int v_source, v_destiny, e_value;
        cin >> v_source >> v_destiny >> e_value;
        graph->insert(v_source, v_destiny, e_value);

        // In case the the graph is an undirect graph, insert the returning edge
        if (directed == 0) {
            graph->insert(v_destiny, v_source, e_value);
        }
    }

    // Execute BFS algorithm which returns the vertex visiting order
    graph->BFS(initial_vertex);
    
    // Output vertices visiting order
    graph->printVisitingOrder();

    delete graph;
    return 0;
}