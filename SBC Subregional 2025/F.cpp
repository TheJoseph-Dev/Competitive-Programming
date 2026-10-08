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

constexpr ll inv2 = (MOD+1)>>1;

struct P {
    ll a, b;
    bool operator<(const P& other) const {
        if(this->a != other.a) return this->a < other.a;
        return this->b > other.b;
    }
    void operator+=(P other) {
        if(this->b <= other.b) {
            ll f = other.b/this->b;
            //dbg(other.b, this->b);
            this->b = (b*f)%MOD;
            this->a = (a*f)%MOD;
            this->a = (a+other.a)%MOD;
        }
        else {
            ll f = this->b/other.b;
            //dbg(this->b, other.b);
            this->a = (this->a + (other.a * f)%MOD)%MOD;
        }
    }
    void half() { this->b = (b*2)%MOD; }
    P operator*(ll v) const {
        return {(this->a*v)%MOD,this->b};
    }
};


int n, q, k;
int x[maxN];
ll p[maxN], dp[maxN];
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 0; i < q; i++) scanf("%d", x+i);
    //p[0] = {7,4}; p[1] = {1,4};
    //p[0] = {11,4}; p[1] = {5,4}; p[2] = {1,1}; p[3] = {0,2};
    //p[0] = {3,2};
    //p[0] = {7,4}; p[1] = {1,1};
    
    // p[t] = \sum_{i=k+1}^q (1 / 2^(i-k+1)) * x[i]
    // p[t] = 2^(k-1) * \sum_{i=k+1}^q (1 / 2^i) * x[i]
    // p[t] = dp[k+1]
    // dp[i] = dp[i+1]/2 + x[i]/2 = (dp[i+1] + x[i])/2
    // dp[q] = 0
    dp[q] = 0;
    for(int i = q-1; i >= 0; i--) 
        dp[i] = (dp[i+1] + x[i]) * inv2 % MOD;
    
    std::map<int, ll> pmp;
    for(int i = q-1; i >= 0; i--) {
        if(pmp.count(x[i]-1)) pmp[x[i]-1] = (pmp[x[i]-1] + dp[i+1])%MOD;
        else pmp[x[i]-1] = dp[i+1]%MOD;
    }

    for(int i = 0; i < n; i++) p[i] = 0;
    p[0] = dp[0];
    for(int i = 0; i < n; i++)
        if(pmp.count(i)) p[i] = (p[i]+pmp[i]*inv2)%MOD;
    for(int i = 0; i < n; i++) printf("%lld\n", p[i]%MOD);
    return 0;
}