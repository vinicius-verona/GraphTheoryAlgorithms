/**
 * @file floydwarshall.cpp
 *
 * @author Vinicius Gabriel Angelozzi Verona de Resende
 * @brief Conforme mencionado em sala, este código utiliza
 * a mesma implementação do algoritmo de DFS, isto é, utilizando
 * matriz para representar a matriz de adjacência.
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#include "floydwarshall.hpp"

// Constructors and Destructors

Graph::Graph(){}
Graph::Graph(size_t n_vertices):transitivity_matrix(n_vertices, vector<Edge*>(n_vertices, NULL)),distance_matrix(n_vertices, vector<int>(n_vertices, INT_MAX)){}
Graph::~Graph(){

    for (int row = 0; row < (int) this->transitivity_matrix.size(); row++){
        for (int column = 0; column < (int) this->transitivity_matrix.size(); column++){
            if (this->transitivity_matrix[row][column] != NULL){
                delete this->transitivity_matrix[row][column];
            }
        }
    }

}

Edge::Edge(int value){this->setValue(value);}
Edge::~Edge(){}


// Insert methods

void Graph::insert(int v_source, int v_destiny, int e_value){
    this->transitivity_matrix[v_source - 1][v_destiny - 1] = new Edge(e_value);
    this->distance_matrix[v_source - 1][v_destiny - 1] = e_value;
}


// Set & Get

void Edge::setValue(int e_value){
    this->value = e_value;
}
int Edge::getValue() const{
    return this->value;
}

// Print Distance Matrix

void Graph::printDistanceMatrix(){

    for (int i = 0; i < (int) this->distance_matrix.size(); i++){
        for (int j = 0; j < (int) this->distance_matrix.size(); j++){
            
            if (this->distance_matrix[i][j] != INT_MAX) cout << this->distance_matrix[i][j];
            else cout << "-";

            if (j < (int) this->distance_matrix.size() - 1) cout << " ";
        
        }
        cout << "\n";
    }

}

// Floyd-Warshall Algorithm

void Graph::floydwarshall(){

    // Traverse graph
    for (int k = 0; k < (int) this->distance_matrix.size(); k++){
        for (int i = 0; i < (int) this->distance_matrix.size(); i++){
            for (int j = 0; j < (int) this->distance_matrix.size(); j++){
                int l_ik = this->distance_matrix[i][k];
                int l_kj = this->distance_matrix[k][j];

                if (l_ik != INT_MAX && l_kj != INT_MAX && this->distance_matrix[i][j] > l_ik + l_kj){
                    this->distance_matrix[i][j] = l_ik + l_kj;
                }
            }
        }
    }

}