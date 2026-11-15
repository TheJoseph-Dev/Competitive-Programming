#include <stdio.h>
#include <bitset>

constexpr int maxN = 3e3 + 2;

char grid[maxN][maxN];
std::bitset<maxN> bm[26][maxN];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    for(int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            bm[grid[i][j] - 'A'][i].set(j);

    bool exists[26] = {};

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            if(i == j) continue;

            char idx = grid[i][j] - 'A';
            if(exists[idx]) continue;

            auto x = bm[idx][i] & bm[idx][j];

            if(x.any()) {
                x.reset(x._Find_first());
                exists[idx] = x.any();
            }
        }

    for(int i = 0; i < m; i++)
        puts(exists[i] ? "YES" : "NO");

    return 0;
}