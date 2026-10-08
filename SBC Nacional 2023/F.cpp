#include <stdio.h>
#include <vector>
#include <set>
using ll = long long;

ll n;
void solve() {
    if(n == 2) { puts("*"); return; }
    auto ispb = [](ll b) {
        std::vector<ll> ds;
        ll t = n;
        while(t) {
            ds.push_back(t%b);
            t /= b;
        }
        for(int i = 0; i < ds.size()/2; i++) if(ds[i] != ds[ds.size()-i-1]) return false;
        //printf("b(%lld): ", b);
        //for(int i = 0; i < ds.size(); i++) printf("%lld ", ds[i]); putchar('\n');
        return true;
    };
    std::set<ll> bases;
    for(ll b = 2; b < std::min<ll>(n, 2e6); b++) {
        if(ispb(b)) bases.insert(b);
    }

    for(ll d = 1; d*d <= n; d++) {
        if(n%d) continue;
        if((d+1)*d < n) bases.insert(n/d-1); // d must be smaller than the base
        //if(d > 2 && d <= d-1) bases.insert(d-1);
    }
    for(ll b : bases) printf("%lld ", b);
    putchar('\n');
}

int main() {
    scanf("%lld", &n);
    solve();
    return 0;
}