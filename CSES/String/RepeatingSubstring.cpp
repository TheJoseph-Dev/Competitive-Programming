#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

typedef long long ll;
class Hashing {
private:
    const ll P = 31;
	const ll M1 = 1e9 + 7;
	const ll M2 = 1e9 + 9;
    std::vector<long long> base_pow, base_pow2, pref, pref2;

public:
    
    // O(n)
    Hashing(const std::string &s) {
        int a = s.size();
        base_pow.resize(a);
        base_pow2.resize(a);
        pref.resize(a + 1);
        pref2.resize(a + 1);

        base_pow[0] = 1;
        base_pow2[0] = 1;
        for (int i = 1; i < a; i++) {
            base_pow[i] = base_pow[i - 1] * P % M1;
            base_pow2[i] = base_pow2[i - 1] * P % M2;
        }

        pref[0] = pref2[0] = s[0];
        for (int i = 1; i < a; i++) {
            pref[i] = (pref[i - 1] * P + s[i]) % M1;
            pref2[i] = (pref2[i - 1] * P + s[i]) % M2;
        }
    }
    
    // O(1)
    long long get_hash(int l, int r) const {
        if (l == 0) return (pref[r] << 30) ^ (pref2[r]);
        long long ret1 = ((pref[r] - (pref[l - 1] * base_pow[r - l + 1]) % M1 + M1) % M1);
        long long ret2 = ((pref2[r] - (pref2[l - 1] * base_pow2[r - l + 1]) % M2 + M2) % M2);
        return (ret1 << 30) ^ (ret2);
    }
};

bool seen(std::string& s, int len, const Hashing& hs) {
    std::unordered_set<ll> hSet;
    for(int i = 0; i + len < s.size(); i++) {
        ll hash = hs.get_hash(i, i+len);
        if(hSet.count(hash)) return true;
        hSet.insert(hash);
    }
    return false;
}

int main() {

    std::ios::sync_with_stdio(0);

    std::string s;
    std::cin >> s;

    Hashing hs = Hashing(s);

    int l = 1, r = s.size()-1;
    while(l < r) {
        int mid = (l+r) >> 1;
        if(seen(s, mid, hs)) l = mid+1;
        else r = mid;
    }
    
    std::unordered_set<ll> hSet;
    for(int i = 0; i+l <= s.size(); i++) {
        ll hash = hs.get_hash(i, i+l-1);
        if(hSet.count(hash)) { puts(s.substr(i, l).c_str()); break; }
        hSet.insert(hash);
    }

    if(l == 1) puts("-1");

    return 0;
}