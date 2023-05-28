//
// Created by korycki on 27.05.2023.
//

#include <iostream>
#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int _v, int _e) : v(_v), e(_e) {
    vertices = std::vector<Vertex*>(_v, nullptr);
}

void DirectedGraph::add_vertex(int v) {
    vertices[v-1] = new Vertex(v);
}

void DirectedGraph::add_edge(int v1, int v2, int cost) {
    if (vertices[v1-1] == nullptr) {
        add_vertex(v1);
    }
    if (vertices[v2-1] == nullptr) {
        add_vertex(v2);
    }
    get_vertex(v1)->neighbours[get_vertex(v2)] = cost;
}

Vertex *DirectedGraph::get_vertex(int v) {
    return vertices[v-1];
}

void DirectedGraph::print_graph() {
    for (auto vertex : vertices) {
        for (auto neighbour : vertex->neighbours) {
            std::cout << vertex->id << " --> " << neighbour.second << " -- > " << neighbour.first->id << std::endl;
        }
    }

}
