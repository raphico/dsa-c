## Recursion

Recursion is a programming technique where a function solves a problem by calling itself with a smaller input. A recursive function has two main parts:

- A base case that ends the recursion
- A recursive case that calls the function again with a smaller input

The result builds up as the recursion unwinds

An example using recursion:

```c
int factorial(int n) {
    if (n == 1) {
        return n;
    }

    return n * factorial(n - 1);
}

factorial(3);
```

In the call stack, we have:

- `factorial(3)` needs `3 * factorial(2)`
- `factorial(2)` needs `2 * factorial(1)`
- `factorial(1)` hits the base case and returns 1

Now unwinding:

- `factorial(2)` becomes `2 * 1 = 2`
- `factorial(3)` becomes `3 * 2 = 6`

so the final result is 6
