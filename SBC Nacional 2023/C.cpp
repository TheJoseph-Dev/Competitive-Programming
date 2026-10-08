#include <stdio.h>
#include <vector>
#include <chrono>
#include <random>
#include <map>
using ll = long long;
constexpr int maxN = 4e5+5;

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const ll M = 1000001927;
ll H1[maxN], H2[maxN];
class Hashing {
private:
    std::vector<ll> pref, pref2;

public:
    // O(n)
    Hashing(int s[maxN], int a) {
        pref.resize(a + 1);
        pref2.resize(a + 1);

        for (int i = 0; i < a; i++) {
            pref[i + 1]  = pref[i]  + H1[s[i]];
            pref2[i + 1] = pref2[i] + H2[s[i]];
        }
    }

    // O(1)
    std::pair<ll, ll> get_hash(int l, int r) const {
        return { pref[r + 1] - pref[l], pref2[r + 1] - pref2[l] };
    }
};

int n, k;
int a[maxN], t[maxN];
int main() {
    scanf("%d%d", &n, &k);

    for(int i = 0; i <= k; i++) {
        H1[i] = rng() % M;
        H2[i] = rng() % M;
    }

    for(int i = 1; i <= k; i++) t[i-1] = i;
    for(int i = 0; i < n; i++) scanf("%d", a+i);

    Hashing hs = Hashing(a, n);
    Hashing ts = Hashing(t, k);

    auto [s1, s2] = ts.get_hash(0, k-1);

    std::map<std::pair<ll, ll>, int> mp;
    mp[{0, 0}] = -1;
    int len = 0;
    for(int i = 0; i < n; i++) {
        auto [p1, p2] = hs.get_hash(0, i);
        auto r = std::make_pair(p1 % s1, p2 % s2);
        if(!mp.count(r)) mp[r] = i;
        else len = std::max(len, i - mp[r]);
    }
    printf("%d\n", len);
}