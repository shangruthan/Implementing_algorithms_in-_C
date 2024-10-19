#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Node {
    char vertex;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create a new queue node
Node* createNode(char vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to enqueue an element
void enqueue(Queue* queue, char vertex) {
    Node* newNode = createNode(vertex);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue an element
char dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return '\0';
    }
    Node* temp = queue->front;
    char vertex = temp->vertex;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return vertex;
}

// Function to check if a vertex is visited
int isVisited(char* visited, char vertex) {
    for (int i = 0; i < MAX; i++) {
        if (visited[i] == vertex) {
            return 1;
        }
        if (visited[i] == '\0') {
            break;  // Stop searching when we reach the end of visited
        }
    }
    return 0;
}

// Function to perform BFS
void bfs(char graph[MAX][MAX], int size, char start, char goal) {
    char visited[MAX] = {0};  // Array to keep track of visited nodes
    Queue* queue = createQueue();
    enqueue(queue, start);

    while (queue->front != NULL) {
        char current_node = dequeue(queue);
        printf("Visiting: %c\n", current_node);

        if (current_node == goal) {
            printf("Goal %c found!\n", goal);
            return;  // Goal found
        }

        if (!isVisited(visited, current_node)) {
            visited[strlen(visited)] = current_node;  // Mark current node as visited

            for (int i = 0; i < size; i++) {
                if (graph[current_node - 'A'][i] == 1 && !isVisited(visited, i + 'A')) {
                    enqueue(queue, i + 'A');  // Enqueue unvisited neighbors
                }
            }
        }
    }
    printf("Goal not found\n");
}

int main() {
    int size = 7; // Number of nodes (S, A, B, C, D, E, G)
    char graph[MAX][MAX] = {
        {0, 1, 1, 0, 0, 0, 0},  // S: A, B
        {1, 0, 1, 1, 0, 0, 0},  // A: B, D
        {1, 1, 0, 0, 1, 0, 0},  // B: C, A
        {0, 0, 1, 0, 0, 0, 1},  // C: E
        {0, 0, 0, 0, 0, 0, 1},  // D: G
        {0, 0, 0, 0, 0, 0, 0},  // E: (none)
        {0, 0, 0, 0, 1, 0, 0}   // G: (none)
    };

    bfs(graph, size, 'S', 'G');

    return 0;
}
