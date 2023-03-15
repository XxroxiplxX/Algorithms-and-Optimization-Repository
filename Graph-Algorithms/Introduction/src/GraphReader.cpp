//
// Created by piotrkali on 3/5/23.
//

#include "GraphReader.h"
#include "iostream"
void GraphReader::initialCheck() {
    std::string tmp;
    getline(input, tmp);
    //std::cout << tmp;
    if (tmp == "D") {
        std::cout << "Directed      ";
        //d = 'd';
        type = types::DIRECTED;
    } else {
        std::cout << "Undirected      ";
        //d = 'u';
        type = types::UNDIRECTED;
    }
    getline(input, tmp);
    v = std::stoi(tmp);
    getline(input, tmp);
    e = std::stoi(tmp);
    std :: cout << "|V| = " << v << "   |E| = " << e << "   \n";
    if (e > 0.9*v*v) {
        std::cout << "Gesty\n";
    }
    //std::cout << tmp << "-------\n";
}

Graph* GraphReader::buildGraph() {

    Graph* g = new Graph(v);
    std::string tmp;
    int c = 0;
    while (getline(input, tmp)) {
        if (c > 2) {
            std::string t;
            int u, v;
            bool flag = true;
            for (auto item : tmp) {
                if ((char)item != ' ') {
                    t += item;
                } else {
                    if (flag) {
                        u = std::stoi(t);
                    } else {
                        v = std::stoi(t);
                    }
                    flag = false;
                    t = "";
                }
            }
            g->addEdge(u, v);
        } else {
            c++;
        }
    }
    return g;
}
DirectedGraph* GraphReader::buildDirectedGraph() {
    DirectedGraph* g = new DirectedGraph(v);
    std::string in;


    std::string u;
    std::string v;
    for (int i = 0; i < e; i++) {
        input >> u;
        input >> v;
        //td::cout << u << "  " << v << std::endl;
        g->addEdge(std::stoi(u), std::stoi(v));
    }


    /*
    std::string tmp;
    int b = 0;
    while (getline(input, tmp)) {

            std::cout << tmp <<  std::endl;
            std::string t;
            int _u, _v;
            bool flag = true;
            for (auto item : tmp) {
                if ((char)item != ' ') {
                    t += item;
                } else {
                    if (flag) {
                        _u = std::stoi(t);
                    } else {
                        _v = std::stoi(t);
                    }
                    flag = false;
                    t = "";
                }
            }

            g->addEdge(_u, _v);

    }*/
    return g;
}
