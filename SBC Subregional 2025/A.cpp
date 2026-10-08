#include <stdio.h>
#include <algorithm>

constexpr int maxN = 1e3+2;
int main() {

    int n,m,mtx[maxN][maxN];
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", mtx[i]+j);

    long long s = 0;
    for(int j = 0; j < m; j++) {
        int mx = 0;
        for(int i = 0; i < n; i++)
            mx = std::max(mx, mtx[i][j]);
        s += mx;
    }

    printf("%lld\n", s);
    return 0;
}