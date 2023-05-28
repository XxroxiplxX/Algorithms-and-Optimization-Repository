//
// Created by korycki on 28.05.2023.
//
#include "Dijkstra.h"

void dijkstra_to_all_nodes(Vertex* source, DirectedGraph graph) {
    BinaryHeap queue = BinaryHeap(graph.get_v());
    for (auto& v : graph.get_vertices()) {
        v->dist = INT_MAX;
        queue.insert_key(v);
    }
    source->dist = 0;

    while (!queue.is_empty()) {
        auto u = queue.extract_min();

        for (auto& v : u->neighbours) {
            int alt = u->dist + graph.get_cost(u,v.first);
            if (alt < v.first->dist) {
                v.first->dist = alt;
            }
        }
    }
}
int dijkstra_pair_to_pair(Vertex* source, Vertex* destination, DirectedGraph* graph) {

}