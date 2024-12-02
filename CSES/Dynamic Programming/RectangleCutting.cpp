#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/*
         0 1 2 3 4 5
      
    0    0 0 0 0 0 0
    1    0 0 1 2 3 4
    2    0 1 0 2 1 3
    3    0 2 2 0 4 3
    4    0 3 1 4 0 5
    5    0 4 3 3 5 0
*/

int countSquares(int a, int b) {
    if(a == b) return 0;

    int dp[501][501];
    for(int i = 0; i <= MAX(a,b); i++) {
        dp[i][0] = dp[0][i] = dp[i][i] = 0;
        if(i >= 2) dp[1][i] = dp[i][1] = i-1;
    }

    for(int i = 2; i <= MIN(a,b); i++)
        for(int j = i+1; j <= MAX(a,b); j++) {

            int cnt = 501*501;
            for(int c = 1; c < j; c++)
                cnt = MIN(dp[MIN(i,j-c)][MAX(i,j-c)] + dp[MIN(i,c)][MAX(i,c)] + 1, cnt);

            for(int c = 1; c < i; c++)
                cnt = MIN(dp[MIN(j,i-c)][MAX(j,i-c)] + dp[MIN(j,c)][MAX(j,c)] + 1, cnt);

            dp[i][j] = cnt;
        }
    
    return dp[MIN(a,b)][MAX(a,b)];
}

int main() {

    int a, b;
    scanf("%d%d", &a, &b);

    printf("%d\n", countSquares(a, b));

    return 0;
}