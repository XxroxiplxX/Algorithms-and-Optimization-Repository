//
// Created by korycki on 28.05.2023.
//
#include <utility>
#include "Parsers.h"

GraphParser::GraphParser(std::string directory) {
    open_file(std::move(directory));
}

DirectedGraph* GraphParser::build_graph() {

    std::string line, sv, se;
    bool e_flag = false;
    bool v_flag = false;
    int spaces = 0;
    int c = 0;
    getline(ifs, line);
    getline(ifs, line);
    for (auto _char : line) {
        if (_char == ' ') {
            spaces++;
        } else {
            if (spaces == 2) {
                v_flag = true;
            }
            if (spaces == 3) {
                e_flag = true;
                v_flag = false;
            }
            if (v_flag) {
                sv += _char;
            } else if (e_flag) {
                se += _char;
            }
        }

    }
    auto graph = new DirectedGraph(std::stoi(sv), std::stoi(se));
    c+=2;
    std::string sv1, sv2, cost;
    while (getline(ifs, line)) {
        spaces = 0;
        for (auto _char : line) {
            if (_char == ' ') {
                spaces++;
            } else if (spaces == 1) {
                sv1 += _char;
            } else if (spaces == 2) {
                sv2 += _char;
            } else if (spaces == 3) {
                cost += _char;
            }
        }
        graph->add_edge(std::stoi(sv1), std::stoi(sv2), std::stoi(cost));
        sv1 = "";
        sv2 = "";
        cost = "";
        c++;
    }

    ifs.close();
    return graph;
}

GraphParser::~GraphParser() {
    ifs.close();
}

PairToPairParser::PairToPairParser(std::string directory) {
    open_file(std::move(directory));
}

std::list<std::pair<int, int>> PairToPairParser::build_parameters() {
    std::string line;
    getline(ifs, line);
    int spaces = 0;
    std::string sv1, sv2;
    std::list<std::pair<int,int>> params;
    while (getline(ifs,line)) {
        for (auto _char : line) {
            if (_char == ' ') {
                spaces++;
            } else if (spaces == 1) {
                sv1 += _char;
            } else if (spaces == 2) {
                sv2 += _char;
            }
        }
        params.push_front(std::pair<int,int>(std::stoi(sv1), std::stoi(sv2)));
        sv1 = "";
        sv2 = "";
    }
    ifs.close();
    return std::list<std::pair<int, int>>();
}

SourceParser::SourceParser(std::string directory) {
    open_file(std::move(directory));
}

std::list<int> SourceParser::build_parameters() {
    std::string line, sv;
    int spaces = 0;
    std::list<int> sources;
    while (getline(ifs,line)) {
        if (line[0] == 's') {
            for (auto _char : line) {
                if (_char == ' ') {
                    spaces++;
                } else if (spaces == 1) {
                    sv += _char;
                }
            }
            sources.push_front(std::stoi(sv));
            sv = "";
        }

    }
    ifs.close();
    return std::list<int>();
}

void Parser::open_file(std::string directory) {
    ifs = std::ifstream(directory, std::ios_base::in);
    if (!ifs) {
        std::cerr << "invalide flename\n";
        exit(1);
    }
}
