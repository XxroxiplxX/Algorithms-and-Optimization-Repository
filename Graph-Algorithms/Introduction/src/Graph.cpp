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
    if (vertices[id - 1].id == -1) {
        vertices[id - 1].id = id;
    }
    return &vertices[id - 1];
}

void DirectedGraph::addEdge(int u, int v) {
    getVertex(u)->id = u;
    getVertex(v)->id = v;
    getVertex(u)->neighbours.push_back(getVertex(v));
}

void AbstractGraph::addVertex(int _id) {
    vertices.push_back(Vertex(_id));
}

Vertex *DirectedGraph::getVertex(int id) {
    if (vertices[id - 1].id == -1) {
        vertices[id - 1].id = id;
    }
    return &vertices[id - 1];
}

DirectedGraph *DirectedGraph::transpose() {
    auto transposedGraph = new DirectedGraph(size);
    for (int i = 0; i < size; i++) {
        transposedGraph->vertices[i].id = i+1;
        for (auto neigh : vertices[i].neighbours) {

        }
    }
}

