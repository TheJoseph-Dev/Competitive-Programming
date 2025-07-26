#include <stdio.h>

int main() {
    int t, n;
    scanf("%d", &t);

    while(t--) {
        scanf("%d", &n);

        /*
            If the parity of all numbers is even:
                Second player can always keep it even, so it is losing state
            Otherwise:
                First player can always keep one odd, so it is a winning state
            
            Grundy numbers? g[bitmask] where bitmask is the state = (h1 % 2, h2 % 2, ..., hn % 2)
            g[0] = 0
            g[1] = 1
            g[2] = 1
            g[3] = 1
            g[4] = 1
            ...
            g[n] = 1
            Because every bitmask > 0 has a way to transition to g[0], so ? -> L = W
        */

        int x;
        bool odd = false;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            odd |= (x&1);
        }
        
        if(odd) puts("first");
        else puts("second");
    }
    return 0;
}