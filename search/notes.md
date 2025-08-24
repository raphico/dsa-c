## Linear Search

Linear search is a brute-force algorithm that:

1. check each element in the array sequentially
2. compares it with the target element
3. and either stops when the target is found or the array is exhausted

### Time complexity:

In the worst case, when the target is at the end or not in the array to begin with, every element is checked.
So it has a O(n)

In the best case, the target is the first element in the array.
So linear search has a Ω(1)

## Binary Search

Binary search is a divide-and-conquer algorithm that works on sorted arrays.
It repeatedly checks the middle element:

1. if it's the target, the search is over
2. if it's larger than the target, we search the left-half
3. if it's smaller than the target, we search the right-half
   This is repeated until the target is found or there are no more search interval

### Time complexity:

Each step cuts the search interval in half. In the worst case, the total number of steps is how many times 2 can divide n before reaching 1, which is log2(n).
So binary search has a O(logn). In the best case, the middle element is the target. So it has a Ω(1)

## The Two Crystal Balls puzzle

The problem is a search puzzle:

- You have a building with n floors
- You have two balls
- A ball will not break if dropped from a floor below a certain "breaking floor", but will always break if dropped from that floor or higher
- Once a ball breaks, you can't use it again
- The task is to find the exact breaking floor

1. The naive approaches:

   - linear search. This involves dropping the ball at each floor, from the bottom, one after the other, until the ball breaks. It is the simplest, but least efficient (worst case: n drops)

   - Binary search: jump to the middle floor, then half again. The problem is that if ball breaks early, you are stuck with one ball, and now have to check every floor below linearly (worst case: n/2 drops)

2. The balance idea: Jumping in bigger steps(√n), but not as big as binary search. When the first ball breaks, you then apply linear search from the last safe jump to the current floor the first ball broke.

## Why √n is chosen for the 2-ball problem

### Step 1: What happens if we pick a step size?

Suppose there are 100 floors. Imagine we decide to test **every 10th floor**:

- Drop ball 1 at floor 10, 20, 30, … until it breaks.
- Suppose it breaks at floor 40.
- Now we know the answer is between floor 31–39.
- Use ball 2 to check linearly (31, 32, …, 39).

👉 Worst case = 10 drops (to reach 40) + 9 drops (linear) = 19 drops.

### Step 2: What if we picked a bigger step?

Say step = 20:

- Drop at 20, 40, 60, 80, 100.
- Suppose it breaks at 100.
- Now we linearly check from 81 to 99 → 19 more drops.

👉 Worst case = 5 + 19 = 24 drops (worse!).

### Step 3: What if we picked a smaller step?

Say step = 5:

- Drop at 5, 10, 15, …, 100.
- Suppose it breaks at 100.
- Then we linearly check 96–99 → 4 more drops.

👉 Worst case = 20 + 4 = 24 drops (also worse).

### Step 4: Finding the sweet spot

So with step = 10, we needed at most **19 drops**.
With step = 20, it was **24**.
With step = 5, it was **24**.

Turns out the sweet spot is when step ≈ √100 = 10.
That minimizes the total drops.

### Step 5: General formula

For n floors, if we pick step size = k,

- First ball: n/k drops,
- Second ball: up to k drops,
- Worst case ≈ n/k + k.

This expression is minimized when k ≈ √n.

So the running time is **O(√n)**.
