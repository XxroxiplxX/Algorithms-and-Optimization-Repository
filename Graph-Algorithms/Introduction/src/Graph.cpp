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

Vertex *AbstractGraph::getVertex(int id) {
    if (id == 0 or id > vertices.size())
        std::cout << "blad";
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

void AbstractGraph::saveToCSV(std::string modifier) {
        std::ofstream outdata_v;
        std::ofstream outdata_e;
        outdata_v.open("/tmp/graph_v" + modifier + ".csv");
        outdata_e.open("/tmp/graph_e" + modifier + ".csv");
        outdata_v << "v" << ";" << std::endl;
        outdata_e << "e1" << ";" << "e2" << std::endl;
        for (auto vertex : vertices) {
            outdata_v << vertex.id << ";" << std::endl;
        }
        outdata_v.close();
        for (auto vertex : vertices) {
            for (auto neighbour : vertex.neighbours) {
                outdata_e << vertex.id << ";" << neighbour->id << std::endl;
            }
        }
        outdata_e.close();
}

void AbstractGraph::saveTreeToCSV(std::string modifier) {
    std::ofstream outdata_v;
    std::ofstream outdata_e;
    outdata_v.open("/tmp/graph_v" + modifier + ".csv");
    outdata_e.open("/tmp/graph_e" + modifier + ".csv");
    outdata_v << "v" << ";" << std::endl;
    outdata_e << "e1" << ";" << "e2" << std::endl;
    for (auto vertex : vertices) {
        outdata_v << vertex.id << ";" << std::endl;
    }
    outdata_v.close();
    for (auto vertex : vertices) {
        if (vertex.parent_id != -1) {
            //std::cout << vertex.id << ";" << vertex.parent_id << std::endl;
            outdata_e << vertex.id << ";" << vertex.parent_id << std::endl;
        }
    }
}

void AbstractGraph::cleanTree() {
    for (auto& vertex : vertices) {
        vertex.parent_id = -1;
        vertex.color = 'w';
    }
}

AbstractGraph::~AbstractGraph() {

}

Graph* DirectedGraph::transformTreeToNormalFormGraph() {
    auto normalTree = new Graph(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        normalTree->vertices[i].id = vertices[i].id;
        if (vertices[i].parent_id != -1) {
            normalTree->addEdge(vertices[i].id, vertices[i].parent_id);
        }
    }
    return normalTree;
}


DirectedGraph *DirectedGraph::transpose() {
    auto transposedGraph = new DirectedGraph(size);
    for (auto vertex : vertices) {
        for (auto neigh : vertex.neighbours) {
            transposedGraph->addEdge(neigh->id, vertex.id);
        }
    }
    return transposedGraph;
}

Vertex::~Vertex() {

}
