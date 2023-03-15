//
// Created by piotrkali on 3/1/23.
//

#ifndef INTRODUCTION_GRAPH_H
#define INTRODUCTION_GRAPH_H
#include <vector>
#include "iostream"
struct Vertex {
    int id = -1;
    char color = 'w';
    int d;
    int f;
    Vertex* parent = nullptr;
    std::vector<Vertex*> neighbours;
    Vertex(int _id) : id(_id), color('w'){}
    Vertex() {}
    /*
    std::string color() {
        if ((long) this % 2) {
            return "nieparzysty";
        } else {
            return "parzysty";
        }
    }*/

};
struct AbstractGraph {
    virtual void addEdge(int u, int v) = 0;
    void addVertex(int _id);
    std::vector<Vertex> vertices;
    int tex;
    void wspolny() {}
};
struct Tree {
    Vertex* root;
    Vertex* curr;

};
struct Graph : public AbstractGraph{
public:
    //std::vector<Vertex> vertices;
    int size;
    int time = 0;
    void addEdge(int u, int v);
    Graph() {}
    Graph(int _size) : size(_size) {
        vertices = std::vector<Vertex>(size, Vertex());
    }
    //void addVertex(int _id);
    Vertex* getVertex(int id);

    /*
    void addVertex(int id, bool color){
        Vertex* v = new Vertex();

        std::vector<Vertex*> ptrs;
        if (((long) v  >> 4 )% 2 != color) {

            do {
                ptrs.push_back(v);
                v = new Vertex();
            } while (((long) v  >> 4)% 2 != color);

            v->id = id;
            vertices.push_back(v);
        } else {
            v->id = id;
            vertices.push_back(v);
        }
        for (int i = 0; i < ptrs.size(); i++) {
            delete ptrs[i];
        }
    }*/
    void show() {
        std::cout << this;
    }
};

struct DirectedGraph : public AbstractGraph{
public:
    //std::vector<Vertex> vertices;
    int size;
    void addEdge(int u, int v);
    Vertex* getVertex(int id);
    DirectedGraph(){}
    DirectedGraph(int _size) : size(_size) {
        vertices = std::vector<Vertex>(size, Vertex());
    }
};


#endif //INTRODUCTION_GRAPH_H
