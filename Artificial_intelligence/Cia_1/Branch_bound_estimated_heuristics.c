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

// Branch and Bound Algorithm with Cost and Heuristics
void branch_and_bound_with_heuristic(char start, char goal) {
    typedef struct {
        int f_cost;
        int g_cost;
        char node;
        char path[MAX_NODES];
    } Node;

    Node queue[MAX_NODES * MAX_NODES];
    int queue_size = 0;

    // Initialize queue with the start node
    queue[queue_size++] = (Node){get_heuristic(start), 0, start, {start, '\0'}};

    int best_cost = INF;
    char best_path[MAX_NODES];

    while (queue_size > 0) {
        // Find the node with the lowest f_cost
        int best_index = 0;
        for (int i = 1; i < queue_size; i++) {
            if (queue[i].f_cost < queue[best_index].f_cost) {
                best_index = i;
            }
        }

        Node current_node = queue[best_index];

        // Remove the best node from the queue
        for (int i = best_index; i < queue_size - 1; i++) {
            queue[i] = queue[i + 1];
        }
        queue_size--;

        // Check if the goal is reached
        if (current_node.node == goal) {
            if (current_node.g_cost < best_cost) {
                best_cost = current_node.g_cost;
                strcpy(best_path, current_node.path);
            }
            continue;
        }

        // Expand neighbors
        int current_index = current_node.node - 'A';
        for (int j = 0; j < edge_count[current_index]; j++) {
            char neighbor = graph[current_index][j].node;
            int edge_cost = graph[current_index][j].cost;
            int total_cost = current_node.g_cost + edge_cost;

            if (total_cost < best_cost) {
                Node neighbor_node;
                neighbor_node.g_cost = total_cost;
                neighbor_node.node = neighbor;
                strcpy(neighbor_node.path, current_node.path);
                strncat(neighbor_node.path, &neighbor, 1);
                neighbor_node.f_cost = total_cost + get_heuristic(neighbor);

                // Add to queue
                queue[queue_size++] = neighbor_node;
            }
        }
    }

    if (best_cost < INF) {
        printf("Best Path Found (Branch and Bound with Cost + Heuristics): %s\n", best_path);
        printf("Total Path Cost: %d\n", best_cost);
    } else {
        printf("No path found from %c to %c\n", start, goal);
    }
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

    // Run Branch and Bound with Heuristics
    branch_and_bound_with_heuristic(start_node, goal_node);

    return 0;
}
