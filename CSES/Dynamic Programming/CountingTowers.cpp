#include <stdio.h>

#define MOD 1000000007

#define ll long long

ll dp[1000001][2];

/*
    There are only 8 kinds of configurations your subtower can be.

    --  __  --  __  |-  -|  ||  Full Box
    --  --  __  __  |-  -|  ||   
    11  10  01  00  11  11  11     00

    The transition lies on the fact that you have:
        - 2 ways to go from a horizontally divided subtower to a horizontally divided subtower (00)
        - 4 ways to go from a vertically divided subtower to a vertically divided subtower (11)
        - 1 way to go from a horizontally divided subtower to a vertically divided subtower (01)
        - 1 way to go from a vertically divided subtower to a horizontally divided subtower (10)
*/

void countTowers() {
    dp[1][0] = dp[1][1] = 1;
    for(int h = 2; h <= 1000000; h++) {
        dp[h-1][0] %= MOD; dp[h-1][1] %= MOD;
        dp[h][0] = (2*dp[h-1][0] + dp[h-1][1])%MOD;
        dp[h][1] = (4*dp[h-1][1] + dp[h-1][0])%MOD;
    }
}

int getTowerCount(int n) {
    return (dp[n][0] + dp[n][1])%MOD;
}

int main() {

    int t;
    scanf("%d", &t);
    countTowers();

    while(t--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", getTowerCount(n));
    }

    return 0;
}