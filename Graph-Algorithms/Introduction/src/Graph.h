//
// Created by piotrkali on 3/1/23.
//

#ifndef INTRODUCTION_GRAPH_H
#define INTRODUCTION_GRAPH_H
#include <vector>
#include "iostream"
#include <fstream>
enum cyclic {
    CYCLIC,
    ACYCLIC
};
struct Vertex {
    int id = -1;
    char color = 'w';
    int d;
    int f;
    Vertex* parent = nullptr;
    int parent_id = -1;
    std::vector<Vertex*> neighbours;
    Vertex(int _id) : id(_id), color('w'), parent(nullptr){}
    Vertex() {}
    ~Vertex();
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
    AbstractGraph* transformTreeToNormalFormGraph();
    virtual void addEdge(int u, int v) = 0;
    void addVertex(int _id);
    void cleanTree();
    int time = 0;
    Vertex* getVertex(int id);
    std::vector<Vertex> vertices;
    void saveToCSV(std::string modifier);
    void saveTreeToCSV(std::string modifier);
    int tex;
    void wspolny() {}
    ~AbstractGraph();
};
struct Tree {
    Vertex* root;
    Vertex* curr;

};
struct Graph : public AbstractGraph{
public:
    //std::vector<Vertex> vertices;
    int size;
    //int time = 0;
    void addEdge(int u, int v);
    Graph() {}
    Graph(int _size) : size(_size) {
        vertices = std::vector<Vertex>(size, Vertex());
    }
    //void addVertex(int _id);


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
        //std::    << this;
    }
};

struct DirectedGraph : public AbstractGraph{
public:
    //std::vector<Vertex> vertices;
    int size;
    cyclic c;
    void addEdge(int u, int v);
    Graph* transformTreeToNormalFormGraph();
    DirectedGraph(){}
    DirectedGraph(int _size) : size(_size) {
        vertices = std::vector<Vertex>(size, Vertex());
    }
    DirectedGraph* transpose();
};


#endif //INTRODUCTION_GRAPH_H
