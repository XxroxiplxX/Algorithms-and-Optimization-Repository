//
// Created by piotrkali on 3/5/23.
//

#include "GraphReader.h"
#include "iostream"
void GraphReader::initialCheck() {
    std::string tmp;
    getline(input, tmp);
    std::cout << tmp;
    if (tmp == "D") {
        std::cout << "Directed      ";
        d = 'd';
    } else {
        std::cout << "Undirected      ";
        d = 'u';
    }
    getline(input, tmp);
    v = std::stoi(tmp);
    getline(input, tmp);
    e = std::stoi(tmp);
    std :: cout << "|V| = " << v << "   |E| = " << e << "   ";
    if (e > 0.9*v*v) {
        std::cout << "Gesty\n";
    }
}

Graph GraphReader::buildGraph() {

    Graph g(v);
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
            g.addEdge(u, v);
        } else {
            c++;
        }
    }
    return g;
}
