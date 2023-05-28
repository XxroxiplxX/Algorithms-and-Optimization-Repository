//
// Created by korycki on 28.05.2023.
//

#ifndef BINARY_HEAP_DIJKSTRA_H
#define BINARY_HEAP_DIJKSTRA_H
#include "BinaryHeap.h"
void dijkstra_to_all_nodes(Vertex* source, DirectedGraph graph);
int dijkstra_pair_to_pair(Vertex* source, Vertex* destination, DirectedGraph graph);
#endif //BINARY_HEAP_DIJKSTRA_H
