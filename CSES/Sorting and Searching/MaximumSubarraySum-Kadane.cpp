#include <stdio.h>

constexpr int INF = 0x3f3f3f3f;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {

    int n;
    scanf("%d", &n);

    int x;
    long long maxGlobal = -INF, local = -INF;
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        local = MAX(local+x, x);
        maxGlobal = MAX(maxGlobal, local);
    }

    printf("%lld\n", maxGlobal);

    return 0;
}