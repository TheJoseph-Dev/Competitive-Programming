#include <stdio.h>
int main() {
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        int x, ns = 0;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            ns ^= (x%4);
        }
        if(ns) puts("first");
        else puts("second");
    }
    return 0;
}