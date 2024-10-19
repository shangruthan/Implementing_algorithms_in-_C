# Implementing_algorithms_in-_C
This repository contains a collection of algorithms and implementations focusing on various search and optimization techniques in artificial intelligence. The implementations are primarily done in C and cover a range of algorithms that are fundamental to problem-solving and decision-making processes.

CIA1 - Search Algorithms

AStar.c
Implements the A* algorithm, a popular pathfinding and graph traversal algorithm known for its efficiency and accuracy in finding the shortest path.
Uses both cost and heuristic (f(n) = g(n) + h(n)).
Guarantees the shortest path if the heuristic is admissible.

BranchAndBoundCostHeuristic.c
Implementation of the Branch and Bound algorithm that uses cost and heuristic values to prune the search space.
Combines cost and heuristic for efficient pruning.

BranchAndBoundDeadHorsePrinciple.c
An extended Branch and Bound method that incorporates the Dead Horse Principle, where unpromising paths are pruned early.
Early pruning of non-viable paths.

BeamSearch.c
Implements the Beam Search algorithm, a heuristic search technique that explores a set number of the most promising nodes at each level.
Uses a beam width to limit the search space.
Efficient memory usage compared to exhaustive search methods.

BestFirstSearch.c
Implements the Best-First Search algorithm, which greedily selects the most promising node based on a given heuristic.
Uses a priority queue to explore the best node first.

BreadthFirstSearch.c
Implements the Breadth-First Search algorithm, a fundamental graph traversal technique that explores all nodes at the present depth before moving on to nodes at the next depth level.
Guarantees finding the shortest path in an unweighted graph.
Explores neighbors level by level.
Suitable for tree and graph traversal problems.

British museum search.c
maps all possible ways and paths to travers from source to goal

BranchAndBound.c
Standard implementation of the Branch and Bound algorithm, which systematically explores all possible solutions and prunes suboptimal paths.
Guarantees finding the optimal solution.


DepthFirstSearch.c
A basic implementation of Depth-First Search, a fundamental graph traversal algorithm.
Explores as deep as possible along each branch before backtracking.

HillClimbing.c
Only one such solution is possible. works based on heuristics how close is the goal towards the node

Oracle.c
A simple oracle-finding algorithm that attempts to find the best solution in a decision problem.
Explores the search space to find an optimal oracle.


CIA2 - Gaming Adversarial Algorithm

AlphaBetaPruning.c
Implementation of the Alpha-Beta Pruning algorithm, an optimization technique for the Minimax algorithm that reduces the number of nodes evaluated.
Prunes branches in the game tree that don’t influence the final decision.
More efficient than standard Minimax.

Minimax
Implementation of the Minimax algorithm, which provides an optimal move for the player assuming the opponent plays optimally.
Evaluates all possible moves to find the best outcome.
