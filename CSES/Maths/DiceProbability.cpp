#include <stdio.h>

constexpr int maxN = 1e2+1;
int n, a, b;
double dp[maxN][maxN*6];
int main() {
    scanf("%d%d%d", &n, &a, &b);

    dp[0][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int s = i; s <= 6*i; s++)
            for(int d = 1; d <= 6; d++)
                if(s >= d)
                    dp[i][s] += dp[i-1][s-d]/6;
    
    double p = 0;
    for(int i = a; i <= b; i++) p += dp[n][i];
    printf("%.6lf\n", p);

    /*
        0 0 0 0 0 0 0 0 0 0 0 0 0 0
        0 1 1 1 1 1 1 0 0 0 0 0 0 0
        0 0 1 2 3 4 5 6 5 4 3 2 1 0
    */
   
    return 0;
}