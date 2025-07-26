#include <stdio.h>
constexpr int maxN = 1e2+1, maxG = 1e6+1;
int main() {
    int n,k;
    scanf("%d%d", &n, &k);
    int p[maxN];
    for(int i = 0; i < k; i++) scanf("%d", p+i);
    /*
        g[0] = 0
        g[n] = mex{g[n-p[i]], g[n-p[i+1]], ..., g[n-p[k]]}
    */
    
    int g[maxG] = {0};
    for(int i = 1; i <= n; i++) {
        bool seen[maxN] = {0}; // mex can't exceed k
        for(int j = 0; j < k; j++)
            if(p[j] <= i) seen[g[i-p[j]]] = true;
        
        while(seen[g[i]]) g[i]++;
        if(g[i]) putchar('W');
        else putchar('L');
    }
 
    return 0;
}