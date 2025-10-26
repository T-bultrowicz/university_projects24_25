#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// Comparison function for sorting integers in ascending order
int less_int(const void *a, const void *b) {
    int _a = *(int*)a;
    int _b = *(int*)b;
    if (_a < _b) return -1;
    else if (_a == _b) return 0;
    else return 1;
}

int main() {
    int r, n, k, d;

    // Read input values
    scanf("%d%d%d%d", &r, &n, &k, &d);

    // Set the random seed
    srand(r);

    // Print the number of elements to be processed
    printf("%d\n", n);

    // Dynamically allocate an array to store random numbers
    int *t = (int *)malloc(n * sizeof(int));

    // Generate n random integers in the range [0, d-1]
    for (int i = 0; i < n; ++i)
        t[i] = rand() % d;

    // Sort the array in ascending order
    qsort(t, n, sizeof(int), less_int);

    // Print the results with an additional random value between 1 and k
    for (int i = 0; i < n; ++i)
        printf("%d %d\n", rand() % k + 1, t[i]);

    // Free the allocated memory
    free(t);

    return 0;
}
