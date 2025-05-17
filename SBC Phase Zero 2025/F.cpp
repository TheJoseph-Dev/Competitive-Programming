#include <iostream>
#include <algorithm>
#include <unordered_map>

constexpr int maxN = 1e3 + 1;
int n, nums[maxN];

long long dp[maxN][8001][5] = {0};
void count() {
    for(int i = 0;i <= n; i++) dp[i][0][0] = 1;
    for(int i = 1; i <= n; i++)
        for(int s = 0; s <= 8000; s++)
            for(int k = 1; k <= 4; k++) {
                dp[i][s][k] += dp[i-1][s][k];
                if(s + nums[i-1] <= 8000)
                    dp[i][s+nums[i-1]][k] += dp[i-1][s][k-1];
            }
}

int main() {
    int min = 1e6;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
        min = std::min(min, nums[i]);
    }
    min = abs(min);
    for (int i = 0; i < n; i++) nums[i] += min;
    count();
    
    //for(auto k : dp) if(k.first[1] < 60) printf("[%d, %d, %d] : %d\n", k.first[0], k.first[1], k.first[2], k.second);
    //for(int i= 0; i <= n; i++) printf("%d ", dp[{i,30,4}]);
    //printf("\n>%d\n", dp[{5, -9, 2}]);
    //putchar('\n');

    int q, x;
    scanf("%d", &q);
    while (q--) {
        scanf("%d", &x);
        printf("%lld\n", dp[n][x+4*min][4]);  
    }

    return 0;
}
