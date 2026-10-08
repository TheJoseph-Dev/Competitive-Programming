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

int main() {
    std::ios::sync_with_stdio(0);

    std::string s;
    std::cin >> s;

    int n = s.size();
    Hashing hs(s);

    std::vector<int> periods;

    for (int len = 1; len <= n; ++len) {
        if (len == n) {
            periods.push_back(len);
            continue;
        }

        // s[len..n-1] == s[0..n-len-1]
        if (hs.get_hash(len, n - 1) == hs.get_hash(0, n - len - 1)) 
            periods.push_back(len);
    }

    for (int p : periods)
        std::cout << p << ' ';
}
