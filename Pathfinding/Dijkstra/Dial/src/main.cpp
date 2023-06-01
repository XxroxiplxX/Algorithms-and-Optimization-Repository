#include <iostream>
#include "Parsers.h"
#include "Dijkstra.h"
int main() {
    auto parser = new GraphParser("../../../dataset/ch9-1.1/inputs/Random4-c/Random4-C.0.0.gr");
    auto graph = parser->build_graph();
    /*
    auto graph = new DirectedGraph(6,9, 1);
    graph->add_edge(1,2,0);
    graph->add_edge(2,3,0);
    graph->add_edge(1,3,1);
    graph->add_edge(3,4,1);
    graph->add_edge(4,5,0);
    graph->add_edge(5,3,1);
    graph->add_edge(3,6,1);
    graph->add_edge(6,5,0);
    graph->add_edge(6,1,0);
    graph->add_edge(1,3,1);
    */
    std::cout << "graph built successfully with highest cost: " << graph->get_highest_cost() << std::endl;
    dijkstra_to_all_nodes(graph->get_vertex(9), *graph);
    return 0;
}
