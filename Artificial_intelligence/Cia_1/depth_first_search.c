#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100  // Maximum number of nodes

// Graph structure
char graph[][MAX] = {
    {'A', 'B', '\0'},   // S -> A, B
    {'B', 'D', '\0'},   // A -> B, D
    {'C', 'A', '\0'},   // B -> C, A
    {'E', '\0'},        // C -> E
    {'G', '\0'},        // D -> G
    {'\0'},             // E -> (none)
    {'\0'}              // G -> (none)
};

// Node names
char nodes[] = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};
int num_nodes = 7;

// Function to find the index of a node in the graph
int find_index(char node) {
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i] == node) {
            return i;
        }
    }
    return -1;
}

// Depth First Search algorithm
bool dfs(char start, char goal, bool visited[], char path[], int *path_len) {
    int start_index = find_index(start);  // Get index of the start node
    if (start_index == -1) {
        return false;  // Invalid start node
    }

    visited[start_index] = true;  // Mark the current node as visited
    path[(*path_len)++] = start;  // Add the current node to the path
    printf("Visiting: %c\n", start);

    if (start == goal) {
        printf("Goal %c found!\n", goal);
        printf("Path: ");
        for (int i = 0; i < *path_len; i++) {
            printf("%c ", path[i]);
        }
        printf("\n");
        return true;  // Goal found
    }

    // Explore all neighbors of the current node
    for (int i = 0; graph[start_index][i] != '\0'; i++) {
        char neighbor = graph[start_index][i];
        int neighbor_index = find_index(neighbor);
        if (!visited[neighbor_index]) {
            if (dfs(neighbor, goal, visited, path, path_len)) {
                return true;  // Goal found in recursion
            }
        }
    }

    (*path_len)--;  // Backtrack (remove the current node from the path)
    return false;
}

int main() {
    bool visited[MAX] = {false};  // Track visited nodes
    char path[MAX];               // Store the current path
    int path_len = 0;             // Length of the current path

    char start = 'S';  // Start node
    char goal = 'G';   // Goal node

    // Perform DFS
    if (!dfs(start, goal, visited, path, &path_len)) {
        printf("Goal not found.\n");
    }

    return 0;
}
