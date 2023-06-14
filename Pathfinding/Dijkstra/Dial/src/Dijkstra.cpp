//
// Created by korycki on 29.05.2023.
//

#include "Dijkstra.h"

#include <string>

void dijkstra_to_all_nodes(Vertex* source, DirectedGraph* graph) {

    //auto l = new Logger("../../logs/dial.log");
    //std::cout << graph.get_v() << std::endl;
    //list of vertices ids
    CircularArray* buckets = new CircularArray(graph->get_highest_cost() + 1, *graph);
    int checked = 0;
    source->dist = 0;
    unsigned long long zero = 0;
    buckets->set_element(source->id, zero);
    while (buckets->get_full_size() != 0) {
        //l->log("checked: ", buckets->get_full_size());
        for (unsigned long long i = 0; i < buckets->get_size(); i++) {

            while (!buckets->empty(i)) {

                auto u = graph->get_vertex(buckets->get_element(i));
                buckets->delete_element(i, u->id);
                checked++;

                for (auto& v : u->neighbours) {
                    unsigned long long alt = u->dist + v.second;
                    if (v.first->dist == ULLONG_MAX) {
                        v.first->dist = alt;
                        //std::cout << "a" << alt << std::endl;
                        buckets->set_element(v.first->id, alt);
                    } else if (alt < v.first->dist) {

                        buckets->delete_element(v.first->dist, v.first->id);
                        v.first->dist = alt;
                        //std::cout << "b" << alt << std::endl;
                        buckets->set_element(v.first->id, alt);
                    }
                }
            }
        }
    }
    //delete l;
    delete buckets;
    //graph->print_distances();
}
