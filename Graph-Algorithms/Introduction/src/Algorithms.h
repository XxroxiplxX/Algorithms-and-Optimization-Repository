//
// Created by piotrkali on 3/1/23.
//

#ifndef INTRODUCTION_ALGORITHMS_H
#define INTRODUCTION_ALGORITHMS_H
#include "Graph.h"
#include "Logger.h"
//Logging::Logger* log = new Logging::Logger("algos");
void BFS(Graph graph, Vertex* source);
void DFS(Graph graph, Vertex* source);
void printPath(Vertex* source, Vertex* destination);
//94855167282784
//47239281841184

#endif //INTRODUCTION_ALGORITHMS_H
