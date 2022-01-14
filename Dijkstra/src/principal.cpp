#include <iostream>
#include "dijkstra.hpp"

using namespace std;

/**
 * Description: Dijkstra algorithm
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 * @date 24/10/2021
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

    // Execute Dijkstra algorithm which returns the vertex visiting order
    graph->dijkstra(initial_vertex);
    
    // Output vertices visiting order
    graph->printDijkstra();

    delete graph;
    return 0;
}