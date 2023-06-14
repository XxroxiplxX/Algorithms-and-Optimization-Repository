//
// Created by korycki on 28.05.2023.
//
#include <utility>
#include "Parsers.h"

GraphParser::GraphParser(std::string directory) {
    if (directory.substr(directory.length() - 3, 3) != ".gr") {
        std::cerr << "unknown format in graph\n";
        exit(1);
    }
    open_file(std::move(directory));
}

DirectedGraph* GraphParser::build_graph() {

    std::string line, sv, se, sh;
    bool e_flag = false;
    bool v_flag = false;
    int spaces = 0;
    int c = 0;
    //getline(ifs, line);
    int highest_cost = 0;
    spaces = 0;
    c = 0;
    //getline(ifs, line);
    bool go = true;
    while (go and getline(ifs,line)) {
        if (line[0] == 'p') {
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
            go = false;
        }
    }
    auto graph = new DirectedGraph(std::stoi(sv), std::stoi(se));
    c+=2;
    std::string sv1, sv2, cost;
    while (getline(ifs, line)) {
        if (line[0] == 'a') {
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
            int pot_cost = std::stoi(cost);
            if (pot_cost > highest_cost) {
                highest_cost = pot_cost;
            }
            graph->add_edge(std::stoi(sv1), std::stoi(sv2), pot_cost);
            sv1 = "";
            sv2 = "";
            cost = "";
            c++;
        }
    }
    graph->set_highest_cost(highest_cost);

    ifs.close();
    return graph;
}

GraphParser::~GraphParser() {
    ifs.close();
}

Parser *GraphParser::init(const std::string& directory) {
    return new GraphParser(directory);
}

PairToPairParser::PairToPairParser(std::string directory) {
    if (directory.substr(directory.length() - 4, 4) != ".p2p") {
        std::cerr << "unknown format in pairs\n";
        exit(1);
    }
    open_file(std::move(directory));
}

Parameters* PairToPairParser::build_parameters() {
    std::string line;
    int spaces = 0;
    std::string sv1, sv2;
    auto pairs = new Parameters();
    while (getline(ifs,line)) {
        if (line[0] == 'q') {
            for (auto _char : line) {
                if (_char == ' ') {
                    spaces++;
                } else if (spaces == 1) {
                    sv1 += _char;
                } else if (spaces == 2) {
                    sv2 += _char;
                }
            }
            pairs->get_pairs().push_front(std::pair<int,int>(std::stoi(sv1), std::stoi(sv2)));
            sv1 = "";
            sv2 = "";
            spaces = 0;
        }
    }
    ifs.close();
    return pairs;
}

Parser *PairToPairParser::init(const std::string &directory) {
    return new PairToPairParser(directory);
}

SourceParser::SourceParser(std::string directory) {
    if (directory.substr(directory.length() - 3, 3) != ".ss") {
        std::cout << directory.substr(directory.length() - 3, 2);
        std::cerr << "unknown format in sources\n";
        exit(1);
    }
    open_file(std::move(directory));
}

Parameters* SourceParser::build_parameters() {
    std::string line, sv;
    int spaces = 0;
    auto sources = new Parameters();
    while (getline(ifs,line)) {
        if (line[0] == 's') {
            for (auto _char : line) {
                if (_char == ' ') {
                    spaces++;
                } else if (spaces == 1) {
                    sv += _char;
                }
            }
            //std::cout << sv << std::endl;
            sources->get_sources().push_front(std::stoi(sv));
            sv = "";
            spaces = 0;
        }

    }
    ifs.close();
    return sources;
}

Parser *SourceParser::init(const std::string &directory) {
    return new SourceParser(directory);
}

void Parser::open_file(const std::string& directory) {
    ifs = std::ifstream(directory, std::ios_base::in);
    if (!ifs) {
        std::cerr << "invalide flename\n";
        exit(1);
    }
}

