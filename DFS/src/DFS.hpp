#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <vector>
using namespace std;

class Edge {

    private:
        bool exists;
        int value;
        bool visited;

    public:
        Edge(bool exists = true, int value = 0, bool visited = false);
        ~Edge();

        /**
         * Set the value for the current edge.
         * @param e_value is the edge's value 
        */
        void setExists(bool e_exists);

        /**
         * Get the existance of the current edge.
         * @return existance - <bool> representing the current edge's existance in the graph.
        */
        bool getExists() const;
        
        /**
         * Set the value for the current edge.
         * @param e_value is the edge's value 
        */
        void setValue(int e_value);

        /**
         * Get the value for the current edge.
         * @return value - <int> representing the current edge's value.
        */
        int getValue() const;

        /**
         * Mark the edge as visited.
        */
        void visit();

        /**
         * Check if the edge has already been visited.
         * 
         * @return true if it has been visited before and false if not.
        */
        bool isVisited() const;

};

class Graph {

    private:
        vector<vector<Edge*>> transitivity_matrix;
        vector<int> visiting_order;

    public:
        // Constructor and Destructor
        Graph();
        Graph(size_t n_vertices);
        ~Graph();

        /**
         * In order to insert the edge, the function access the transitivity matrix in the given position and creates a new Edge.
         * 
         * @param v_source is the source vertex of the edge
         * @param v_destiny is the destiny vertex of the edge
         * @param e_value is the edge's value
         * @param e_exists is the edge's existance in the graph
        */
        void insert(int v_source, int v_destiny, int e_value, bool e_exists);

        /**
         * Print the graph visiting order for DFS algorithm 
        */
        void printVisitingOrder();

        /**
         * Execute DFS algorithm with initial_vertex as the starting point.
         * In case of a disconnected graph, the returned array contains only
         * the visiting order for the component in which initial_vertex exists.
         * 
         * @param initial_vertex is the starting point (vertex) for the DFS algorithm.
        */
        void DFS(int initial_vertex);

};