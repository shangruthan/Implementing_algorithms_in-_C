#include <stdio.h>
#include <limits.h>

int alphaBetaPruning(int depth, int nodeIndex, int isMaximizingPlayer, int values[], int alpha, int beta, int maxDepth) {
    // Terminal node (leaf nodes)
    if (depth == maxDepth) {
        return values[nodeIndex];
    }

    if (isMaximizingPlayer) {
        int best = INT_MIN;

        // Maximizer's choice (MAX player)
        for (int i = 0; i < 2; i++) {
            int value = alphaBetaPruning(depth + 1, nodeIndex * 2 + i, 0, values, alpha, beta, maxDepth);
            best = best > value ? best : value;
            alpha = alpha > best ? alpha : best;

            // Alpha-Beta Pruning
            if (beta <= alpha) {
                break; // Pruning
            }
        }
        return best;
    } else {
        int best = INT_MAX;

        // Minimizer's choice (MIN player)
        for (int i = 0; i < 2; i++) {
            int value = alphaBetaPruning(depth + 1, nodeIndex * 2 + i, 1, values, alpha, beta, maxDepth);
            best = best < value ? best : value;
            beta = beta < best ? beta : best;

            // Alpha-Beta Pruning
            if (beta <= alpha) {
                break; // Pruning
            }
        }
        return best;
    }
}

int main() {
    // The depth of the game tree
    int maxDepth = 3;

    // Values of the leaf nodes
    int values[] = {-1, 4, 2, 6, -3, -5, 0, 7};

    // Initial values of alpha and beta
    int alpha = INT_MIN;
    int beta = INT_MAX;

    // Call the alpha-beta pruning algorithm
    int optimalValue = alphaBetaPruning(0, 0, 1, values, alpha, beta, maxDepth);

    printf("The optimal value is: %d\n", optimalValue);

    return 0;
}
