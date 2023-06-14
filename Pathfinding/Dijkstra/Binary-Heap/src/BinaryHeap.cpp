//
// Created by korycki on 27.05.2023.
//

#include "BinaryHeap.h"
void BinaryHeap::swap_elements(int i, int j) {
    auto tmp = elements[i];
    elements[i] = elements[j];
    elements[j] = tmp;

    position[elements[i]->id] = i;
    position[elements[j]->id] = j;

}
int BinaryHeap::parent(int i) {
    return (i-1)/2;
}

int BinaryHeap::left(int i) {
    return (2*i + 1);
}

int BinaryHeap::right(int i) {
    return (2*i + 2);
}

void BinaryHeap::heapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size and elements[l]->dist < elements[i]->dist) {
        smallest = l;
    }
    if (r < heap_size and elements[r]->dist < elements[smallest]->dist) {
        smallest = r;
    }
    if (smallest != i) {
        swap_elements(i, smallest);
        heapify(smallest);
    }
}

int BinaryHeap::get_root() {
    return 0;
}

void BinaryHeap::insert_key(Vertex* k) {
    heap_size++;
    int i = heap_size - 1;
    elements[i] = k;
    position[k->id] = i;
    while (i != 0 and elements[parent(i)]->dist > elements[i]->dist) {
        swap_elements(i, parent(i));
        i = parent(i);
    }
}

Vertex* BinaryHeap::extract_min() {

    if (heap_size == 1) {
        heap_size--;
        return elements[0];
    }
    auto root = elements[0];
    elements[0] = elements[heap_size - 1];
    heap_size--;
    heapify(0);
    return root;
}



void BinaryHeap::print_heap_unordered() {
    for (int i = 0; i < heap_size; i++) {
        std::cout << elements[i]->id << "--" << elements[i]->dist << "  |  ";
    }
    std::cout << std::endl;
}

bool BinaryHeap::is_empty() {
    return heap_size == 0;
}

void BinaryHeap::decrease_key(Vertex *v, unsigned long long new_distance) {

    int i = position[v->id];
    elements[i]->dist = new_distance;
    while (i != 0 and elements[parent(i)]->dist > elements[i]->dist) {
        swap_elements(i, parent(i));
        i = parent(i);
    }
}
