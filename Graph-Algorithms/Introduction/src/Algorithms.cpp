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