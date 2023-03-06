//
// Created by piotrkali on 3/1/23.
//

#include "Graph.h"

void Graph::addEdge(int u, int v) {
    getVertex(u)->id = u;
    getVertex(v)->id = v;
    getVertex(u)->neighbours.push_back(getVertex(v));
    getVertex(v)->neighbours.push_back(getVertex(u));
}

Vertex *Graph::getVertex(int id) {
    return &vertices[id - 1];
}

void DirectedGraph::addEdge(int u, int v) {
    getVertex(u)->id = u;
    getVertex(v)->id = v;
    getVertex(u)->neighbours.push_back(getVertex(v));
}

void Graph::addVertex(int _id) {
    vertices.push_back(Vertex(_id));
}

Vertex *DirectedGraph::getVertex(int id) {
    return &vertices[id - 1];
}

