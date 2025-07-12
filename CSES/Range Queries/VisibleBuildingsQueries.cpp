#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstring>
constexpr int maxN = 2e5+5, maxLOG = 18, INF = 1e9;

int arr[maxN], ngeR[maxLOG+1][maxN];
int main() {
    int n, q;
    scanf("%d%d", &n, &q);

    for(int i = 0; i < n; i++) scanf("%d", arr+i);
    
    memset(ngeR, -1, sizeof(ngeR));
    std::vector<int> monostk;
    for(int i = 0; i < n; i++) {
        while(!monostk.empty() && arr[monostk.back()] < arr[i]) {
            ngeR[0][monostk.back()] = i;
            monostk.pop_back();
        }
        monostk.push_back(i);
    }

    for(int i = 0; i < n; i++) if(ngeR[0][i] == -1) ngeR[0][i] = INF;
    for(int i = 1; i <= maxLOG; i++)
        for(int j = 0; j < n; j++) {
            if(ngeR[i-1][j] < INF) ngeR[i][j] = ngeR[i-1][ngeR[i-1][j]];
            else ngeR[i][j] = INF;
        }
    
    
    int a, b;
    while(q--) {
        scanf("%d%d", &a, &b);
        a--; b--;
        int idx = a, count = 1;
        for(int i = maxLOG; i >= 0; i--)
            if(ngeR[i][idx] <= b) {
                idx = ngeR[i][idx];
                count += (1<<i);
            }
        
        printf("%d\n", count);
    }

    return 0;
}