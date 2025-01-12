#include <stdio.h>

constexpr int maxN = 2e5 + 1, maxLOG = 31;
int tp[maxLOG][maxN];

int main() {

    int n, q;
    scanf("%d%d", &n, &q);

    for(int p = 1; p <= n; p++)
        scanf("%d", tp[0]+p);

    for(int i = 1; i < maxLOG; i++)
        for(int p = 1; p <= n; p++)
            tp[i][p] = tp[i-1][tp[i-1][p]];

    while(q--) {
        int node, k;
        scanf("%d%d", &node, &k);

        for(int i = 30; i >= 0; i--)
            if(k&(1<<i)) node = tp[i][node];

        printf("%d\n", node);
    }

    return 0;
}