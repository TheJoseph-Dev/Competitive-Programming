#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
// 1 <= n <= 10^6 

int biggestDigit(int n) {
    int d = 0;
    while(n) {
        d = MAX(d, n%10);
        n /= 10;
    }
    return d;
}

// Greedy
int removeDigits(int n) {
    int steps = 0;
    while(n) {
        steps++;
        n -= biggestDigit(n);
    }

    return steps;
}

int main() {

    int n;
    scanf("%d", &n);

    printf("%d\n", removeDigits(n));

    return 0;
}