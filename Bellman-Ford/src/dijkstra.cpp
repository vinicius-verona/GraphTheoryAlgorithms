#include "dijkstra.hpp"

// Iterators
Vertex::edgeIterator Vertex::beginEdges(){return this->edges.begin();}
Vertex::edgeIterator Vertex::endEdges(){return this->edges.end();}
Vertex::predIterator Vertex::beginPredecessorEdges(){return this->predecessor_edges.begin();}
Vertex::predIterator Vertex::endPredecessorEdges(){return this->predecessor_edges.end();}


// Overloading operators

int operator< (const Edge& e1, const Edge& e2){
    if (e1.getValue() == e2.getValue()){
        return e1.getDestiny() < e2.getDestiny();
    }
    return e1.getValue() < e2.getValue();
}

int operator> (const Edge& e1, const Edge& e2){
    return !(e1 < e2);
}


// Constructors and Destructors

Graph::Graph(){}
Graph::Graph(size_t n_vertices):vertices(n_vertices, NULL),distance_edge(n_vertices, INT_MAX),predecessor_vertex(n_vertices,INT_MAX){}
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
Vertex::Vertex(int id, list<Edge*> edges, list<Edge*> predecessor_edges, bool visited){

    this->setId(id);
    this->edges = edges;
    this->predecessor_edges = predecessor_edges;
    this->visited = visited;

}
Vertex::~Vertex(){

    for (auto e:this->edges){
        delete e;
    }

    for (auto e:this->predecessor_edges){
        delete e;
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

    this->vertices[v_source - 1]->insert(v_destiny, e_value, true);
    this->vertices[v_destiny - 1]->insert(v_source, e_value, false);
}


void Vertex::insert(int v_destiny, int e_value, bool filter){
    if (filter) {
        this->edges.push_back(new Edge(v_destiny, e_value));
    } else {
        this->predecessor_edges.push_back(new Edge(v_destiny, e_value));
    }
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

// Print Dijkstra Result

void Graph::printDijkstra(){

    for (Vertex* i:this->vertices){
        if (this->predecessor_vertex[i->getId() - 1] == 0){
            continue;
        }
        if (this->distance_edge[i->getId() - 1] == INT_MAX){
            continue;
        }

        cout << i->getId() << " (" << this->distance_edge[i->getId() - 1] << "):";
        
        // Track path
        vector<int> path;
        int source = this->predecessor_vertex[i->getId() - 1];
        path.push_back(i->getId());

        while(true){
            if (this->predecessor_vertex[source - 1] == 0 || this->predecessor_vertex[source - 1] == INT_MAX){
                path.push_back(source);   
                break;
            }

            path.push_back(source);   
            source = this->predecessor_vertex[source - 1];
        }

        // Print path
        for (int j = (int) path.size() - 1; j >= 0; j--){
            cout << " " << path[j];
        }

        cout << "\n";
    }

}

// Dijkstra Algorithm

bool Graph::relaxEdge(Vertex* vertex, Edge* edge){
    int dtv = this->distance_edge[vertex->getId() - 1];
    int dvu = edge->getValue();
    int dtu = this->distance_edge[edge->getDestiny() - 1];

    if ((dtu == INT_MAX && dtv != INT_MAX) || (dtv != INT_MAX && dtv + dvu < dtu)){
        this->distance_edge[edge->getDestiny() - 1] = dtv + dvu;
        this->predecessor_vertex[edge->getDestiny() - 1] = vertex->getId();
        
        return true;
    }
    
    return false;
}

bool Graph::relaxEdge(Vertex* source, Vertex* destiny, int edge_value){
    int dtv = this->distance_edge[source->getId() - 1];
    int dvu = edge_value;
    int dtu = this->distance_edge[destiny->getId() - 1];

    if ((dtu == INT_MAX && dtv != INT_MAX) || (dtv != INT_MAX && dtv + dvu < dtu)){
        this->distance_edge[destiny->getId() - 1] = dtv + dvu;
        this->predecessor_vertex[destiny->getId() - 1] = source->getId();
        
        return true;
    }
    
    return false;
}


void Graph::dijkstra(int initial_vertex){

    // Mark initial vertex as visited
    Vertex* init_vertex = this->vertices[initial_vertex - 1];

    // Traverse graph
    for (Vertex* v:this->vertices){

        if (v->getId() == init_vertex->getId()) continue;

        if (v->isVisited()) continue;
        v->visit();

        // Execute Bellman-ford relaxation checking predecessors
        for (auto e = v->beginPredecessorEdges(); e != v->endPredecessorEdges(); ++e){
            Edge* edge = (*e);
            Vertex* source = this->vertices[edge->getDestiny() - 1];
            
            relaxEdge(source, v, edge->getValue());
        }

    }

}
