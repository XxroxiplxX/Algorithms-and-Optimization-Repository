#include <iostream>
#include "Graph.h"
#include "GraphReader.h"
#include "Algorithms.h"
int main(int argc, char** argv) {
   /*GraphReader* gr = new GraphReader(argv[1]);
   gr->initialCheck();
   if (gr->d == 'u') {
       Graph g = gr->buildGraph();
   }
   delete gr;*/
    std::cout << "argv[1]";

   Graph g;

   for (int i = 1; i < 9; i++) {
       g.addVertex(i);
       std::cout << "start";
   }
    std::cout << "start";
   g.addEdge(1,2);

   g.addEdge(3,2);
    g.addEdge(1,4);
    g.addEdge(4,5);
    g.addEdge(4,6);
    g.addEdge(5,6);
    g.addEdge(5,8);
    g.addEdge(6,8);
    g.addEdge(6,7);
    std::cout << "start";
    BFS(g, g.getVertex(1));
    printPath(g.getVertex(1), g.getVertex(6));
   return 0;
} //73,832
