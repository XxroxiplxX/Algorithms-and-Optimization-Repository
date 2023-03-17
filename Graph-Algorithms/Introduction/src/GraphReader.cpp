//
// Created by piotrkali on 3/5/23.
//

#include "GraphReader.h"
#include "iostream"
void GraphReader::initialCheck() {
    std::string tmp;
    getline(input, tmp);
    type = types::UNDIRECTED;
    for (auto item : tmp) {
        if (item == 'D') {
            type = types::DIRECTED;
        }
    }
    if (type == DIRECTED) {
        std::cout << "Directed:     ";
    } else {
        std::cout << "Undirected:     ";
    }
    getline(input, tmp);
    v = std::stoi(tmp);
    getline(input, tmp);
    e = std::stoi(tmp);
    std :: cout << "|V| = " << v << "   |E| = " << e << "   \n";
    if (e > 0.9*v*v) {
        std::cout << "Gesty\n";
    }
    state = ANALYZED;
    //std::cout << tmp << "-------\n";
}

Graph* GraphReader::buildGraph() {
    if (state != ANALYZED) {
        input.close();
        input.open(dir);
        initialCheck();
    }
    Graph* g = new Graph(v);
    std::string u;
    std::string v;
    for (int i = 0; i < e; i++) {
        input >> u;
        input >> v;
        //td::cout << u << "  " << v << std::endl;
        g->addEdge(std::stoi(u), std::stoi(v));
    }
    std::cout << "Graph loaded with success\n";
    state = BUILT;
    return g;
}
DirectedGraph* GraphReader::buildDirectedGraph() {
    if (state != ANALYZED) {
        input.close();
        input.open(dir);
        initialCheck();
    }

    DirectedGraph* g = new DirectedGraph(v);

    std::string u;
    std::string v;
    for (int i = 0; i < e; i++) {
        input >> u;
        input >> v;
        //td::cout << u << "  " << v << std::endl;
        g->addEdge(std::stoi(u), std::stoi(v));
    }
    std::cout << "Graph loaded with success\n";

    state = BUILT;
    return g;
}

DirectedGraph *GraphReader::buildTransposedDirectedGraph() {
    if (state != ANALYZED) {
        input.close();
        input.open(dir);
        initialCheck();
    }

    DirectedGraph* g = new DirectedGraph(v);

    std::string u;
    std::string v;
    for (int i = 0; i < e; i++) {
        input >> u;
        input >> v;
        //td::cout << u << "  " << v << std::endl;
        g->addEdge(std::stoi(v), std::stoi(u));
    }
    std::cout << "Graph loaded with success\n";
    state = BUILT;
    return g;
}
