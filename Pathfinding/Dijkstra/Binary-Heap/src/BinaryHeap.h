//
// Created by korycki on 27.05.2023.
//

#ifndef BINARY_HEAP_BINARYHEAP_H
#define BINARY_HEAP_BINARYHEAP_H
#include <climits>
#include <iostream>
#include "DirectedGraph.h"
#include <vector>
class BinaryHeap {
    //first is value and second is ordered key
    std::vector<Vertex*> elements;
    int* position;
    int capacity;
    int heap_size;
public:
    explicit BinaryHeap(int _capacity) :heap_size(0), capacity(_capacity) {
        elements = std::vector<Vertex*>(_capacity);
        position = new int[capacity];
    }
    BinaryHeap() = default;
    ~BinaryHeap() {
        delete[] position;
    }
    static int parent(int i);
    static int left(int i);
    static int right(int i);
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
    void decrease_key(Vertex* v, int new_distance);
    void swap_elements(int i, int j);
    void print_heap_unordered();
};


#endif //BINARY_HEAP_BINARYHEAP_H
