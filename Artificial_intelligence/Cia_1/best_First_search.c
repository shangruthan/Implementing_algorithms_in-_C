#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define MAX_EDGES 20
#define INF 9999

typedef struct {
    char node;
    int cost;
} Edge;

typedef struct {
    char node;
    int heuristic;
} Heuristic;

Edge graph[MAX_NODES][MAX_EDGES];
int edge_count[MAX_NODES];
Heuristic heuristics[MAX_NODES];
int heuristics_size = 0;

// Function to add edges to the graph
void add_edge(char from, char to, int cost) {
    int from_index = from - 'A';
    graph[from_index][edge_count[from_index]].node = to;
    graph[from_index][edge_count[from_index]].cost = cost;
    edge_count[from_index]++;
}

// Function to get the heuristic value for a node
int get_heuristic(char node) {
    for (int i = 0; i < heuristics_size; i++) {
        if (heuristics[i].node == node) {
            return heuristics[i].heuristic;
        }
    }
    return INF; // Return a large number if node not found
}

// Best First Search Algorithm
void best_first_search(char start, char goal) {
    char open_list[MAX_NODES][MAX_NODES]; // Store paths
    int costs[MAX_NODES]; // Store costs
    int open_count = 0; // Count of paths in open list

    // Initialize open list with the start node
    open_count++;
    open_list[0][0] = start;
    open_list[0][1] = '\0';
    costs[0] = 0;

    while (open_count > 0) {
        // Find the best path (lowest heuristic)
        int best_index = -1;
        int best_h_value = INF;

        for (int i = 0; i < open_count; i++) {
            int h_value = get_heuristic(open_list[i][strlen(open_list[i]) - 1]);
            if (h_value < best_h_value) {
                best_h_value = h_value;
                best_index = i;
            }
        }

        // Current node to expand
        char *current_path = open_list[best_index];
        char current_node = current_path[strlen(current_path) - 1];
        int current_cost = costs[best_index];

        // Remove the best path from the open list
        for (int i = best_index; i < open_count - 1; i++) {
            strcpy(open_list[i], open_list[i + 1]);
            costs[i] = costs[i + 1];
        }
        open_count--;

        // Check if the goal is reached
        if (current_node == goal) {
            printf("Best First Search Solution Path: %s\n", current_path);
            printf("Total Cost: %d\n", current_cost);
            return;
        }

        // Expand neighbors
        int current_index = current_node - 'A';
        for (int j = 0; j < edge_count[current_index]; j++) {
            char neighbor = graph[current_index][j].node;
            int edge_cost = graph[current_index][j].cost;
            int new_cost = current_cost + edge_cost;

            // Create a new path for the neighbor
            char new_path[MAX_NODES];
            snprintf(new_path, sizeof(new_path), "%s%c", current_path, neighbor);

            // Add to open list
            strcpy(open_list[open_count], new_path);
            costs[open_count] = new_cost;
            open_count++;
        }
    }

    printf("No path found from %c to %c\n", start, goal);
}

int main() {
    // Initialize graph edges
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

    // Run Best First Search
    best_first_search(start_node, goal_node);

    return 0;
}
