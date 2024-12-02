#include <stdio.h>

#define MOD 1000000007

/*
int memo[1000001];
int coinCount(int sum, int coins[101], int n) {
    if(sum < 0) return 0;
    if(sum == 0) return 1;
    if(memo[sum]) return memo[sum];

    int cnt = 0;
    for(int i = 0; i < n; i++)
        cnt += coinCount(sum-coins[i], coins, n);

    return memo[sum] = cnt;
}
*/

/*
    1 <= n <= 100
    1 <= x <= 10^6
    1 <= ci <= 10^6
*/

/*
    [2, 3, 5]
    0 1 2 3 4 5 6 7 8 9
    1 0 1 1 1 3
*/

int dp[1000001] = {0};
int coinCount(int sum, int coins[101], int n) {
    dp[0] = 1;
    for(int s = 1; s <= sum; s++) {
        for(int i = 0; i < n; i++)
            if(s >= coins[i]) dp[s] = (dp[s] + dp[s-coins[i]])%MOD;
    }

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