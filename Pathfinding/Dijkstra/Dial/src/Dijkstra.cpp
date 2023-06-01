//
// Created by korycki on 29.05.2023.
//

#include "Dijkstra.h"
#include "Logger.h"
#include <string>
using namespace Logging;
void dijkstra_to_all_nodes(Vertex* source, DirectedGraph graph) {
    auto l = new Logger("../../logs/dial.log");

    CircularArray<Vertex*> cubes = CircularArray<Vertex*>(graph.get_highest_cost() + 1);
    int checked = 0;
    source->dist = 0;
    cubes.set_element(source, 0);
    while (checked < graph.get_v()) {
        //std::cout << "outter\n";
        for (int i = 0; i < cubes.get_size(); i++) {
            while (!cubes.empty(i)) {
                l->log("current buckets size: ", cubes.get_ful_size());
                //logger->log("cubes total size is: ", cubes.get_ful_size());
                //std::cout << "inner\n";
                auto u = cubes.get_element(i);
                cubes.delete_element(i);
                checked++;
                std :: cout << checked << std::endl;
                for (auto& v : u->neighbours) {
                    int alt = u->dist + v.second;
                    if (v.first->dist == INT_MAX) {
                        v.first->dist = alt;
                        cubes.set_element(v.first, alt);
                    } else if (alt < v.first->dist) {
                        cubes.delete_element(v.first->dist);
                        v.first->dist = alt;
                        cubes.set_element(v.first, alt);
                    }
                }
            }
        }
    }
    delete l;
    //graph.print_distances();
}