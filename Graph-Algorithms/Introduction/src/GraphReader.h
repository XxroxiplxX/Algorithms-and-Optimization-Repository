//
// Created by piotrkali on 3/5/23.
//

#ifndef INTRODUCTION_GRAPHREADER_H
#define INTRODUCTION_GRAPHREADER_H

#include "fstream"
#include "iostream"
#include "Graph.h"
enum types {
    DIRECTED,
    UNDIRECTED
};
class GraphReader {

public:
    std::ifstream input;
    int v;
    int e;
    types type;
    std::string dir;
    //char d;
    GraphReader() {}
    GraphReader(std::string directory) {
        dir = directory;
        try {
            input.open(directory);
            input.exceptions(std::ifstream::failbit);
            std::cout << "working on file named: " << directory << std::endl;
        } catch (const std::ifstream::failure& e) {
            //std::cerr << e.what() << '\n';
            std::cerr << "Unknown file\n";
            exit(1);
        }
    }
    Graph* buildGraph();
    DirectedGraph* buildDirectedGraph();
    DirectedGraph* buildTransposedDirectedGraph();
    ~GraphReader() {
        input.close();
    }
    void initialCheck();
};


#endif //INTRODUCTION_GRAPHREADER_H
