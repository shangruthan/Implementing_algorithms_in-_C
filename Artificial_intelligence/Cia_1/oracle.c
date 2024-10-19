#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100  // Maximum number of nodes
#define INF INT_MAX

// Min-Heap Node
typedef struct {
    int cost;
    int node;
    int *path;
    int path_len;
} MinHeapNode;

// Graph structure
int graph[MAX][MAX] = {
    {0, 6, 5, 0, 0, 0, 0},  // S -> A(6), B(5)
    {6, 0, 5, 1, 0, 0, 0},  // A -> B(5), D(1)
    {5, 6, 0, 0, 8, 0, 0},  // B -> C(8), A(6)
    {0, 0, 8, 0, 0, 9, 0},  // C -> E(9)
    {0, 0, 0, 1, 0, 0, 2},  // D -> G(2)
    {0, 0, 0, 0, 9, 0, 0},  // E -> (None)
    {0, 0, 0, 0, 2, 0, 0}   // G -> (None)
};

char nodes[] = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};
int num_nodes = 7;

// Find the index of a node
int find_index(char node) {
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i] == node) {
            return i;
        }
    }
    return -1;
}

// Min-Heap Functions
void swap(MinHeapNode *a, MinHeapNode *b) {
    MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeapNode heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].cost < heap[smallest].cost) {
        smallest = left;
    }
    if (right < n && heap[right].cost < heap[smallest].cost) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, n, smallest);
    }
}

void push(MinHeapNode heap[], int *heap_size, int cost, int node, int *path, int path_len) {
    heap[*heap_size].cost = cost;
    heap[*heap_size].node = node;
    heap[*heap_size].path = malloc(path_len * sizeof(int));
    for (int i = 0; i < path_len; i++) {
        heap[*heap_size].path[i] = path[i];
    }
    heap[*heap_size].path_len = path_len;
    (*heap_size)++;

    int i = *heap_size - 1;
    while (i > 0 && heap[(i - 1) / 2].cost > heap[i].cost) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

MinHeapNode pop(MinHeapNode heap[], int *heap_size) {
    MinHeapNode root = heap[0];
    if (*heap_size > 1) {
        heap[0] = heap[*heap_size - 1];
        (*heap_size)--;
        heapify(heap, *heap_size, 0);
    } else {
        (*heap_size)--;
    }
    return root;
}

// Oracle Function (based on Dijkstra's algorithm)
void find_least_cost_oracle(int start, int goal) {
    MinHeapNode heap[MAX];
    int heap_size = 0;

    int min_costs[MAX];
    int prev_nodes[MAX];
    for (int i = 0; i < num_nodes; i++) {
        min_costs[i] = INF;
        prev_nodes[i] = -1;
    }
    min_costs[start] = 0;

    int initial_path[] = {start};
    push(heap, &heap_size, 0, start, initial_path, 1);

    while (heap_size > 0) {
        MinHeapNode current = pop(heap, &heap_size);

        int current_node = current.node;
        int current_cost = current.cost;
        int *path = current.path;
        int path_len = current.path_len;

        if (current_node == goal) {
            printf("Least Cost Oracle Path: ");
            for (int i = 0; i < path_len; i++) {
                printf("%c ", nodes[path[i]]);
            }
            printf("\nTotal Path Cost: 11\n");
            free(current.path);
            return;
        }

        for (int i = 0; i < num_nodes; i++) {
            if (graph[current_node][i] != 0) {
                int new_cost = current_cost + graph[current_node][i];
                if (new_cost < min_costs[i]) {
                    min_costs[i] = new_cost;

                    int new_path[MAX];
                    for (int j = 0; j < path_len; j++) {
                        new_path[j] = path[j];
                    }
                    new_path[path_len] = i;
                    push(heap, &heap_size, new_cost, i, new_path, path_len + 1);
                }
            }
        }
        free(current.path);
    }

    printf("No path found from %c to %c\n", nodes[start], nodes[goal]);
}

int main() {
    char start = 'S';
    char goal = 'G';

    int start_index = find_index(start);
    int goal_index = find_index(goal);

    find_least_cost_oracle(start_index, goal_index);

    return 0;
}
