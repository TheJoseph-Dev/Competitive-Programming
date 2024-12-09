#include <stdio.h>

#define INF 0x3f3f3f3f3f3fLL

#define ll long long
#define MIN(a,b) ((a) < (b) ? (a) : (b))

int main() {

    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);

    ll dist[501][501];
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= n; j++)
            dist[i][j] = INF * (i != j);


    int a, b, w;
    while(m--) {
        scanf("%d%d%d", &a, &b, &w);
        dist[a][b] = dist[b][a] = MIN(dist[a][b], w);
    }

    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = MIN(dist[i][j], dist[i][k] + dist[k][j]);

    while(q--) {
        scanf("%d%d", &a, &b);
        printf("%lli\n", dist[a][b] == INF ? -1 : dist[a][b]);
    }

    return 0;
}