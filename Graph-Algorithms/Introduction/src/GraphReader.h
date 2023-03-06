//
// Created by piotrkali on 3/5/23.
//

#ifndef INTRODUCTION_GRAPHREADER_H
#define INTRODUCTION_GRAPHREADER_H

#include "fstream"
#include "iostream"
#include "Graph.h"
class GraphReader {

public:
    std::ifstream input;
    int v;
    int e;
    char d;
    GraphReader(std::string directory) {
        try {
            input.open(directory);
            std::cout << "working on file named: " << directory << std::endl;
        } catch (const std::ifstream::failure& e) {
            std::cout << "Exception opening/reading file";
        }
    }
    Graph buildGraph();
    DirectedGraph buildDirectedGraph();
    ~GraphReader() {
        input.close();
    }
    void initialCheck();
};


#endif //INTRODUCTION_GRAPHREADER_H
