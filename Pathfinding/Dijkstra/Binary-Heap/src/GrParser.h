//
// Created by korycki on 28.05.2023.
//

#ifndef BINARY_HEAP_GRPARSER_H
#define BINARY_HEAP_GRPARSER_H
#include <iostream>
#include <fstream>
#include "DirectedGraph.h"
class GrParser {
    std::ifstream ifs;
    int v;
    int e;
public:
    GrParser(std::string directory);
    GrParser() = default;
    DirectedGraph* build_graph();
    ~GrParser();
};


#endif //BINARY_HEAP_GRPARSER_H
