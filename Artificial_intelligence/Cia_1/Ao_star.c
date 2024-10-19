#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX
#include <string.h> // For strcpy, snprintf

#define INF INT_MAX

// Define the structure for neighbors
typedef struct {
    char node;
    int cost;
} Neighbor;

// Define a structure for the heuristic values
typedef struct {
    char node;
    int heuristic;
} Heuristic;

// The graph and heuristic arrays
Neighbor graph[256][256];
int graph_size[256];
Heuristic heuristics[256];
int heuristics_size = 0;

// Add an edge to the graph
void add_edge(char start, char end, int cost) {
    graph[start][graph_size[start]].node = end;
    graph[start][graph_size[start]].cost = cost;
    graph_size[start]++;
}

// Get the heuristic value of a node
int get_heuristic(char node) {
    for (int i = 0; i < heuristics_size; i++) {
        if (heuristics[i].node == node) {
            return heuristics[i].heuristic;
        }
    }
    return INF;
}

// AO* algorithm implementation
int ao_star(char node, char goal, int visited[256], char path[100]) {
    if (node == goal) {
        path[0] = goal;
        path[1] = '\0';
        return 0;
    }

    if (visited[node]) {
        return INF;
    }

    visited[node] = 1; // Mark node as visited

    int min_cost = INF;
    char best_subtree_path[100] = {0};

    for (int i = 0; i < graph_size[node]; i++) {
        Neighbor neighbor = graph[node][i];
        char subtree_path[100] = {0};

        int subtree_cost = ao_star(neighbor.node, goal, visited, subtree_path);

        // Skip if the subtree cost is infinite (no valid path)
        if (subtree_cost == INF) {
            continue;
        }

        int total_cost = neighbor.cost + subtree_cost;

        if (total_cost < min_cost) {
            min_cost = total_cost;
            size_t remaining_space = sizeof(best_subtree_path) - 1; // Reserve space for null terminator
            if (remaining_space > strlen(subtree_path)) {
                snprintf(best_subtree_path, remaining_space, "%c%s", node, subtree_path);
            } else {
                continue; // Skip if not enough space is available
            }
        }
    }

    visited[node] = 0; // Unmark node as visited

    // Copy best path found
    strcpy(path, best_subtree_path);

    return min_cost;
}

void run_ao_star(char start_node, char goal_node) {
    int visited[256] = {0};
    char solution_path[100] = {0};
    int total_cost = ao_star(start_node, goal_node, visited, solution_path);

    if (total_cost == INF) {
        printf("No path found!\n");
    } else {
        printf("AO* Solution Path: %s\n", solution_path);
        printf("Total Cost to Goal: %d\n", total_cost);
    }
}

int main() {
    // Define the graph
    add_edge('S', 'A', 6);
    add_edge('S', 'B', 5);
    add_edge('A', 'B', 5);
    add_edge('A', 'D', 1);
    add_edge('B', 'C', 8);
    add_edge('B', 'A', 6);
    add_edge('C', 'E', 9);
    add_edge('D', 'G', 2);

    // Define the heuristic values
    heuristics[heuristics_size++] = (Heuristic){'S', 7};
    heuristics[heuristics_size++] = (Heuristic){'A', 6};
    heuristics[heuristics_size++] = (Heuristic){'B', 5};
    heuristics[heuristics_size++] = (Heuristic){'C', 8};
    heuristics[heuristics_size++] = (Heuristic){'D', 1};
    heuristics[heuristics_size++] = (Heuristic){'E', 9};
    heuristics[heuristics_size++] = (Heuristic){'G', 0};

    char start_node = 'S';
    char goal_node = 'G';

    run_ao_star(start_node, goal_node);

    return 0;
}
