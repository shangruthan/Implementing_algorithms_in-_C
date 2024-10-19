#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000 // A large number representing infinity

typedef struct {
    char node;
    int cost;
} Neighbor;

typedef struct {
    char node;
    int heuristic;
} Heuristic;

typedef struct {
    int cost;
    int heuristic;
    char path[100];
} State;

int compare(const void* a, const void* b) {
    return ((State*)a)->cost + ((State*)a)->heuristic - (((State*)b)->cost + ((State*)b)->heuristic);
}

Neighbor graph[256][256];
int graph_size[256]; // To store number of neighbors for each node
Heuristic heuristics[256];
int heuristics_size = 0;

// Add a neighbor to the graph
void add_edge(char start, char end, int weight) {
    graph[start][graph_size[start]].node = end;
    graph[start][graph_size[start]].cost = weight;
    graph_size[start]++;
}

// Get heuristic value of a node
int get_heuristic(char node) {
    for (int i = 0; i < heuristics_size; i++) {
        if (heuristics[i].node == node) {
            return heuristics[i].heuristic;
        }
    }
    return INF;
}

// A* algorithm implementation
void a_star_search(char start_node, char goal_node) {
    State priority_queue[1000];
    int pq_size = 0;

    State initial_state = {0, get_heuristic(start_node), {start_node, '\0'}};
    priority_queue[pq_size++] = initial_state;

    while (pq_size > 0) {
        qsort(priority_queue, pq_size, sizeof(State), compare); // Sort the priority queue

        State current_state = priority_queue[0];
        memmove(&priority_queue[0], &priority_queue[1], --pq_size * sizeof(State));

        char current_node = current_state.path[strlen(current_state.path) - 1];

        // Check if goal node is reached
        if (current_node == goal_node) {
            printf("Goal node %c reached with total cost %d\n", goal_node, current_state.cost);
            printf("Path: %s\n", current_state.path);
            return;
        }

        // Expand neighbors
        for (int i = 0; i < graph_size[current_node]; i++) {
            Neighbor neighbor = graph[current_node][i];

            State new_state;
            new_state.cost = current_state.cost + neighbor.cost;
            new_state.heuristic = get_heuristic(neighbor.node);

            int current_path_len = strlen(current_state.path);
            int remaining_space = sizeof(new_state.path) - current_path_len - 1; // -1 for null terminator

            if (remaining_space > 0) {
                snprintf(new_state.path, remaining_space + 1, "%s%c", current_state.path, neighbor.node); // +1 to account for null terminator
            } else {
                continue;  // Skip this neighbor if there’s no space to add it to the path
            }

            priority_queue[pq_size++] = new_state;
        }
    }

    printf("Goal node not found!\n");
}

int main() {
    // Define the graph (same as in the Python example)
    add_edge('A', 'B', 2);
    add_edge('A', 'C', 4);
    add_edge('B', 'D', 3);
    add_edge('B', 'E', 6);
    add_edge('C', 'F', 5);
    add_edge('C', 'G', 2);
    add_edge('D', 'H', 4);
    add_edge('E', 'I', 3);
    add_edge('F', 'J', 2);
    add_edge('G', 'K', 7);

    // Define heuristics
    heuristics[heuristics_size++] = (Heuristic){'A', 10};
    heuristics[heuristics_size++] = (Heuristic){'B', 8};
    heuristics[heuristics_size++] = (Heuristic){'C', 6};
    heuristics[heuristics_size++] = (Heuristic){'D', 7};
    heuristics[heuristics_size++] = (Heuristic){'E', 4};
    heuristics[heuristics_size++] = (Heuristic){'F', 3};
    heuristics[heuristics_size++] = (Heuristic){'G', 5};
    heuristics[heuristics_size++] = (Heuristic){'H', 9};
    heuristics[heuristics_size++] = (Heuristic){'I', 2};
    heuristics[heuristics_size++] = (Heuristic){'J', 0};
    heuristics[heuristics_size++] = (Heuristic){'K', 1};

    char start_node = 'A';
    char goal_node = 'J';
    a_star_search(start_node, goal_node);

    return 0;
}
