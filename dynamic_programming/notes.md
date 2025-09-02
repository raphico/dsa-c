# Dynamic programming

Dynamic programming is an algorithm technique for solving complex problem by:

1. Breaking the problem into smaller subproblems
2. recognizing overlapping subproblems (when the same subproblem occur multiple times)
3. solving each subproblem only once and storing its result (usually in a table or memo)
4. reusing the stored results to build up a solution to the larger problem efficiently

This prevents redundant computations, and can reduce exponential-time recursive solutions to polynomial time

Two common approaches in DP:

1. Top-down (Memoization): start with the original problem and recursively solve subproblems, cache results
2. Bottom-up (Tabulation): Iteratively solve smaller subproblems first, then combine them to solve larger ones
