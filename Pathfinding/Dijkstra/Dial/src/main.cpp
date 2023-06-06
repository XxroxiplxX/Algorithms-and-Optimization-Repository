#include <iostream>
#include "Parsers.h"
#include "Dijkstra.h"
int main() {
    auto parser = new GraphParser("../../../dataset/ch9-1.1/inputs/Square-C/Square-C.14.0.gr");
    auto graph = parser->build_graph();

    std::cout << "graph built successfully with highest cost: " << graph->get_highest_cost() << std::endl;

    dijkstra_to_all_nodes(graph->get_vertex(951313), *graph);
    delete parser;
    delete graph;





    return 0;
}
