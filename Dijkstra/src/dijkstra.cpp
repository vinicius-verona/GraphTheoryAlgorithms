#include "dijkstra.hpp"

// Iterators
Vertex::edgeIterator Vertex::beginEdges(){return this->edges.begin();}
Vertex::edgeIterator Vertex::endEdges(){return this->edges.end();}

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
Graph::Graph(size_t n_vertices):vertices(n_vertices, NULL),distance_edge(n_vertices, INT_MAX),predecessor_vertex(n_vertices,0){}
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

    for (auto e:this->edges){
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

void Graph::dijkstra(int initial_vertex){

    // Visiting vertex list
    list<Vertex*> visiting_vertices;

    // Mark initial vertex as visited
    Vertex* vertex = this->vertices[initial_vertex - 1];
    this->distance_edge[vertex->getId() - 1] = 0;
    visiting_vertices.push_back(vertex);

    // Traverse graph
    while(!visiting_vertices.empty()){

        // Find next vertice to be visited
        int minimum = INT_MAX;
        int minimum_id = 0;
        for (auto v = visiting_vertices.begin(); v != visiting_vertices.end(); ++v){
            if (!(*v)->isVisited() && this->distance_edge[(*v)->getId() - 1] < minimum){
                minimum = this->distance_edge[(*v)->getId() - 1];
                vertex  = (*v);
                minimum_id = vertex->getId();
            }else{
                if(!(*v)->isVisited() && this->distance_edge[(*v)->getId() - 1] == minimum && (*v)->getId() < minimum_id){
                    minimum = this->distance_edge[(*v)->getId() - 1];
                    vertex  = (*v);
                    minimum_id = vertex->getId();
                }
            }
        }
        visiting_vertices.remove(vertex);

        // Check each vertex neighbors
        for (auto e = vertex->beginEdges(); e != vertex->endEdges(); ++e){

            // Auxiliary variables used to facilitate code reading
            Edge* edge = (*e);
            Vertex* neighbor_vertex = this->vertices[edge->getDestiny() - 1];

            // In case neighbor vertex is not visited, insert it to the visiting list
            // In case it has been visited, check if the edge has already been visited.
            if (!neighbor_vertex->isVisited()){
                edge->visit();
                visiting_vertices.push_back(neighbor_vertex);

            } else{
                if (!edge->isVisited()){
                    edge->visit();
                }
            }

            // Update DT and ROT (distance_edge & predecessor_vertex)
            this->relaxEdge(vertex, edge);

        }

        vertex->visit();
    }

}

