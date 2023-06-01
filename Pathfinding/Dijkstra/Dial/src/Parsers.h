//
// Created by korycki on 28.05.2023.
//

#ifndef DIAL_PARSERS_H
#define DIAL_PARSERS_H
#include <iostream>
#include <fstream>
#include <list>
#include "DirectedGraph.h"
class Parser {
protected:
    std::ifstream ifs;
    void open_file(std::string directory);
};
class GraphParser : public Parser{
    int v;
    int e;
public:
    explicit GraphParser(std::string directory);
    GraphParser() = default;
    DirectedGraph* build_graph();
    ~GraphParser();
};

class PairToPairParser : public Parser {
public:
    PairToPairParser() = default;
    explicit PairToPairParser(std::string directory);
    std::list<std::pair<int,int>> build_parameters();
};

class SourceParser : public Parser {
public:
    SourceParser() = default;
    explicit SourceParser(std::string directory);
    std::list<int> build_parameters();
};

#endif //DIAL_PARSERS_H
