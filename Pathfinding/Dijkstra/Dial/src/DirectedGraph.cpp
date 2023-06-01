//
// Created by korycki on 27.05.2023.
//

#include <iostream>
#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int _v, int _e, int _highest_cost) : V(_v), E(_e), highest_cost(_highest_cost) {
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

std::vector<Vertex *> &DirectedGraph::get_vertices() {
    return vertices;
}

int DirectedGraph::get_v() {
    return V;
}

int DirectedGraph::get_cost(Vertex* u, Vertex* v) {
    for (auto neighbour : u->neighbours) {
        if (neighbour.first->id == v->id) {
            return neighbour.second;
        }
    }
    return -1;
}

int DirectedGraph::get_highest_cost() {
    return highest_cost;
}

void DirectedGraph::print_distances() {
        for (auto v : vertices) {
            std::cout << v->id << "   " << v->dist << std::endl;
        }
}
