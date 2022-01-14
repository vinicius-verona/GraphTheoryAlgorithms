#include "BFS.hpp"

// Iterators
Vertex::edgeIterator Vertex::beginEdges(){return this->edges.begin();}
Vertex::edgeIterator Vertex::endEdges(){return this->edges.end();}


// Constructors and Destructors

Graph::Graph(){}
Graph::Graph(size_t n_vertices):vertices(n_vertices, NULL){}
Graph::~Graph(){

    for (auto i:this->vertices){
        delete i;
    }

}

Vertex::Vertex(){}
Vertex::Vertex(int id, bool visited){

    this->setId(id);
    this->visited = visited;

}
Vertex::Vertex(int id, list<Edge*> edges, bool visited){

    this->setId(id);
    this->edges = edges;
    this->visited = visited;

}
Vertex::~Vertex(){

    for (auto i:this->edges){
        delete i;
    }

}

Edge::Edge(int destiny, int value, bool visited){
    
    this->setDestiny(destiny);
    this->setValue(value);
    this->visited = visited;

}
Edge::~Edge(){}


// Insert methods

void Graph::insert(int v_source, int v_destiny, int e_value){

    if (this->vertices[v_destiny - 1] == NULL){
        this->vertices[v_destiny - 1] = new Vertex(v_destiny, false);
    }
    if (this->vertices[v_source - 1] == NULL){
        this->vertices[v_source - 1]  = new Vertex(v_source, false);
    }

    this->vertices[v_source - 1]->insert(v_destiny, e_value);

}

void Vertex::insert(int v_destiny, int e_value){
    this->edges.push_back(new Edge(v_destiny, e_value));
}

// Set & Get

void Edge::setDestiny(int v_destiny){
    this->destiny = v_destiny;
}
void Edge::setValue(int e_value){
    this->value = e_value;
}
int Edge::getDestiny() const{
    return this->destiny;
}
int Edge::getValue() const{
    return this->value;
}

void Vertex::setId(int vertex){
    this->id = vertex;
}
int Vertex::getId() const{
    return this->id;
}


// Visiting methods

void Edge::visit(bool status){
    this->visited = status;
}
bool Edge::isVisited() const{
    return this->visited;
}

void Vertex::visit(bool status){
    this->visited = status;
}
bool Vertex::isVisited() const{
    return this->visited;
}

// Print Visiting Order

void Graph::printVisitingOrder(){
    for (int i:this->visiting_order){
        cout << i << endl;
    }
}

// BFS Algorithm
void Graph::BFS(int initial_vertex){

    // Visiting vertex list
    list<Vertex*> visiting_vertices;

    // Mark initial vertex as visited
    Vertex* vertex = this->vertices[initial_vertex - 1];
    vertex->visit();
    visiting_vertices.push_back(vertex);


    // Traverse graph
    while(!visiting_vertices.empty()){

        vertex = visiting_vertices.front();
        visiting_vertices.pop_front();
        this->visiting_order.push_back(vertex->getId());

        // Check each vertex neighbors
        for (auto e = vertex->beginEdges(); e != vertex->endEdges(); ++e){
            
            // Auxiliary variables used to facilitate code reading
            Edge* edge = (*e);
            Vertex* neighbor_vertex = this->vertices[edge->getDestiny() - 1];

            // In case neighbor vertex is not visited, visit and insert it to the queue
            // In case it has been visited, check if the edge has already been visited.
            if (!neighbor_vertex->isVisited()){
                edge->visit();
                visiting_vertices.push_back(neighbor_vertex);
                neighbor_vertex->visit();

            } else{
                if (!edge->isVisited()){
                    edge->visit();
                }
            }

        }

    }

}
