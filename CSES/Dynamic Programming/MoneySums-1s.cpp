#include <stdio.h>

bool dp[100001];
void moneySums(int n, int coins[101]) {
    int sum = 0;
    for(int i = 0; i < n; i++) sum += coins[i];
    for(int i = 1; i <= sum; i++) dp[sum] = 0;
    dp[0] = 1;

    int lSum = 0;
    for(int i = 1; i <= n; i++) {
        for(int s = lSum; s >= 0; s--)
            dp[s+coins[i-1]] = dp[s+coins[i-1]] | dp[s];
        lSum += coins[i-1];
    }
    
    int ms = 0;
    for(int s = 1; s <= sum; s++) ms += dp[s];
    printf("%d\n", ms);
    for(int s = 1; s <= sum; s++) if(dp[s]) printf("%d ", s);
}

int main() {

    int n, coins[101];
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", coins+i);

    moneySums(n, coins);
    return 0;
}