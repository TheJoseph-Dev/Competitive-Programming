#include <stdio.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
// Count the minimum number of coins required to achieve a certain sum
/*
    f(s) = {
        cnt = 10^6
        for i in arr
            cnt = MIN(cnt, f(s-i))
        return cnt
    }
*/

/*
    1 <= n <= 100
    1 <= x <= 10^6
    1 <= ci <= 10^6
*/

/*
int memo[1000001] = {0};
int minCoins(int sum, int arr[101], int n) {
    if(sum < 0) return 1e6;
    if(sum == 0) return 0;
    if(memo[sum]) return memo[sum];
    int cnt = 1e6;
    for(int i = 0; i < n; i++)
        cnt = MIN(cnt, minCoins(sum-arr[i], arr, n) + 1);

    return memo[sum] = cnt;
}
*/

/*
    [1, 5, 7]
    0 1 2 3 4 5 6 7 8 9 10 11
    0 1 2 3 4 1 2 1 2 3  2  3
*/

#define MAXC 1e6+5
int dp[1000001];
int minCoins(int sum, int arr[101], int n) {
    dp[0] = 0;
    for(int s = 1; s <= sum; s++) dp[s] = MAXC;

    for(int s = 1; s <= sum; s++) {
        for(int i = 0; i < n; i++)
            if(s >= arr[i]) dp[s] = MIN(dp[s-arr[i]] + 1, dp[s]);
    }

    return dp[sum];
}

int main() {

    int n, sum, arr[101];
    scanf("%d%d", &n, &sum);

    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);
    
    int mc = minCoins(sum, arr, n);
    printf("%d\n", (mc == MAXC ? -1 : mc));

    return 0;
}