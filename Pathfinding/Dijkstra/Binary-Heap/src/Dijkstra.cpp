//
// Created by korycki on 28.05.2023.
//
#include "Dijkstra.h"
void dijkstra_to_all_nodes(Vertex* source, DirectedGraph* graph) {

    BinaryHeap queue = BinaryHeap(graph->get_v());
    for (auto v : graph->get_vertices()) {
        v->dist = ULLONG_MAX;
        queue.insert_key(v);
    }
    queue.decrease_key(source, 0);
    int checked = 0;
    while (!queue.is_empty()) {
        auto u = queue.extract_min();
        checked++;
        for (auto v : u->neighbours) {
            unsigned long long alt = u->dist + v.second;
            if (alt < v.first->dist) {
                queue.decrease_key(v.first, alt);
            }
        }
    }
    //graph->print_distances();
}
int dijkstra_pair_to_pair(Vertex* source, Vertex* destination, DirectedGraph* graph) {

}