#include <stdio.h>

constexpr int maxN = 101;

int main() {

    int n;
    scanf("%d", &n);

    int C[maxN][maxN], dist[maxN][maxN];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            scanf("%d", C[i]+j);
            dist[i][j] = C[i][j];
        }

    bool removed[maxN][maxN] = {{false}};
    int count = 0;
    for(int k = 0; k < n && count != -1; k++)
        for(int i = 0; i < n && count != -1; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j || i == k || j == k) continue;
                if(dist[i][j] > dist[i][k] + dist[k][j]) { count = -1; break; }
                if(dist[i][j] == dist[i][k] + dist[k][j] && !removed[i][j]) { // Redundant Direct Path
                    count++; 
                    removed[i][j] = removed[j][i] = true;
                }
            }
        }
    
    printf("%d\n", count);

    return 0;
}