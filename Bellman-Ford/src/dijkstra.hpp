#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <list>
using namespace std;

class Edge {

    private:
        int destiny;
        int value;
        bool visited;

    public:
        Edge(int destiny = 0, int value = 0, bool visited = false);
        ~Edge();

        /**
         * Set the destiny vertex for the edge.
         * @param v_destiny is the id of the destiny vertex 
        */
        void setDestiny(int v_destiny);

        /**
         * Set the value for the current edge.
         * @param e_value is the edge's value 
        */
        void setValue(int e_value);

        /**
         * Get the edge's destiny vertex
         * @return destiny - <int> representing the edge's destiny vertex id. 
        */
        int getDestiny() const;

        /**
         * Get the value for the current edge.
         * @return value - <int> representing the current edge's value.
        */
        int getValue() const;

        /**
         * Mark the edge as visited.
        */
        void visit(bool status = true);

        /**
         * Check if the edge has already been visited.
         * 
         * @return true if it has been visited before and false if not.
        */
        bool isVisited() const;

        /**
         * `Less than` operator overloading
        */
        friend int operator< (const Edge& e1, const Edge& e2);

        /**
         * `Greater than` operator overloading
        */
        friend int operator> (const Edge& e1, const Edge& e2);

};

class Vertex {

    private:
        int id;
        list<Edge*> edges;
        list<Edge*> predecessor_edges;
        bool visited;

    public:
        typedef list<Edge*>::iterator edgeIterator;
        edgeIterator beginEdges();
        edgeIterator endEdges();

        typedef list<Edge*>::iterator predIterator;
        predIterator beginPredecessorEdges();
        predIterator endPredecessorEdges();

        Vertex();
        Vertex(int id, bool visited);
        Vertex(int id, list<Edge*> edges, list<Edge*> predecessor_edges, bool visited);
        ~Vertex();

        /**
         * Set the vertex ID 
         * -> Ex: Vertex 1 set ID = 1.
         * @param vertex is the id of the vertex 
        */
        void setId(int vertex);

        /**
         * Get the vertex ID.
         * @return ID - <int> representing the vertex ID
         * -> Ex: Vertex 1 returns 1. 
        */
        int getId() const;

        /**
         * Insert the edge v1 -> v_destiny with value e_value, where v1 is the current vertex.
         * Besides, insert the edge v1 -> v_destiny in v_destiny to ensure v1 is a predecessor to v_destiny.
         * 
         * @param v_destiny is the destiny vertex ID.
         * @param e_value is the edge's value.
         * @param filter is a filter to insert edge in predecessor_edge list.
        */
        void insert(int v_destiny, int e_value, bool filter);
        
        /**
         * Mark the vertex as visited.
        */
        void visit(bool status = true);

        /**
         * Check if the vertex has already been visited.
         * 
         * @return true if it has been visited before and false if not.
        */
        bool isVisited() const;

};

class Graph {

    protected:
        vector<Vertex*> vertices;
        vector<int> distance_edge; // Distance from source vertex to vertex i
        vector<int> predecessor_vertex; // Source vertex to reach vertex i

    public:
        // Constructor and Destructor
        Graph();
        Graph(size_t n_vertices);
        ~Graph();

        /**
         * In order to insert the edge, the function checks both vertices existence and in case one does not exist
         * the vertex is inserted into the list and then the edge is created.
         * 
         * @param v_source is the source vertex of the edge
         * @param v_destiny is the destiny vertex of the edge
         * @param e_value is the edge's value
        */
        void insert(int v_source, int v_destiny, int e_value);
        
        /**
         * Print the Dijkstra algorithm result 
        */
        void printDijkstra();

        /**
         * Relax the edge connecting vertex to edge destiny.
         * @param vertex The source vertex
         * @param edge The edge that connects the source vertex to the destinated vertex
         * @return boolean representing if the edge was relaxed.
        */
        bool relaxEdge(Vertex* vertex, Edge* edge);

        /**
         * Relax the edge connecting vertex to edge destiny.
         * @param source The source vertex
         * @param destiny The edge's destiny vertex
         * @param edge_value The edge's value for traversing from source to destiny
         * @return boolean representing if the edge was relaxed.
        */
        bool relaxEdge(Vertex* source, Vertex* destiny, int edge_value);

        /**
         * Execute Dijkstra algorithm with initial_vertex as the starting point.
         * 
         * @param initial_vertex is the starting point (vertex) for the algorithm.
        */
        void dijkstra(int initial_vertex);

};