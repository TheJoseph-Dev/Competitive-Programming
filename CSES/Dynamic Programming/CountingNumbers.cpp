#include <stdio.h>
#include <string>

#define ll long long

ll dp[19][2][11];

ll countNums(int i, bool tight, int lD, const std::string& limit) {
    if(i == -1) return 1;

    if(dp[i][tight][lD] != -1) return dp[i][tight][lD];
    int k = tight ? (limit[limit.size()-i-1]-'0') : 9;

    ll count = 0;
    for(int d = 0; d <= k; d++) {
        if(d == lD-1) continue;
        count += countNums(i-1, tight && (d == k), (d == 0 && lD == 0 ? 0 : d+1), limit); 
    }

    return dp[i][tight][lD] = count;
}

void dpset() {
    for(int i = 0; i < 19; i++)
        for(int d = 0; d <= 10; d++) {
            dp[i][0][d] = -1; dp[i][1][d] = -1;
        }
}

int main() {

    ll a, b;
    scanf("%lli%lli", &a, &b);

    std::string sA = std::to_string(a-1), sB = std::to_string(b);
    dpset();
    ll rV = countNums(sB.size()-1, true, 0, sB);
    dpset();
    ll lV = countNums(sA.size()-1, true, 0, sA);
    printf("%lli\n", rV-lV);

    return 0;
}