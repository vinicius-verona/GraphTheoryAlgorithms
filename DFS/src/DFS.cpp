#include "DFS.hpp"

// Constructors and Destructors
Graph::Graph(){}
Graph::Graph(size_t n_vertices):transitivity_matrix(n_vertices, vector<Edge*>(n_vertices, NULL)){}
Graph::~Graph(){

    for (int row = 0; row < (int) this->transitivity_matrix.size(); row++){
        for (int column = 0; column < (int) this->transitivity_matrix.size(); column++){
            if (this->transitivity_matrix[row][column] != NULL){
                delete transitivity_matrix[row][column];
            }
        }
    }

}

Edge::Edge(bool exists, int value, bool visited){
    
    this->setExists(exists);
    this->setValue(value);
    this->visited = visited;

}
Edge::~Edge(){}


// Insert methods
void Graph::insert(int v_source, int v_destiny, int e_value, bool e_exists){
    if (this->transitivity_matrix[v_source - 1][v_destiny - 1] != NULL){
        return;
    }

    this->transitivity_matrix[v_source - 1][v_destiny - 1] = new Edge(e_exists, e_value);
}


// Set & Get
void Edge::setExists(bool e_exists){
    this->exists = e_exists;
}
bool Edge::getExists() const{
    return this->exists;
}

void Edge::setValue(int e_value){
    this->value = e_value;
}
int Edge::getValue() const{
    return this->value;
}


// Visiting methods
void Edge::visit(){
    this->visited = true;
}
bool Edge::isVisited() const{
    return this->visited;
}

// Print Visiting Order
void Graph::printVisitingOrder(){
    for (int i:this->visiting_order){
        cout << i << endl;
    }
}

// DFS Algorithm

void Graph::DFS(int initial_vertex){

    // Mark initial vertex as visited
    vector<Edge*> edges = this->transitivity_matrix[initial_vertex - 1];
    edges[initial_vertex - 1]->visit();
    this->visiting_order.push_back(initial_vertex);


    // Traverse graph
    for(int e = 0; e < (int) edges.size(); e++){
        if (edges[e] != NULL){
        
            // Auxiliary variables used to facilitate code reading
            Edge* edge = edges[e];

            if (!edge->getExists()){
                continue;
            }
  
            if (!this->transitivity_matrix[e][e]->isVisited()){
                edge->visit();
                this->DFS(e+1);
            } else{
                if (!edge->isVisited()){
                    edge->visit();
                }
            }
        
        }
    }

}