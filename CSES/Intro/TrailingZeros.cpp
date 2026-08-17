#include <stdio.h>
#include <algorithm>
// 1 2 3 4 5 6 7 8 9 10 15 20 25
// 5: 6

int main() {
    int n;
    scanf("%d", &n);
    int c = 0;
    for(int p = 5; p <= n; p *= 5) c += n/p;
    printf("%d\n", c);
    return 0;
}