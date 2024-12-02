#include <stdio.h>

#define MOD 1000000007

bool inBounds(int x, int y, int n) {
    return 0 <= x && x < n && 0 <= y && y < n;
}

/*
int memo[1001][1001] = {{0}};
int countPaths(int x, int y, char grid[1001][1001], int n) {
    if(!inBounds(x,y,n) || grid[x][y] == '*') return 0;
    if(x == n-1 && y == n-1) return 1;
    if(memo[x][y]) return memo[x][y];

    int paths = countPaths(x+1, y, grid, n)%MOD + countPaths(x, y+1, grid, n)%MOD;
    return memo[x][y] = paths;
}
*/

int dp[1001][1001] = {{0}};
int countPaths(char grid[1001][1001], int n) {
    if(grid[n-1][n-1] == '*') return 0;
    dp[n-1][n-1] = 1;
    for(int i = n-1; i >= 0; i--) {
        for(int j = n-1; j >= 0; j--) {
            if(i == n-1 && j == n-1) continue;
            dp[i][j] = 0;
            if(grid[i][j] == '*') continue;
            if(inBounds(i+1, j, n)) dp[i][j] = (dp[i][j]+dp[i+1][j])%MOD;
            if(inBounds(i, j+1, n)) dp[i][j] = (dp[i][j]+dp[i][j+1])%MOD;
        }
    }

    return dp[0][0];
}

int main() {

    int n;
    scanf("%d", &n);

    char grid[1001][1001];
    for(int i = 0; i < n; i++)
        scanf("%s", grid[i]);

    printf("%d\n", countPaths(grid, n));

    return 0;
}