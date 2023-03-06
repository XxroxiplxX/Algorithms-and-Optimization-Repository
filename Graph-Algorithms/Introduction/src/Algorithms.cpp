//
// Created by piotrkali on 3/1/23.
//

#include "Algorithms.h"
#include "queue"
#include "iostream"
void BFS(Graph graph, Vertex* source) {
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
void DFS(Graph graph, Vertex* source) {

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