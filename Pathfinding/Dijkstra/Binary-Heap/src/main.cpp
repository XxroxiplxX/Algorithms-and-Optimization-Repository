#include <iostream>
#include "Parsers.h"
#include "Dijkstra.h"
int main() {


    auto parser = new GraphParser("../../../dataset/ch9-1.1/inputs/Random4-c/Random4-C.0.0.gr");
    auto graph = parser->build_graph();

    dijkstra_to_all_nodes(graph->get_vertex(8609), *graph);
    return 0;
}
