/**
 * @file floydwarshall.hpp
 *
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 * @brief Conforme mencionado em sala, este código utiliza
 * a mesma implementação do algoritmo de DFS, isto é, utilizando
 * matriz para representar a matriz de adjacência.
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <vector>
using namespace std;

class Edge {

    private:
        int value;

    public:
        Edge(int value = 0);
        ~Edge();

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

};

class Graph {

    private:
        vector<vector<Edge*>> transitivity_matrix;
        vector<vector<int>> distance_matrix;

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
        */
        void insert(int v_source, int v_destiny, int e_value);
        
        /**
         * Print the graph's distance matrix
        */
        void printDistanceMatrix();

        /**
         * Execute Floyd-Warshall algorithm.
        */
        void floydwarshall();

};