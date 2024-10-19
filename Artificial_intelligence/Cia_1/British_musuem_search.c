#include <stdio.h>
#include <string.h>

#define MAX 100  // Max number of nodes and max path length

// Function to check if a node is already in the current path
int is_in_path(char path[], int path_len, char node) {
    for (int i = 0; i < path_len; i++) {
        if (path[i] == node) {
            return 1;
        }
    }
    return 0;
}

// Function to find all paths from start to goal
void bms(char graph[][MAX], char *nodes[], int num_nodes, char start, char goal, char path[], int path_len) {
    // Add the current start node to the path
    path[path_len] = start;
    path_len++;

    // If we've reached the goal, print the path
    if (start == goal) {
        printf("Path: ");
        for (int i = 0; i < path_len; i++) {
            printf("%c ", path[i]);
        }
        printf("\n");
        return;
    }

    // Find the index of the current node (start) in the graph
    int start_index = -1;
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i][0] == start) {
            start_index = i;
            break;
        }
    }

    // If node is not in graph, return (dead-end)
    if (start_index == -1) {
        return;
    }

    // Explore all neighbors of the current node
    for (int i = 0; graph[start_index][i] != '\0'; i++) {
        char neighbor = graph[start_index][i];
        // If the neighbor is not already in the current path, explore further
        if (!is_in_path(path, path_len, neighbor)) {
            bms(graph, nodes, num_nodes, neighbor, goal, path, path_len);
        }
    }
}

int main() {
    // Graph representation using an adjacency list
    char graph[][MAX] = {
        {'A', 'B', '\0'},   // S: A, B
        {'B', 'D', '\0'},   // A: B, D
        {'C', 'A', '\0'},   // B: C, A
        {'E', '\0'},        // C: E
        {'G', '\0'},        // D: G
        {'\0'},             // E: (none)
        {'\0'}              // G: (none)
    };

    // List of node names
    char *nodes[] = {"S", "A", "B", "C", "D", "E", "G"};
    int num_nodes = 7;  // Number of nodes in the graph

    char start = 'S';  // Start node
    char goal = 'G';   // Goal node

    char path[MAX];  // To store the current path
    int path_len = 0;

    // Find and print all possible paths from start to goal
    printf("All Possible Paths from %c to %c:\n", start, goal);
    bms(graph, nodes, num_nodes, start, goal, path, path_len);

    return 0;
}
