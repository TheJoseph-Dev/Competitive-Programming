#include <stdio.h>
 
 /*
    n: 1
    0: 1
    1: 1
    
    n: 3
    0: 1
    1: 3
    2: 3
    3: 1
    
    n: 8
    0: 1
    1: 8
    2: 28
    3: 
    8: 1
    
    Pascal's Triangle
    R: Sum(freq[b]/2) => 2^bitcount(n)
 */
 
int main() {
    long long unsigned n;
    scanf("%llu", &n);
    printf("%llu\n", (1LLU << __builtin_popcountll(n)));
    return 0;
}