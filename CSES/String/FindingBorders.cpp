#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
std::vector<int> bases = {37,61,79,83,97,53,61,
                         107,127,137,163,191 ,
                         199,211,229,239,263 ,
                         271,281,293 };      
std::vector<int> mods = {1000000007, 1000000009, 1000000433, 1000001329, 1000001927,
                    1000003051, 1000003253, 1000003397, 1000003579, 1000003751,
                    1000003793, 1000002043, 1000003967, 1000003987, 1000004123,
                    1000004843, 1000006129, 1000006961, 1000012253, 1000015271};
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
    long long get_hash(int l, int r) {
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
    Hashing hash = Hashing(s);
    for(int len = 0; len < s.size()-1; ++len)
        if(hash.get_hash(0, len) == hash.get_hash(s.size()-1-len, s.size()-1)) 
            printf("%d ", len+1);

    return 0;
}