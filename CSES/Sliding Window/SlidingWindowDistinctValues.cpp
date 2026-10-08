 #include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

constexpr int maxN = 2e5+4;
int a[maxN];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    std::map<int, int> fq;
    int d = 0;
    for(int i = 0; i < k; i++) if(fq[a[i]]++ == 0) d++;
    for(int i = k; i <= n; i++) {
        printf("%d ", d);
        if(--fq[a[i-k]] == 0) d--;
        if(fq[a[i]]++ == 0) d++;
    }
    return 0;
}