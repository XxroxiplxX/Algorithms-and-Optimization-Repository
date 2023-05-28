//
// Created by korycki on 27.05.2023.
//

#ifndef BINARY_HEAP_DIRECTEDGRAPH_H
#define BINARY_HEAP_DIRECTEDGRAPH_H
#include <vector>
#include <map>
struct Vertex {
    int dist;
    int id;
    std::map<Vertex*, int> neighbours;
    Vertex() = default;
    Vertex(int _id) : id(_id) {}
    Vertex(int _id, int _dist) : id(_id), dist(_dist) {}
};
/*
 *
 * +---------------------------------------+
 * |    vertices[0] is vertex with id 1    |
 * +---------------------------------------+
 *
 */
class DirectedGraph {
    int v;
    int e;
    std::vector<Vertex*> vertices;
public:

    DirectedGraph() = default;
    DirectedGraph(int _v, int _e);
    void add_edge(int v1, int x1, int cost);
    void add_vertex(int v);
    Vertex* get_vertex(int v);
    void print_graph();

};


#endif //BINARY_HEAP_DIRECTEDGRAPH_H
