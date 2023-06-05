//
// Created by korycki on 29.05.2023.
//

#include "Dijkstra.h"
#include "Logger.h"
#include <string>
using namespace Logging;
void dijkstra_to_all_nodes(Vertex* source, DirectedGraph& graph) {
    auto l = new Logger("../../logs/dial.log");
    std::cout << graph.get_v() << std::endl;
    //list of vertices ids
    CircularArray<int>* cubes = new CircularArray<int>(graph.get_highest_cost() + 1);
    int checked = 0;
    source->dist = 0;
    cubes->set_element(source->id, 0);
    while (cubes->get_full_size() != 0) {
        l->log("checked: ", cubes->get_full_size());
        for (int i = 0; i < cubes->get_size(); i++) {

            while (!cubes->empty(i)) {

                auto u = graph.get_vertex(cubes->get_element(i));
                cubes->delete_element(i, u->id);
                checked++;

                for (auto& v : u->neighbours) {

                    int alt = u->dist + v.second;
                    if (v.first->dist == INT_MAX) {

                        v.first->dist = alt;
                        cubes->set_element(v.first->id, alt);
                    } else if (alt < v.first->dist) {

                        cubes->delete_element(v.first->dist, v.first->id);
                        v.first->dist = alt;
                        cubes->set_element(v.first->id, alt);
                    }
                }
            }
        }
    }
    delete l;
    delete cubes;
    graph.print_distances();
}