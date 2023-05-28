//
// Created by korycki on 27.05.2023.
//

#ifndef BINARY_HEAP_BINARYHEAP_H
#define BINARY_HEAP_BINARYHEAP_H
#include <climits>
#include <iostream>
#include "DirectedGraph.h"

class BinaryHeap {
    //first is value and second is ordered key
    Vertex** elements;
    int capacity;
    int heap_size;
public:
    explicit BinaryHeap(int _capacity) :heap_size(0), capacity(_capacity) {
        elements = new Vertex* [_capacity];
    }


    BinaryHeap() = default;
    ~BinaryHeap() {

        delete[] elements;
    }
    int parent(int i);
    int left(int i);
    int right(int i);
    void heapify(int i);
    int get_root();
    void insert_key(Vertex* i);
    Vertex* extract_min();
    bool is_empty();
    int get_size() {
        return heap_size;
    }
    int check_min() {
        return elements[0]->dist;
    }

    void print_heap_unordered();
};
void swap(Vertex**, int i, int j);

#endif //BINARY_HEAP_BINARYHEAP_H
