#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_NODES 100

typedef struct {
    char node;
    int cost;
} Edge;

typedef struct {
    char name;
    int heuristic;
} Heuristic;

typedef struct {
    char path[MAX_NODES];
    int cost;
} Node;

Edge graph[MAX_NODES][MAX_NODES];
int graphSize[MAX_NODES];
Heuristic heuristics[MAX_NODES];
int heuristics_size = 0;

void add_edge(char from, char to, int cost) {
    int fromIndex = from - 'A';
    int toIndex = to - 'A';
    
    graph[fromIndex][graphSize[fromIndex]].node = to;
    graph[fromIndex][graphSize[fromIndex]].cost = cost;
    graphSize[fromIndex]++;
}

Node branch_and_bound(char start, char goal) {
    Node best_solution;
    best_solution.cost = INT_MAX;
    
    Node queue[MAX_NODES];
    int queue_size = 0;

    // Initial node
    queue[queue_size++] = (Node){{start, '\0'}, 0};

    while (queue_size > 0) {
        Node current_node = queue[--queue_size];

        if (current_node.path[strlen(current_node.path) - 1] == goal) {
            if (current_node.cost < best_solution.cost) {
                best_solution = current_node;
            }
            continue;
        }

        int current_index = current_node.path[strlen(current_node.path) - 1] - 'A';
        
        for (int i = 0; i < graphSize[current_index]; i++) {
            char next_node = graph[current_index][i].node;
            int edge_cost = graph[current_index][i].cost;
            
            // Total cost
            int new_cost = current_node.cost + edge_cost;

            // Check if this path is better than the current best solution
            if (new_cost < best_solution.cost) {
                Node new_node = current_node;
                new_node.path[strlen(new_node.path)] = next_node;
                new_node.path[strlen(new_node.path) + 1] = '\0'; // Null terminate
                new_node.cost = new_cost;

                // Add the new node to the queue
                queue[queue_size++] = new_node;
            }
        }
    }

    return best_solution;
}

int main() {
    // Define the edges
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

    Node solution = branch_and_bound(start_node, goal_node);

    if (solution.cost != INT_MAX) {
        printf("Best Path Found (Branch and Bound): %s\n", solution.path);
        printf("Total Path Cost: %d\n", solution.cost);
    } else {
        printf("No path found from %c to %c\n", start_node, goal_node);
    }

    return 0;
}
