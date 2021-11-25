/*
Según un peso máximo de una mochila y los elementos (con un peso y valor). 
Se calcula la ganancia óptima.

Autores:
Yusdivia Molina
Daniel Yamamoto
Héctor Noyola

Fecha de modificación: 18/10/2021
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;

// Complejidad O(n)
vector<int> readFile(string file) {
    vector<int> tmp;
    string num;
    fstream f;

    f.open(file);
    
    while (getline(f, num)) {
        tmp.push_back(stoi(num));
    }
    
    f.close();
    return tmp;
}

int main() {
    /*
        NOTA:¡Los nodos deben ir previamente ordenados ascendentemente sino el resultado será incorrecto!
        No podemos hacerle un "sort" porque también debe ir en orden correcto o correspondiente los pesos de cada nodo, aunque los pesos pueden ir en desorden. Es decir, el nodo y su peso deben ir como en "pareja".
        
        Ejemplo:

                    ORDEN                   ORDEN
                    CORRECTO                INCORRECTO

                    ------NODOS------       ------NODOS------
                    1   2   3   4   5       5   1   2   4   3
                    ------PESOS------       ------PESOS------
                    1   1   1   2   3       3   1   1   2   1
    */
    
    vector<int> file = readFile("in.txt");
    Graph* g = new Graph(file);
    int W, result; 

    // Obtenemos el peso máximo de la mochila
    int maxWeight = file.back();

    // Complejidad O(n^3)
    // Iteramos sobre todos los nodos
    for (int i = 0; i < file[0]; i++) {
        g->runMaxDijkstra(g->getNode(i)); // Complejidad O(n^2)
        W = g->maxG(maxWeight); // Complejidad O(n^2)
        // Revisamos cual es mayor
        if (result < W) { result = W; }
    }
    cout << result << "\n";
}