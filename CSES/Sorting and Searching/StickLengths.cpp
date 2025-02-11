#include <stdio.h>
#include <math.h>
#include <algorithm>

constexpr int maxN = 2e5+1;

int main() {

    int n;
    scanf("%d", &n);

    int sLen[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", sLen+i);

    std::sort(sLen, sLen+n);

    long long cost = 0;
    for(int i = 0; i < n; i++)
        cost += abs(sLen[n>>1]-sLen[i]);

    printf("%lld\n", cost);

    return 0;
}