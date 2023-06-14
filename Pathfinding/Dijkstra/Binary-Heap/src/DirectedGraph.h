//
// Created by korycki on 27.05.2023.
//

#ifndef DIAL_DIRECTEDGRAPH_H
#define DIAL_DIRECTEDGRAPH_H
#include <vector>
#include <map>
#include <list>
#include <climits>
struct Vertex {
    int id;
    unsigned long long dist;
    std::map<Vertex*, int> neighbours;

    Vertex(int _id) : id(_id), dist(ULLONG_MAX) {}
    Vertex(int _id, int _dist) : id(_id), dist(_dist) {}
    ~Vertex() {

    }

};
/*
 *
 * +---------------------------------------+
 * |    vertices[0] is vertex with id 1    |
 * +---------------------------------------+
 *
 */
class DirectedGraph {
    int V;
    int E;
    int highest_cost;
    std::vector<Vertex*> vertices;
public:
    std::vector<Vertex*>& get_vertices();
    DirectedGraph() = default;
    DirectedGraph(int _v, int _e);
    void set_highest_cost(int cost);
    void add_edge(int v1, int x1, int cost);
    void add_vertex(int v);
    Vertex* get_vertex(int v);
    int get_cost(Vertex* u, Vertex* v);
    void print_graph();
    int get_v();
    int get_e();
    int get_highest_cost();
    void print_distances();
    ~DirectedGraph();
};


#endif //DIAL_DIRECTEDGRAPH_H
