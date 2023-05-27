//
// Created by korycki on 27.05.2023.
//

#ifndef BINARY_HEAP_BINARYHEAP_H
#define BINARY_HEAP_BINARYHEAP_H


class BinaryHeap {
    int* elements;
    int capacity;
    int heap_size;
public:
    explicit BinaryHeap(int _capacity) :heap_size(0), capacity(_capacity) {
        elements = new int [_capacity];
    }
    int parent(int i);
    int left(int i);
    int right(int i);
    void heapify(int i);
    int get_root();
    void insert_key(int i);
    void delete_key(int i);
    int extract_min();
    void decrease_key(int key, int new_val);
};
void swap(int* x, int* y);

#endif //BINARY_HEAP_BINARYHEAP_H
