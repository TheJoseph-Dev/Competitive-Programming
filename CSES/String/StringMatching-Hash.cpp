#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>

using ll = long long;
constexpr ll M1 = 1e9 + 7;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count()); // Random number generator
static ll P = std::uniform_int_distribution<int>(356, M1 - 1)(rng);

class Hashing {
private:
    //const ll P = 31;
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
    std::string str, pattern;
 
    std::cin >> str;
    std::cin >> pattern;
    
    Hashing hs = Hashing(str), hp = Hashing(pattern);
    
    int count = 0;
    for(int i = pattern.size(); i <= str.size(); i++)
        count += (hs.get_hash(i-pattern.size(), i-1) == hp.get_hash(0, pattern.size()-1));

    std::cout << count << std::endl;
 
    return 0;
}