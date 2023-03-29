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
void sortedDFS(DirectedGraph* dg, std::list<std::pair<int,int>> sortedVertices, std::list<std::pair<Vertex*,int>>& heads);
DirectedGraph* stronglyConnectedComponents(DirectedGraph* dg, std::list<std::pair<Vertex*,int>>& heads);
void DFSTreeVisit(Vertex* source, DirectedGraph* dg);
void printForest(DirectedGraph* dg);
void IDFSvisit(Vertex* source, DirectedGraph* dg);
bool isBipartite(AbstractGraph* ag);
void modBFS(AbstractGraph* ag);
//94855167282784
//47239281841184

#endif //INTRODUCTION_ALGORITHMS_H
