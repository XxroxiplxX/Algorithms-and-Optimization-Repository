//
// Created by piotrkali on 3/1/23.
//

#ifndef INTRODUCTION_ALGORITHMS_H
#define INTRODUCTION_ALGORITHMS_H
#include "Graph.h"
#include "Logger.h"
#include <list>
#include <stack>
//Logging::Logger* log = new Logging::Logger("algos");
void BFS(Vertex* source);
void DFS(AbstractGraph* g);
void DFSvisit(Vertex* source, AbstractGraph* g);
void printPath(Vertex* source, Vertex* destination);
std::list<std::pair<int, int>> topologicalSort(DirectedGraph* dg);
bool topoDFSVisit(Vertex* source, DirectedGraph* dg, std::list<std::pair<int, int>>& sortedList);
void sortedDFS(DirectedGraph* dg, std::list<std::pair<int,int>> sortedVertices);
DirectedGraph* stronglyConnectedComponents(DirectedGraph* dg);
void DFSTreeVisit(Vertex* source, DirectedGraph* dg);
void printForest(DirectedGraph* dg);
void IDFSvisit(Vertex* source, DirectedGraph* dg);
bool isBipartite(AbstractGraph* ag);
//94855167282784
//47239281841184

#endif //INTRODUCTION_ALGORITHMS_H
