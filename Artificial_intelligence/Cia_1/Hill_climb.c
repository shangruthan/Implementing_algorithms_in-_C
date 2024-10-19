#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100  // Maximum number of nodes
#define INF INT_MAX

// Graph structure
int graph[MAX][MAX] = {
    {0, 6, 5, 0, 0, 0, 0},   // S -> A(6), B(5)
    {6, 0, 5, 1, 0, 0, 0},   // A -> B(5), D(1)
    {5, 6, 0, 0, 8, 0, 0},   // B -> C(8), A(6)
    {0, 0, 8, 0, 0, 9, 0},   // C -> E(9)
    {0, 0, 0, 1, 0, 0, 2},   // D -> G(2)
    {0, 0, 0, 0, 9, 0, 0},   // E -> (None)
    {0, 0, 0, 0, 2, 0, 0}    // G -> (None)
};

// Heuristic values
int heuristic[] = {7, 6, 5, 8, 1, 9, 0};  // S, A, B, C, D, E, G
char nodes[] = {'S', 'A', 'B', 'C', 'D', 'E', 'G'};
int num_nodes = 7;

// Find index of a node
int find_index(char node) {
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i] == node) {
            return i;
        }
    }
    return -1;
}

// Greedy solution
void greedy_solution(int start, int goal, int solution[], int *sol_len) {
    int current_node = start;
    solution[(*sol_len)++] = current_node;

    while (current_node != goal) {
        int next_node = -1;
        int min_heuristic = INF;

        for (int i = 0; i < num_nodes; i++) {
            if (graph[current_node][i] != 0 && heuristic[i] < min_heuristic) {
                next_node = i;
                min_heuristic = heuristic[i];
            }
        }

        if (next_node == -1) {
            break;  // No more neighbors
        }

        if (solution[*sol_len - 1] != next_node) {
            solution[(*sol_len)++] = next_node;  // Avoid cycles
        }
        current_node = next_node;
    }
}

// Calculate path cost based on heuristic
int path_cost(int solution[], int sol_len) {
    int cost = 0;
    for (int i = 0; i < sol_len; i++) {
        cost += heuristic[solution[i]];
    }
    return cost;
}

// Generate neighbors by swapping nodes in the solution
void generate_neighbors(int solution[], int sol_len, int neighbors[MAX][MAX], int *num_neighbors) {
    *num_neighbors = 0;

    for (int i = 1; i < sol_len - 1; i++) {
        for (int j = i + 1; j < sol_len - 1; j++) {
            int neighbor[MAX];
            memcpy(neighbor, solution, sol_len * sizeof(int));
            int temp = neighbor[i];
            neighbor[i] = neighbor[j];
            neighbor[j] = temp;

            memcpy(neighbors[*num_neighbors], neighbor, sol_len * sizeof(int));
            (*num_neighbors)++;
        }
    }
}

// Find the best neighbor
void best_neighbor(int current_solution[], int sol_len, int best_sol[], int *best_cost) {
    int neighbors[MAX][MAX];
    int num_neighbors;
    generate_neighbors(current_solution, sol_len, neighbors, &num_neighbors);

    *best_cost = path_cost(current_solution, sol_len);
    memcpy(best_sol, current_solution, sol_len * sizeof(int));

    for (int i = 0; i < num_neighbors; i++) {
        int current_cost = path_cost(neighbors[i], sol_len);
        if (current_cost < *best_cost) {
            *best_cost = current_cost;
            memcpy(best_sol, neighbors[i], sol_len * sizeof(int));
        }
    }
}

// Hill Climbing Algorithm
void hill_climbing(int start, int goal) {
    int current_solution[MAX], sol_len = 0;
    greedy_solution(start, goal, current_solution, &sol_len);
    int current_cost = path_cost(current_solution, sol_len);

    while (true) {
        int best_sol[MAX], best_cost;
        best_neighbor(current_solution, sol_len, best_sol, &best_cost);

        if (best_cost >= current_cost) {
            printf("Reached local optimum at: ");
            for (int i = 0; i < sol_len; i++) {
                printf("%c ", nodes[current_solution[i]]);
            }
            printf("with cost %d\n", current_cost);
            break;
        }

        memcpy(current_solution, best_sol, sol_len * sizeof(int));
        current_cost = best_cost;
    }
}

int main() {
    char start = 'S';
    char goal = 'G';

    int start_index = find_index(start);
    int goal_index = find_index(goal);

    hill_climbing(start_index, goal_index);

    return 0;
}
