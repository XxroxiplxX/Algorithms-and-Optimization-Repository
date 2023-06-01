#include <iostream>
#include "Parsers.h"
#include "Dijkstra.h"
int main() {


    auto parser = new GraphParser("../../../dataset/ch9-1.1/inputs/Random4-n/Random4-n.10.0.gr");
    auto graph = parser->build_graph();

    dijkstra_to_all_nodes(graph->get_vertex(9), graph);
    return 0;
}
