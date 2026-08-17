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
constexpr int maxN = 2e5+4, maxLOG = 20, INF = 1e9+2, MOD = 1e9+7;
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
};

class SuffixAutomaton {
    struct State {
        int len, link;
        int next[26];

        State() : len(0), link(-1) {
            memset(next, -1, sizeof(next));
        }
    };

    std::vector<State> st;
    int last;

    void extend(char ch) {
        int c = ch - 'a';

        int cur = st.size();
        st.emplace_back();
        st[cur].len = st[last].len + 1;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }

                st[q].link = st[cur].link = clone;
            }
        }

        last = cur;
    }

public:
    SuffixAutomaton(const std::string &s) {
        st.reserve(2 * s.size());
        st.emplace_back();
        last = 0;

        for (char c : s)
            extend(c);
    }

    bool contains(const std::string &t) const {
        int v = 0;
        for (char ch : t) {
            int c = ch - 'a';
            if (st[v].next[c] == -1)
                return false;
            v = st[v].next[c];
        }

        return true;
    }
};

int n, q, k, t;
std::string s,p;
int main() {
    f_io();
    std::cin >> s >> t;
    SuffixAutomaton sa(s);
    next:
    while(t--) {
        std::cin >> p;
        puts(sa.contains(p) ? "YES" : "NO");
    }
    return 0;
}