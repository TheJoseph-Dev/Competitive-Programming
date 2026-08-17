#include <stdio.h>
#include <algorithm>
constexpr int maxN = 21;
int main() {
    int n, a[maxN];
    long long t = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) { scanf("%d", a+i); t+=a[i]; }
    long long mn = 2e9;
    for(int mask = 0; mask < (1<<n); mask++) {
        long long s = 0;
        for(int j = 0; j < n; j++) if(mask&(1<<j)) s+=a[j];
        mn = std::min(mn, llabs(t-2*s));
    }
    printf("%lld\n", mn);
    return 0;
}