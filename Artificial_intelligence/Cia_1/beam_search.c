#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define MAX_EDGES 20
#define BEAM_WIDTH 3
#define INF 9999

typedef struct {
    char node;
    int cost;
} Edge;

typedef struct {
    char node;
    int heuristic;
} Heuristic;

// Graph representation
Edge graph[MAX_NODES][MAX_NODES];
int edge_count[MAX_NODES];
Heuristic heuristics[MAX_NODES];
int heuristics_size = 0;

void add_edge(char from, char to, int cost) {
    int from_index = from - 'A';
    int to_index = to - 'A';
    graph[from_index][edge_count[from_index]].node = to;
    graph[from_index][edge_count[from_index]].cost = cost;
    edge_count[from_index]++;
}

int get_heuristic(char node) {
    for (int i = 0; i < heuristics_size; i++) {
        if (heuristics[i].node == node) {
            return heuristics[i].heuristic;
        }
    }
    return INF; // Return a large number if node not found
}

// Beam Search Algorithm
void beam_search(char start, char goal) {
    char paths[BEAM_WIDTH][MAX_NODES];
    int costs[BEAM_WIDTH];
    
    // Initialize the beam
    for (int i = 0; i < BEAM_WIDTH; i++) {
        costs[i] = INF;
        strcpy(paths[i], "");
    }
    
    // Start from the initial node
    costs[0] = 0;
    paths[0][0] = start;
    paths[0][1] = '\0';
    
    int path_count = 1;

    while (path_count > 0) {
        char new_paths[BEAM_WIDTH * MAX_NODES][MAX_NODES];
        int new_costs[BEAM_WIDTH * MAX_NODES];
        int new_path_count = 0;

        // Expand each path in the current beam
        for (int i = 0; i < path_count; i++) {
            char current_node = paths[i][strlen(paths[i]) - 1];
            int current_index = current_node - 'A';

            // Check if the current path reaches the goal
            if (current_node == goal) {
                printf("Found path: %s with cost: %d\n", paths[i], costs[i]);
                return;
            }

            // Expand the current node
            for (int j = 0; j < edge_count[current_index]; j++) {
                char next_node = graph[current_index][j].node;
                int edge_cost = graph[current_index][j].cost;
                int new_cost = costs[i] + edge_cost;

                // Create a new path
                strcpy(new_paths[new_path_count], paths[i]);
                int len = strlen(new_paths[new_path_count]);
                new_paths[new_path_count][len] = next_node;
                new_paths[new_path_count][len + 1] = '\0';
                new_costs[new_path_count] = new_cost;
                new_path_count++;
            }
        }

        // Select the best new paths based on the beam width
        // (Combine cost and heuristic for sorting)
        for (int i = 0; i < new_path_count; i++) {
            new_costs[i] += get_heuristic(new_paths[i][strlen(new_paths[i]) - 1]);
        }

        // Simple selection sort to find the top k paths
        for (int i = 0; i < new_path_count; i++) {
            for (int j = i + 1; j < new_path_count; j++) {
                if (new_costs[j] < new_costs[i]) {
                    // Swap costs
                    int temp_cost = new_costs[i];
                    new_costs[i] = new_costs[j];
                    new_costs[j] = temp_cost;

                    // Swap paths
                    char temp_path[MAX_NODES];
                    strcpy(temp_path, new_paths[i]);
                    strcpy(new_paths[i], new_paths[j]);
                    strcpy(new_paths[j], temp_path);
                }
            }
        }

        // Update the beam with the best k paths
        path_count = (new_path_count < BEAM_WIDTH) ? new_path_count : BEAM_WIDTH;
        for (int i = 0; i < path_count; i++) {
            strcpy(paths[i], new_paths[i]);
            costs[i] = new_costs[i];
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

    // Run Beam Search
    beam_search(start_node, goal_node);

    return 0;
}
