#include <bits/stdc++.h>
#include <vector>
using ll = long long;
constexpr int maxN = 3e3+4;
constexpr ll INF = 1e18;
int n, k, a[maxN];
ll prfx[maxN];
//ll dp[maxN][maxN];
/*
ll ms(int i, int s) {
    if(i == n) return INF*(s != k);
    if(s == k) return INF;
    if(dp[i][s]+1) return dp[i][s];
    
    ll mn = INF;
    for(int j = i; j < n; j++) {
        ll v = prfx[j+1]-prfx[i];
        mn = std::min(mn, ms(j+1, s+1)+v*v);
    }
    
    return dp[i][s] = mn;
}
*/

/*
ll ms() {
    memset(dp, 0, sizeof(dp));
    for(int s = 0; s <= k; s++)
        dp[s][n] = INF*(s != k);
    for(int i = 0; i < n; i++)
        dp[k][i] = INF;
    
    for(int s = k-1; s >= 0; s--)
        for(int i = n-1; i >= 0; i--) {
            ll mni = INF;
            for(int j = i+1; j <= n; j++) {
                ll v = prfx[j]-prfx[i];
                mni = std::min(mni, dp[s+1][j]+v*v);
            }
            dp[s][i] = mni;
        }
    return dp[0][0];
}
*/

/*
ll ms() {
    memset(dp, 0, sizeof(dp));
    for(int s = 1; s <= k; s++)
        dp[s][0] = INF*(s != k);
    for(int i = 1; i <= n; i++)
        dp[0][i] = INF;
    
    for(int s = 1; s <= k; s++)
    for(int i = 1; i <= n; i++) {
        ll mni = INF;
        for(int j = i-1; j >= 0; j--) {
            ll v = prfx[i]-prfx[j];
            mni = std::min(mni, dp[s-1][j]+v*v);
        }
        dp[s][i] = mni;
    }
    return dp[k][n];
}
*/

ll cost(int l, int r) {
    ll v = (prfx[r]-prfx[l-1]);
    return v*v;
}

std::vector<ll> dp[2];
void dnc(int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = (l+r) >> 1;
    //printf("%d %d => %d | %d %d\n", l, r, mid, optl, optr);
    std::pair<ll, int> best = {INF, -1};
    for(int j = optl; j <= std::min(mid, optr); j++)
        best = std::min(best, {dp[0][j-1] + cost(j, mid), j});
    dp[1][mid] = best.first;
    int opt = best.second;
    dnc(l, mid-1, optl, opt);
    dnc(mid+1, r, opt, optr);
}

ll ms() {
    dp[0].assign(maxN, 0);
    dp[1].assign(maxN, 0);
    for(int i = 1; i <= n; i++) dp[0][i] = cost(0, i);
    for(int s = 1; s < k; s++) {
        dnc(1, n, 1, n);
        dp[0] = dp[1];
    }
    return dp[0][n];
}

int main() {
    //memset(dp, -1, sizeof(dp));
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    for(int i = 0; i < n; i++) prfx[i+1] = prfx[i] + a[i];
    printf("%lld\n", ms());
    return 0;
}