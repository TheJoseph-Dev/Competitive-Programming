#include <stdio.h>
#include <vector>

#define MOD 1000000007

int dp[1024][1001];

// Genereates the next possible masks given the current mask
void genMasks(int i, int cMask, int nMask, int n, std::vector<int>& masks) {
    if(i == n) { masks.push_back(nMask); return; }

    // Skip
    if(cMask&(1 << i)) genMasks(i+1, cMask, nMask, n, masks);
    else {
        // 1x2
        if(i+1 < n && !(cMask&(1 << (i+1)))) 
            genMasks(i+2, cMask, nMask, n, masks);

        // 2x1
        genMasks(i+1, cMask, nMask | (1 << i), n, masks);
    }
}

int countTilings(int i, int mask, int n, int m) {
    if(i == m) return (mask == 0);
    if(dp[mask][i] != -1) return dp[mask][i];

    if(mask+1 == (1<<n)) return dp[mask][i] = countTilings(i+1, 0, n, m)%MOD;

    std::vector<int> nextMasks;
    genMasks(0, mask, 0, n, nextMasks);

    int count = 0;
    for(int nextMask : nextMasks)
        count = (count + countTilings(i+1, nextMask, n, m))%MOD;

    return dp[mask][i] = count;
}

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    for(int i = 0; i < (1 << n); i++)
        for(int j = 0; j < m; j++)
            dp[i][j] = -1;

    printf("%d\n", countTilings(0, 0, n, m));

    return 0;
}