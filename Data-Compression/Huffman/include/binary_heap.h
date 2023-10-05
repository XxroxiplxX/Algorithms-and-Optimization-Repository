#include <stdint.h>
#include <stdlib.h>
#define u8 uint8_t
#define u16 uint16_t
#define LANG 6
typedef struct huffman_node {
  struct huffman_node *left;
  struct huffman_node *right;
  u8 sign;
  float freq;
} huffman_node;

huffman_node *create_node(u8 sign, float freq);

typedef struct binary_heap {
  huffman_node **array;
  u16 curr_size;
} binary_heap;

binary_heap *initialize_binary_heap();
u16 left(u16 i);
u16 right(u16 i);
void swap_nodes(huffman_node **a, huffman_node **b);
void heapify(binary_heap *, int idx);
huffman_node *extract_min(binary_heap *);
void insert_node(binary_heap *, huffman_node *);
void free_the_heap(binary_heap*);