#include "dijkstra.hpp"



class BellmanFord : public Graph{

    private:
        bool negative_cycle;

    public:

        BellmanFord(int q_vertices);
        ~BellmanFord();

        /**
         * Print the Bellman-Ford algorithm result 
        */
        void printBellmanFord();

        /**
         * Execute Bellman-Ford algorithm with initial_vertex as the starting point.
         * In case of a disconnected graph, the array containing the visiting
         * order and result for the algorithm only considers the component in 
         * which initial_vertex exists.
         * 
         * @param initial_vertex is the starting point (vertex) for the algorithm.
        */
        void bellmanford(int initial_vertex);
};