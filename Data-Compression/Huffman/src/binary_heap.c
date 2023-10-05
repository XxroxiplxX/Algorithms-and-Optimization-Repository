#include "binary_heap.h"
#include <stdint.h>
#include <stdio.h>


void swap_nodes(huffman_node **a, huffman_node **b)
{
  huffman_node* tmp = *a;
  *a = *b;
  *b = tmp;
}
u16 parent(uint16_t i)
{
  return (i-1)/2;
}
u16 left(uint16_t i)
{
  return (2*i + 1);
}
u16 right(uint16_t i)
{
  return (2*i + 2);
}
binary_heap *initialize_binary_heap()
{
  binary_heap* bh = (binary_heap*) malloc(sizeof(binary_heap));
  bh->curr_size = 0;
  bh->array = (huffman_node**) malloc(LANG*sizeof(huffman_node));
  return bh;
}
void heapify(struct binary_heap* heap, int index) {
    int smallest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if (left_child < heap->curr_size && heap->array[left_child]->freq < heap->array[smallest]->freq) {
        smallest = left_child;
    }

    if (right_child < heap->curr_size && heap->array[right_child]->freq < heap->array[smallest]->freq) {
        smallest = right_child;
    }

    if (smallest != index) {
        swap_nodes(&heap->array[index], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

void insert_node(binary_heap* heap,  huffman_node* node) {
    if (heap->curr_size == LANG) {
        printf("heap full\n");
        return;
    }

    int i = heap->curr_size;
    heap->curr_size++;
    heap->array[i] = node;

    while (i > 0 && heap->array[i]->freq < heap->array[(i - 1) / 2]->freq) {
        swap_nodes(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
huffman_node* extract_min(binary_heap* heap)
{
    if (heap->curr_size <= 0) {
        return NULL;
    }

    if (heap->curr_size == 1) {
        heap->curr_size--;
        return heap->array[0];
    }

    struct huffman_node* root = heap->array[0];
    heap->array[0] = heap->array[heap->curr_size - 1];
    heap->curr_size--;
    heapify(heap, 0);

    return root;
}

huffman_node* create_node(u8 sign, float freq)
{
  huffman_node* hf = malloc(sizeof(huffman_node));
  hf->sign = sign;
  hf->freq = freq;
  hf->left = NULL;
  hf->right = NULL;
  return hf;
}
void free_the_heap(binary_heap* heap)
{
  free(heap->array);
  free(heap);
}

