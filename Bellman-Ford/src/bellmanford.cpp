#include "bellmanford.hpp"

BellmanFord::BellmanFord(int q_vertices):Graph(q_vertices){
    this->negative_cycle = false;
}
BellmanFord::~BellmanFord(){}

void BellmanFord::printBellmanFord(){
    if (this->negative_cycle) cout << "ERRO: CICLO DE CUSTO NEGATIVO!" << endl;
    else this->printDijkstra();
}

void BellmanFord::bellmanford(int initial_vertex){

    this->distance_edge[initial_vertex - 1] = 0;
    this->predecessor_vertex[initial_vertex - 1] = 0;
    int q_vertices = (int) this->vertices.size();
    bool altered = false;
    int counter = 0;

    for(int i = 1; i <= q_vertices - 1; i++){
        counter ++;
        
        altered = false;
        vector<int>original_predecessor_vertex = this->predecessor_vertex;
        vector<int>original_distance_edge = this->distance_edge;

        this->dijkstra(initial_vertex);

        // Uncheck visited vertices
        for (Vertex* v : this->vertices){
            v->visit(false);
            bool diff_source   = this->predecessor_vertex[v->getId() - 1] != original_predecessor_vertex[v->getId() - 1];
            bool diff_distance = this->distance_edge[v->getId() - 1] != original_distance_edge[v->getId() - 1];
            if (diff_source || diff_distance) altered = true;
        }

        // Check if dijkstra altered any predecessor or distance
        if(!altered) break;
        if(altered && i == q_vertices - 1) this->negative_cycle = true;

    }

}