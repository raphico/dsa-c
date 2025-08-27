#include <stdio.h>

int factorial(int n);

int main() { printf("%d\n", factorial(3)); }

int factorial(int n) {
    if (n == 1) {
        return n;
    }

    return n * factorial(n - 1);
}