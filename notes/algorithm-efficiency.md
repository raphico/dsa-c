An algorithm is a precise description of how to solve a problem. There are two main ways to analyse the efficiency of the algorithm: Timing the algorithm or counting the number of basic operations(e.g., comparisons, swaps) it performs.

Timing the algorithm measures how long it takes to run, but measurement is influenced by external factors like CPU, background processes, memory, and compiler optimisations. While useful for bench-marking(evaluating performance by comparison with a standard), it is not reliable for comparing the efficiencies of algorithms across different machines or environments.

A more consistent method to evaluate the efficiency of an algorithm is to count the number of basic operation it performs. This is machine independent, and allows us to analyse how the algorithm behaves as the input size grows.

Every algorithm behave differently depending on the type of input. We typically analyse three main scenarios that can occur:

1. Best-case scenario: when the input causes the algorithm to run the fastest. For example, the best -case scenario in linear search is when the first element is the target
2. Worst-case scenario: when the input causes the algorithm to take the longest time to run. For example, the worst-case scenario in linear search is when the target is at the end or not found
3. Average-case scenario: is the expected performance of the algorithm over variety of input. While this is the most realistic measure of an algorithm efficiency, it is more difficult to calculate precisely

We use mathematical notations to describe how the number of operations grows with the input size. This is known as asymptotic analysis. The result of this analysis—the algorithm efficiency expressed in terms of growth rate—is the time complexity of the algorithm.

When someone asks: "What's the time complexity of an algorithm?" They are really asking the asymptotic behaviour of the algorithm as the input size grows, expressed using mathematical notations.

These mathematical notations include:

1. Big O notation: describes the upper-bound—how many operations it performs in the worst case scenario. For example, linear search as a O(n) because in the worst case scenario the algorithm checks every element
2. Big Ω notation: describes the lower bound—how many operation it performs in the best case scenario. For example, linear search as a Ω(1) because in the best case scenario the algorithm only checks one element
3. Big Θ: describes a tight bound—a scenario where the upper bound is equal to the lower bound
