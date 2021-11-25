#include "Node.h"

// Complejidad O(1)
Node::Node(int _number) {
	number = _number;
	distance = 1000;
	prev = nullptr;
}

// Complejidad O(1)
int Node::getNumber() { return number; }

// Complejidad O(1)
int Node::getDistance() { return distance; }

// Complejidad O(1)
void Node::setDistance(int newDistance) { distance = newDistance; }