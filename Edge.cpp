#include "Edge.h"

// Complejidad O(1)
Edge::Edge(Node* _first, Node* _second, int _weight) {
	first = _first;
	second = _second;
	weight = _weight;
}