#include "Graph.h"

// Complejidad O(1)
Graph::Graph(vector<Node*> _nodes, vector<Edge*> _edges) {
	nodes = _nodes;
	edges = _edges;
}

// Liga del push_back: https://www.hackerearth.com/practice/notes/standard-template-library/
// Complejidad O(n^2)
Graph::Graph(vector<int> file) {
	for (int i = 1; i <= file[0]; i++) {
		nodes.push_back(new Node(file[i]));
	}
	// Agregamos el nodo final 'X'
	Node* X = new Node(0);
	nodes.push_back(X); // Complejidad O(1)
	// índice de los pesos
	int index = file[0] + 1;
	for (int i = 0; i < file[0]; i++) {
		for (int j = i + 1; j <= file[0]; j++) {
			edges.push_back(new Edge(nodes[i], nodes[j], file[index])); // Complejidad O(1)
		}
		index++;
	}
}

// Complejidad O(n)
vector<Node*> Graph::getNeighbors(Node* n) {
	vector<Node*> neighbors;
	for (vector<Edge*>::iterator ei = edges.begin(); ei != edges.end(); ++ei) {
		if ((*ei)->first == n) {
			neighbors.push_back((*ei)->second); // Complejidad O(1)
		} else if ((*ei)->second == n) {
			neighbors.push_back((*ei)->first); // Complejidad O(1)
		}
	}
	return neighbors;
}

// Complejidad O(1)
Node* Graph::getNode(int n) {
	return nodes[n];
}

// Liga del find: https://www.geeksforgeeks.org/set-find-function-in-c-stl/
// Complejidad O(n^2)
void Graph::runMaxDijkstra(Node* n) {
	vector<Node*> q;
    // Se recorren todos los nodos
	for (vector<Node*>::iterator ni = nodes.begin(); ni != nodes.end(); ++ni) {
		(*ni)->setDistance(-1);
        //La distancia del nodo inicial es 0
		if ((*ni) == n) { (*ni)->setDistance(0); }
		(*ni)->prev = nullptr;
		q.push_back(*ni); // Complejidad O(1)
	}

	while (!q.empty()) {
		Node* u = getMaxDist(q);
        
		remove(q, u); // Complejidad O(n)
		vector<Node*> neighU = getNeighbors(u);
        if (neighU.size() == 0) break;

        // Se recorren todos los vecinos
        for (vector<Node*>::iterator v = neighU.begin(); v != neighU.end(); ++v) {
            // Still in q
            if (find(q.begin(), q.end(), (*v)) != q.end()) { // Complejidad O(log n)
                int alt = u->distance + getLength(u, *v); // Complejidad O(n)
                if (alt > (*v)->getDistance()) {
                    (*v)->setDistance(alt);
                    (*v)->prev = u;
                }
            }
		}
	}
}

// Complejidad O(n^2)
int Graph::maxG(int weight) {
    int newMax = 0, maxLocal, globalFinal;

    // Se recorren todos los nodos
    for (vector<Node*>::iterator ni = nodes.begin(); ni != nodes.end(); ni++) {
        maxLocal = newMax;
        newMax = (*ni)->getNumber();

        // Si la distancia del nodo es menor al dado
        if ((*ni)->getDistance() <= weight) {            
          
            // Hacemos una vuelta hacia atrás hasta que sea el último nodo y vamos sumando sus valores
            int index = ((*ni)->getNumber())-1;
            while(index < nodes.size() && nodes[index]->prev != nullptr ){
                newMax += nodes[index]->prev->getNumber();
                index++;
            }

            //Le damos al valor final el valor de newMax
            if (maxLocal < newMax) { globalFinal = newMax; }
        }
    }
    return globalFinal;
}

// Complejidad O(n)
Node* Graph::getMaxDist(vector<Node*> qs) {
	Node* maxQ = nullptr;
	int minDist = -1;
	for (vector<Node*>::iterator ni = qs.begin(); ni != qs.end(); ++ni) {
		int d = (*ni)->getDistance();
		if (d >= minDist) {
			maxQ = (*ni);
			minDist = d;
		}
	}
	return maxQ;
}

// Liga del erase: https://newbedev.com/time-complexity-of-removing-items-in-vectors-and-deque
// Complejidad O(n)
void Graph::remove(vector<Node*> &qs, Node* q) {
	for (vector<Node*>::iterator ni = qs.begin(); ni != qs.end(); ++ni) {
		if ((*ni) == q) {
			qs.erase(ni); // Complejidad O(n)
			break;
		}
	}
}

// Complejidad O(n)
int Graph::getLength(Node* u, Node* v) {
	int result = -1;
	for (vector<Edge*>::iterator ei = edges.begin(); ei != edges.end(); ++ei) {
		bool a = (*ei)->first == u && (*ei)->second == v;
		bool b = (*ei)->first == v && (*ei)->second == u;
		if (a || b) { return (*ei)->weight; }
	}
	return result;
}