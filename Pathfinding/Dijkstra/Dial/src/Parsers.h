//
// Created by korycki on 28.05.2023.
//

#ifndef DIAL_PARSERS_H
#define DIAL_PARSERS_H
#include <iostream>
#include <fstream>
#include <list>
#include <cstring>
#include "DirectedGraph.h"


class Parameters {
    std::list<int> sources;
    std::list<std::pair<int,int>> pairs;
public:
    ~Parameters() = default;
    std::list<int>& get_sources() {
        return sources;
    }
    std::list<std::pair<int,int>>& get_pairs() {
        return pairs;
    }
};



class Parser {
protected:
    std::ifstream ifs;
    void open_file(const std::string& directory);
    virtual Parser* init(const std::string& directory) = 0;
    virtual ~Parser() = default;
};
class GraphParser : public Parser{
    int v{};
    int e{};
public:
    explicit GraphParser(std::string directory);
    GraphParser() = default;
    DirectedGraph* build_graph();
    ~GraphParser();
    Parser* init(const std::string& directory) override;
};

class PairToPairParser : public Parser {
public:
    PairToPairParser() = default;
    explicit PairToPairParser(std::string directory);
    Parameters* build_parameters();
    Parser* init(const std::string& directory) override;
};

class SourceParser : public Parser {
public:
    SourceParser() = default;
    explicit SourceParser(std::string directory);
    Parameters* build_parameters();
    Parser* init(const std::string& directory) override;
};




#endif //DIAL_PARSERS_H
