#include <iostream>
#include "Graph.h"
#include "GraphReader.h"
#include "Algorithms.h"
#include <stack>
#include <cstdlib>
enum flags {
    ONE,
    TWO,
    THREE,
    FOUR,
    TREE,
    FILEN,
    NUMBER,
    NONE
};
int main(int argc, char** argv) {
    bool readfile = false;
    std::string directory;
    std::string filename;
    std::stack<flags> fs;
    flags f1;
    flags f2;
    flags f3;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'f' :
                    fs.push(flags::FILEN);
                    break;
                case 'n' :
                    fs.push(flags::NUMBER);
                    break;
                case 't' :
                    f3 = flags::TREE;
                    break;
                default:
                    std::cerr << "unknown flag" << std::endl;
                    exit(1);
            }

        } else {
            flags flag = fs.top();
            switch (flag) {
                case flags::FILEN:
                    filename = std::string(argv[i]);
                    break;
                case flags::NUMBER:
                    switch (argv[i][0]) {
                        case '1' :
                            f2 = flags::ONE;
                            directory = "../../resources/";
                            break;
                        case '2' :
                            f2 = flags::TWO;
                            directory = "../../resources/2/";
                            break;
                        case '3' :
                            f2 = flags::THREE;
                            directory = "../../resources/3/";
                            break;
                        case '4' :
                            f2 = flags::FOUR;
                            directory = "../../resources/4/";
                            break;
                        default :
                            std::cerr << "unknown condition\n";
                            exit(1);
                    }

                    break;
                case flags::TREE :
                    break;
            }

        }
    }
    switch (f2) {
        case ONE: {

            auto g = new Graph();
            for (int i = 1; i < 13; i++) {
                g->addVertex(i);
            }
            g->addEdge(1,2);
            g->addEdge(3,4);
            g->addEdge(1,5);
            g->addEdge(5,9);
            g->addEdge(5,10);
            g->addEdge(9,10);
            g->addEdge(3,7);
            g->addEdge(3,8);
            g->addEdge(7,8);
            g->addEdge(4,8);
            g->addEdge(8,12);
            g->addEdge(8,11);
            g->addEdge(7,11);
            g->saveToCSV("u");
            std::cout << "running DFS...\n";
            DFS(g);
            g->saveTreeToCSV("tDFS");
            g->cleanTree();
            std::cout << "running BFS...\n";
            BFS(g->getVertex(7));
            g->saveTreeToCSV("tBFS");
            delete g;
            if (f3 == TREE) {
                system("python ../../src/printer.py U");
            }
            auto dg = new DirectedGraph();
            for (int i = 1; i < 9; i++) {
                dg->addVertex(i);
            }
            dg->addEdge(1,2);
            dg->addEdge(1,3);
            dg->addEdge(3,4);
            dg->addEdge(4,1);
            dg->addEdge(1,6);
            dg->addEdge(2,5);
            dg->addEdge(5,6);
            dg->addEdge(4,8);
            dg->addEdge(8,7);
            dg->addEdge(6,7);
            dg->addEdge(5,6);
            dg->addEdge(5,8);
            dg->saveToCSV("d");
            std::cout << "running DFS...\n";
            DFS(dg);
            dg->saveTreeToCSV("tDFS");
            dg->cleanTree();
            std::cout << "running BFS...\n";
            BFS(dg->getVertex(1));
            dg->saveTreeToCSV("tBFS");
            delete dg;
            if (f3 == TREE) {
                system("python ../../src/printer.py D");
            }
            break;
        }
        case TWO: {
            directory+=filename;
            auto gr = GraphReader(directory);
            gr.initialCheck();
            DirectedGraph* dg = gr.buildDirectedGraph();
            //DFS(dg);
            auto list = topologicalSort(dg);
            if (dg->c == ACYCLIC and dg->vertices.size() <= 200) {
                for (auto item : list) {
                    std::cout << "[" << item.first << "   " << item.second << "]" << " --> ";
                }
                std::cout << "\n";
            }
            //TODO topological sort
        }
        break;
        case THREE: {
            directory+=filename;
            auto gr = GraphReader(directory);
            gr.initialCheck();
            DirectedGraph* dg = gr.buildDirectedGraph();
            //dg->saveToCSV("dgforcomps");
            //system("python ../../src/TestPrinter.py D dgforcomps shell");
            std::list<std::pair<Vertex*,int>> heads;
            auto result = stronglyConnectedComponents(dg, heads);
            std::cout <<"detected " << heads.size() << "SCCs\n each head is:\n";
            for (auto pair : heads) {
                std::cout << "head: " << pair.first->id << " of component with size: " << pair.second << std::endl;
            }
            //result->saveTreeToCSV("comps");
            if (result->vertices.size() <= 200) {
                auto cp = result->transformTreeToNormalFormGraph();
                //DFS(cp);
                cp->saveToCSV("comps");
                system("python ../../src/TestPrinter.py D comps shell");
            }
            //TODO strong coherent component
        }
        break;
        case FOUR: {
            directory+=filename;
            auto gr = GraphReader(directory);
            gr.initialCheck();
            AbstractGraph* ag;
            if (gr.type == types::DIRECTED) {
                ag = gr.buildDirectedGraph();
            } else {
                ag = gr.buildGraph();
            }
            //ag->saveToCSV("bipart");
            //system("python ../../src/TestPrinter.py D bipart f");
            //TODO Bipartite Graph
            //bool bi = isBipartite(ag);
            if (isBipartite(ag)) {
                std::cout << "Is bipartite\n";
                if (ag->vertices.size() <= 200) {
                    std::list<int> v1;
                    std::list<int> v2;
                    for (auto item : ag->vertices) {
                        if (item.color == 'r') {
                            v1.push_back(item.id);
                        } else {
                            v2.push_back(item.id);
                        }
                    }
                    int max;
                    if (v1.size() > v2.size()) {
                        max = v1.size();
                    } else {
                        max = v2.size();
                    }
                    ag->saveToCSV("bipart");
                    system("python ../../src/TestPrinter.py D bipart f");
                    auto it1 = v1.begin(), it2 = v2.begin();
                    std::cout << "v0  |  v1\n";
                    std::cout << "----------\n";
                    for (int i = 0; i < max; i++) {
                        if (it1 != v1.end()) {
                            std::cout << *it1;
                            it1++;
                        }
                        std::cout << "   |   ";
                        if (it2 != v2.end()) {
                            std::cout << *it2;
                            it2++;
                        }
                        std::cout << std::endl;
                    }
                }

            } else {
                std::cout << "Is not bipartite\n";
            }
        }
        default:

            break;
    }
    return 0;
} //73,832
