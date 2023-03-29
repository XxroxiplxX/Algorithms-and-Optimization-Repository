//
// Created by piotrkali on 3/1/23.
//

#include "Algorithms.h"
#include "queue"
#include "iostream"
void BFS(Vertex* source) {
    source->color = 'g';
    std::queue<Vertex*> queue;
    queue.push(source);
    //log->log(queue.front()->id);
    //std::cout << "\n" << queue.front()->id << std::endl;
    while (!queue.empty()) {
        auto u = queue.front();
        std :: cout << "visiting vertex with id: " << u->id << std::endl;
        for (auto v : u->neighbours) {
            if (v->color == 'w') {
                v->color = 'g';
                //u->neighbours.push_back(v);
                v->parent_id = u->id;
                queue.push(v);
            }
        }
        queue.pop();
        u->color = 'b';
    }

}
void DFSvisit(Vertex* source, AbstractGraph* g) {
    //source->color = 'b';
    g->getVertex(source->id)->color = 'g';
    g->time++;
    g->getVertex(source->id)->d = g->time;
    for (auto v : source->neighbours) {
        if (v->color == 'w') {
            //v->parent = source;
            std :: cout << "visiting vertex with id: " << v->id << std::endl;
            v->parent_id = source->id;
            //std::cout << source->id << " is now parent of " << v->id << std::endl;
            DFSvisit(v, g);
        }
    }

    g->getVertex(source->id)->color = 'b';
    g->time++;
    g->getVertex(source->id)->f = g->time;
}
void DFS(AbstractGraph* g) {
    g->time = 0;
    for (auto u : g->vertices) {
        if (u.color == 'w') {
            std::cout << "aaa\n";
            DFSvisit(&u, g);
        }
    }
}
bool topoDFSVisit(Vertex* source, DirectedGraph* dg, std::list<std::pair<int,int>>& sortedList) {
    dg->getVertex(source->id)->color = 'g';
    dg->time++;
    dg->getVertex(source->id)->d = dg->time;
    for (auto v : source->neighbours) {
        if (v->color == 'w') {
            //v->parent = source;
            //std :: cout << "visiting vertex with id: " << v->id << std::endl;
            v->parent_id = source->id;
            //std::cout << source->id << " is now parent of " << v->id << std::endl;
            topoDFSVisit(v, dg, sortedList);
        }
    }
    dg->getVertex(source->id)->color = 'b';
    dg->time++;
    dg->getVertex(source->id)->f = dg->time;

    //if (sortedList.size() > 0 and source->f >= sortedList.front()->f) {
      //  std::cout << "detected cycle" << std::endl;
        //return false;
    //} else {
        //std::cout << "dodano: " << dg->getVertex(source->id)->f << std::endl;
        sortedList.push_front(std::pair<int,int>(source->id, dg->getVertex(source->id)->f));
        return true;
    //}

}
void printPath(Vertex* source, Vertex* destination) {
    if (source == destination) {
        std::cout << source->id << "-->";
    } else if (destination->parent == nullptr) {
        std::cout << "nie ma sciezki\n";
    } else {
        printPath(source, destination->parent);
        std::cout << destination->id << "-->";
    }

}
std::list<std::pair<int, int>> topologicalSort(DirectedGraph* dg) {\
    dg->c =ACYCLIC;
    auto sortedList = std::list<std::pair<int, int>>();
    dg->time = 0;
    for (auto u : dg->vertices) {
        if (u.color == 'w') {
            bool tmp = topoDFSVisit(&u, dg, sortedList);
            //DFSvisit(&u, dg);
            if (!tmp) {
                return {};
            }
        }
    }
    for (auto v : dg->vertices) {
        for (auto n : v.neighbours) {
            if (v.f < n->f) {
                std::cout << "detected cycle\n";
                dg->c = CYCLIC;
            }
        }
    }
    return sortedList;
}
void IDFSvisit(Vertex* source, DirectedGraph* dg) {
    std::stack<int> s;
    s.push(source->id);
    while (!s.empty()) {
        source = dg->getVertex(s.top());
        dg->getVertex(s.top())->color = 'g';
        s.pop();
        for (auto v : source->neighbours) {
            s.push(v->id);
            v->parent_id = source->id;
        }
    }
}
int iDFSvisit(Vertex* source, AbstractGraph* g, int c) {
    //source->color = 'b';
    g->getVertex(source->id)->color = 'g';
    g->time++;
    int d=0;
    g->getVertex(source->id)->d = g->time;
    for (auto v : source->neighbours) {
        if (v->color == 'w') {
            //v->parent = source;
            std :: cout << "visiting vertex with id: " << v->id << std::endl;
            v->parent_id = source->id;
            //std::cout << source->id << " is now parent of " << v->id << std::endl;
            d=iDFSvisit(v, g, c);
        }
    }

    g->getVertex(source->id)->color = 'b';
    g->time++;
    g->getVertex(source->id)->f = g->time;
    return c+d+1;
}
void sortedDFS(DirectedGraph* dg, std::list<std::pair<int,int>> sortedVertices, std::list<std::pair<Vertex*,int>>& heads) {
    //std::stack<int> s;
    for (auto item : sortedVertices) {
        //std::cout << "[" << item.first << "   " << item.second << "]" << " --> ";
        if (dg->getVertex(item.first)->color == 'w') {
            //s.push(item.first);
            //std::cout << item.first << std::endl;

            int s = iDFSvisit(dg->getVertex(item.first), dg, 0);
            heads.push_front(std::pair<Vertex*, int>(dg->getVertex(item.first), s));
        }
    }
}
DirectedGraph* stronglyConnectedComponents(DirectedGraph* dg, std::list<std::pair<Vertex*,int>>& heads) {
    auto transposedDirectedGraph = dg->transpose();
    auto sortedVerticesList = topologicalSort(dg);
    sortedDFS(transposedDirectedGraph, sortedVerticesList, heads);
    return transposedDirectedGraph;
}
void DFSTreeVisit(Vertex* source, DirectedGraph* dg) {

}
void printForest(AbstractGraph* ag) {

}
bool isBipartite(AbstractGraph* ag) {
    int currColor = 1;
    for (int i = 0; i < ag->vertices.size(); i++) {
        if (ag->vertices[i].color == 'w') {
            std::cout << "vertex " << ag->vertices[i].id << std::endl;
            auto source = ag->getVertex(i+1);
            //source->color = 'g';
            std::queue<Vertex*> queue;
            queue.push(source);
            //log->log(queue.front()->id);
            //std::cout << "\n" << queue.front()->id << std::endl;
            source->color = 'r';
            while (!queue.empty()) {
                auto u = queue.front();
                //u->color = 62 + currColor;
                //std::cout << u->id << "Upokolorowano na: " << u->color << std::endl;
                currColor *= -1;
                //std :: cout << "visiting vertex with id: " << u->id << std::endl;
                for (auto v : u->neighbours) {
                    if (v->color == 'w') {
                        //v->color = u->color + currColor;
                        if (u->color == 'r') {
                            v->color = 'b';
                        } else {
                            v->color = 'r';
                        }
                        //std::cout << v->id <<  "Vpokolorowano na: " << v->color << std::endl;
                        currColor *= -1;
                        //u->neighbours.push_back(v);
                        //v->parent_id = u->id;
                        queue.push(v);
                    } else if (v->color == u->color) {
                        //std::cout << "wierzcholki " << v->id << " i " << u->id << std::endl;
                        return false;
                    }
                }
                queue.pop();
                //u->color = 'b';
            }
        }
    }
    return  true;
}
void modBFS(AbstractGraph* ag) {
    /*for (int i = 0; i < ag->vertices.size(); i++) {
        if (ag->vertices[i].color == 'w') {
            std::cout << "vertex " << ag->vertices[i].id << std::endl;
            auto source = ag->getVertex(i+1);
            //source->color = 'g';
            std::queue<Vertex*> queue;
            queue.push(source);
            //log->log(queue.front()->id);
            //std::cout << "\n" << queue.front()->id << std::endl;
            source->color = 'r';
            while (!queue.empty()) {
                auto u = queue.front();
                //u->color = 62 + currColor;
                //std::cout << u->id << "Upokolorowano na: " << u->color << std::endl;
                currColor *= -1;
                //std :: cout << "visiting vertex with id: " << u->id << std::endl;
                for (auto v : u->neighbours) {
                    if (v->color == 'w') {
                        //v->color = u->color + currColor;
                        if (u->color == 'r') {
                            v->color = 'b';
                        } else {
                            v->color = 'r';
                        }
                        //std::cout << v->id <<  "Vpokolorowano na: " << v->color << std::endl;
                        currColor *= -1;
                        //u->neighbours.push_back(v);
                        //v->parent_id = u->id;
                        queue.push(v);
                    } else if (v->color == u->color) {
                        //std::cout << "wierzcholki " << v->id << " i " << u->id << std::endl;
                        return false;
                    }
                }
                queue.pop();
                //u->color = 'b';
            }
        }
    }*/
}