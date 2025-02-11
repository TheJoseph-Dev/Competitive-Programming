#include <stdio.h>
#include <algorithm>

constexpr int maxN = 2e5+1;

int main() {

    int n;
    scanf("%d", &n);

    int coins[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", coins+i);

    std::sort(coins, coins+n);

    
    // Can represent all coins
    // 1 2 4 
    // Prfx: 1 3 7

    // Fails at 4
    // 1 2 5 
    // Prfx: 1 3 8

    long long prfx = 0;
    for(int i = 0; i < n && (coins[i] > prfx ? prfx+1 == coins[i] : true); i++) 
        prfx += coins[i];

    printf("%lld\n", prfx+1);

    return 0;
}