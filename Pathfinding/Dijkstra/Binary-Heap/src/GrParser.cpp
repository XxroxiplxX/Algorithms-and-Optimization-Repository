//
// Created by korycki on 28.05.2023.
//

#include <cstring>
#include "GrParser.h"

GrParser::GrParser(std::string directory) {

    ifs = std::ifstream(directory, std::ios_base::in);
    if (!ifs) {
        std::cerr << "invalide flename\n";
        exit(1);
    }
}

DirectedGraph* GrParser::build_graph() {

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
                se += _char;
            } else if (e_flag) {
                sv += _char;
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

GrParser::~GrParser() {
    ifs.close();
}
