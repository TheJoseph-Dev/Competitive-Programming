#include <stdio.h>

constexpr int maxN = 1e6+1;

int divisors[maxN] = {0};
void countDivisors() {
    for(int i = 1; i < maxN; i++)
        for(int j = i; j < maxN; j += i)
            divisors[j]++;
}

int main() {

    int n;
    scanf("%d", &n);

    countDivisors();

    int x;
    while(n--) {
        scanf("%d", &x);
        printf("%d\n", divisors[x]);
    }

    return 0;
}