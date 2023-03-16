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
    std::cout << "\n" << queue.front()->id << std::endl;
    while (!queue.empty()) {
        auto u = queue.front();
        std :: cout << "odwiedzono wierzcholek: " << u->id << std::endl;
        for (auto v : u->neighbours) {
            if (v->color == 'w') {
                v->color = 'g';
                //u->neighbours.push_back(v);
                v->parent = u;
                queue.push(v);
            }
        }
        queue.pop();
        u->color = 'b';
    }

}
void DFSvisit(Vertex* source, AbstractGraph* g) {
    source->color = 'g';
    g->time++;
    source->d = g->time;
    for (auto v : source->neighbours) {
        if (v->color == 'w') {
            v->parent = source;
            DFSvisit(v, g);
        }
    }
    source->color = 'b';
    g->time++;
    source->f = g->time;
}
void DFS(AbstractGraph* g) {
    g->time = 0;
    for (auto u : g->vertices) {
        if (u.color == 'w') {
            DFSvisit(&u, g);
        }
    }
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