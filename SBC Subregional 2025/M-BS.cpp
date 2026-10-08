#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <array>
#include <set>
#include <string.h>
#include <bitset>
#include <numeric>
#include <unordered_set>
#include <random>
#include <chrono>

using ll = long long;
using pll = std::pair<ll,ll>;
using pii = std::pair<int,int>;
constexpr int maxN = 1e5+4, maxLOG = 20, INF = 1e9+2, MOD = 1e9+7;
constexpr ll LLINF = 1e18;
constexpr double PI = 3.14159265358979323846;
constexpr double DEG2RAD = PI/180.0;

using i128 = ll;

#define f_io() \
    std::ios::sync_with_stdio(0);
 
#ifndef ONLINE_JUDGE
#define DEBUG_H
#include "Debug.h"
#else
    #define dbgf(fmt, x)
    #define p_vi(v)
    #define dbgvi(v)
    #define dbgmi(mtx, rows)
    #define p_v(v)
    #define dbgv(v)
    #define dbgm(m)
    #define dbg(...)
    #define dbg2(...)
    #define dbgbin(n)
#endif

int msb(ll x) {
    for(int i = 63; i >= 0; i--)
        if(x&(1LL<<i)) return i;
}

ll binpow(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

ll modinv(ll x) { // Fernat's Little Theorem
    return binpow(x, MOD - 2)%MOD;
}

struct P {
    int a, b;
    bool operator<(const P& other) const {
        if(this->a != other.a) return this->a < other.a;
        return this->b > other.b;
    }
};


int n, q, k;
int a[maxN], t[maxN];
bool can(ll minv) {
    int idx = -1;
    for(int i = 0; i < n; i++) if(a[i] < minv) idx = i;
    if(idx == -1) return true;
    for(int i = 0; i < n; i++) t[i] = a[i];
    for(int i = 0; i < k && idx >= i; i++) t[idx-i] += k-i;
    for(int i = 0; i < n; i++) if(t[i] < minv) return false;
    return true;
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    ll l = 1, r = 1e9+k+1, v = 0;
    while(l <= r) {
        ll m = (l+r) >> 1;
        if(can(m)) { l = m+1; v = m; }
        else r = m-1;
    }
    printf("%lld\n", v);
    return 0;
}