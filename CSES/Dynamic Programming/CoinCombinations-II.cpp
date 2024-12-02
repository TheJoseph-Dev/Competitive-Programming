#include <stdio.h>

#define MOD 1000000007

/*
    1 <= n <= 100
    1 <= x <= 10^6
    1 <= ci <= 10^6
*/

// Coin Combinations I => Test all coins options to a given sum
// Coin Combinations II => Consider each coin at a time, thus, you only count a possible sum once
/*
    [2, 3, 5]
    0 1 2 3 4 5 6 7 8 9
    1 0 1 1 1 2
*/

int dp[1000001] = {0};
int coinCount(int sum, int coins[101], int n) {
    dp[0] = 1;
    for(int i = 0; i < n; i++)
        for(int s = coins[i]; s <= sum; s++)
            dp[s] = (dp[s] + dp[s - coins[i]]) % MOD;

    return dp[sum];
}

int main() {

    int n, sum, coins[101];
    scanf("%d%d", &n, &sum);

    for(int i = 0; i < n; i++)
        scanf("%d", coins+i);
    
    printf("%d\n", coinCount(sum, coins, n));

    return 0;
}