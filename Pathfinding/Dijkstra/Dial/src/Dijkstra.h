//
// Created by korycki on 29.05.2023.
//

#ifndef DIAL_DIJKSTRA_H
#define DIAL_DIJKSTRA_H

#include "DirectedGraph.h"
#include "CircularArray.h"
#include <iostream>
void dijkstra_to_all_nodes(Vertex* source, DirectedGraph graph);
int dijkstra_pair_to_pair(Vertex* source, Vertex* destination, DirectedGraph graph);

#endif //DIAL_DIJKSTRA_H
