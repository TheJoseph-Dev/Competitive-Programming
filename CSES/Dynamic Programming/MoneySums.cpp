#include <stdio.h>

bool dp[2][100001];
void moneySums(int n, int coins[101]) {
    int sum = 0;
    for(int i = 0; i < n; i++) sum += coins[i];
    for(int i = 1; i <= sum; i++) dp[0][i] = 0;
    dp[0][0] = 1;

    bool si = 1;
    for(int i = 1; i <= n; i++) {
        for(int s = sum; s >= 0; s--) {
            if(s >= coins[i-1]) dp[si][s] = dp[!si][s-coins[i-1]] | dp[!si][s];
            else dp[si][s] = dp[!si][s];
        }

        si = !si;
    }
    
    int ms = 0;
    for(int s = 1; s <= sum; s++) ms += dp[!si][s];
    printf("%d\n", ms);
    for(int s = 1; s <= sum; s++) if(dp[!si][s]) printf("%d ", s);
}

int main() {

    int n, coins[101];
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", coins+i);

    moneySums(n, coins);
    return 0;
}