#include <stdio.h>

constexpr int maxN = 5e3+1;
int g[maxN];
void grundy() {
    g[1] = g[2] = 0;
    for(int i = 3; i < maxN; i++) {
        bool seen[maxN] = {false};
        for(int j = 1; j <= i/2 - !(i&1); j++)
            seen[g[j]^g[i-j]] = true;
        
        while(seen[g[i]]) g[i]++;
    }
}

int main() {
    grundy();
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);

        /*
            In a disjunctive game composed of multiple independent subgames,
            the Grundy number of the combined position is the bitwise XOR
            of the Grundy numbers of the subgames. 
            Because you're basically just creating 2 nim's heaps,
            and you solve them by XOR.
        */
        // g[1] = 0
        // g[2] = 0
        // g[3] = 1 W(1,2) => mex{g[1]^g[2]} = 1
        // g[4] = 0 L(1,3) => mex{g[1]^g[3]} = 0
        // g[5] = 1 W(1,4) L(2,3) => mex{g[1]^g[4], g[2]^g[3]} = 2
        // g[6] = 1 L(1,5) W(2,4) => mex{g[1]^g[5], g[2]^g[4]} = 1
        // g[7] = 0 L(1,6) L(2,5) L(3,4) => mex{g[1]^g[6], g[2]^g[5], g[3]^g[4]} = 0
        // g[8] = 1 W(1,7) L(2,6) W(3,5) => mex{g[1]^g[7], g[2]^g[6], g[3]^g[5]} = 2
        // g[9] = 1 L(1,8) W(2,7) W(3,6) L(4,5) => mex{g[1]^g[8], g[2]^g[7], g[3]^g[6], g[4]^g[5]} = 1
        // g[10] = 0 L(1,9) L(2,8) L(3,7) L(4,6) => mex{g[1]^g[9], g[2]^g[8], g[3]^g[7], g[4]^g[6]} = 0

        if(n > 5000 || g[n]) puts("first");
        else puts("second");
    }
    return 0;
}