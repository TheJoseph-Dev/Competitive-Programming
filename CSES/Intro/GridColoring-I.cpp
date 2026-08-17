#include <stdio.h>
#include <algorithm>
constexpr int maxN = 5e3+2;
int n, m;
char grid[maxN][maxN];
char mtx[maxN][maxN];
int main() {
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++) {
            bool good[4];
            for(int k = 0; k < 4; k++) good[k] = (i == 0 || mtx[i-1][j] != 'A'+k) && (j == 0 || mtx[i][j-1] != 'A'+k) && grid[i][j] != 'A'+k;
            for(int k = 0; k < 4; k++) if(good[k]) mtx[i][j] = 'A'+k;
        }

    for(int i = 0; i < n; i++) { for(int j = 0; j < m; j++) putchar(mtx[i][j]); putchar('\n'); }
    return 0;
}