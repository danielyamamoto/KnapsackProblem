#include <iostream>
#include <vector>
#include <algorithm> 
#include "Edge.h"

using namespace std;

class Graph {
    public:
        // Constructores
        Graph(vector<Node*> _nodes, vector<Edge*> _edges);
        Graph(vector<int> file);

        Node* getNode(int n);
        void runMaxDijkstra(Node* n);
        int maxG(int weight);

    private:
        vector<Node*> nodes;
        vector<Edge*> edges;

        vector<Node*>getNeighbors(Node* n);
        Node* getMaxDist(vector<Node*> qs);
        void remove(vector<Node*> &qs, Node* q);
        int getLength(Node* u, Node* v);
};