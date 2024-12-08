#include <stdio.h>

#define ll long long

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/*
    1 <= n <= 5000
    -1e9 <= xi <= 1e9
*/

/*
    f(i, j, st) {
        if(i > j) return 0;
        
        if(st) return MAX(f(i+1, j, 0)+arr[i], f(i, j-1, 0) + arr[j])
        else return MIN(f(i+1, j, 0), f(i, j-1, 0))
    }
*/

#define INF 10e9+5

/*
ll memo[5001][5001][2];
ll rGame(int i, int j, bool player, ll nums[5001]) {
    if(i > j) return 0;
    if(memo[i][j][player] != INF) return memo[i][j][player];
    ll gL = rGame(i+1, j, !player, nums) + nums[i]*(player), gR = rGame(i, j-1, !player, nums) + nums[j]*(player);
    if(player) return memo[i][j][player] = MAX(gL, gR);
    else return memo[i][j][player] = MIN(gL, gR);
}
*/

ll dp[5002][2][2];
ll rGame(ll nums[5001], int n) {
    for(int i = 0; i <= n; i++)
        dp[i][0][0] = dp[i][1][0] = dp[i][1][1] = dp[i][1][1] = 0;
    
    bool sj = 1;
    for(int j = 1; j <= n; j++) {
        for(int i = j; i >= 1; i--) {
            dp[i][sj][1] = MAX(dp[i+1][sj][0] + nums[i-1], dp[i][!sj][0] + nums[j-1]);
            dp[i][sj][0] = MIN(dp[i+1][sj][1], dp[i][!sj][1]);
        }
        sj = !sj;
    }

    return dp[1][!sj][1];
}

int main() {

    int n; 
    ll nums[5001];
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%lli", nums+i);
    
    printf("%lli\n", rGame(nums, n));

    return 0;
}