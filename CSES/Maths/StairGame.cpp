#include <stdio.h>
int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        
        //              v - multiplying the amount so that it becomes accurate to nim's game heaps  
        // g[1] = 0 * s[1]
        // g[2] = 1 * s[2]
        // g[3] = 0 * s[3]
        // g[4] = 1 * s[4]
        // g[n] = mex(g[n-1]) * s[n]

        int x, ns = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &x);
            ns ^= x*!(i&1);
        }
        if(ns) puts("first");
        else puts("second");
    }
    return 0;
}