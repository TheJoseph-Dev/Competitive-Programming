#include <stdio.h>
#include <vector>
#include <set>
using ll = long long;
constexpr int maxN = 20;
ll fact[maxN];
void genFact() {
    fact[0] = fact[1] = 1;
    for(int i = 2; i < 21; i++) fact[i] = (fact[i-1]*i);
}

int main() {
    genFact();
    int t;
    scanf("%d", &t);

    int type, n;
    ll k;
    while(t--) {
        scanf("%d", &type);

        if(type-1) {
            scanf("%d", &n);
            k = 1;
            int p;
            
            std::set<int> pset;
            for(int i = 1; i <= n; i++) pset.insert(i);
            
            for(int i = 0; i < n; i++) {
                scanf("%d", &p);
                int kth = 1;
                auto it = pset.begin();
                while(*it != p) { kth++; it = std::next(it); }

                k += (kth-1)*fact[n-i-1];
                pset.erase(p);
            }
            printf("%lld", k);
        }
        else {
            scanf("%d%lld", &n, &k);
            // _ x y z => 1 x y z => 3!
            // k/fact[i-1] => How many permutations of size must i-1 have passed?
            // if k/fact[n-1] = 0, then it must be 1
            // if (k-0)/fact[n-2] = 0, then it must be 2, because 1 has already been placed
            // m*fact[i-1] = k
            // m = (int)(k/fact[i-1])
            std::set<int> pset;
            for(int i = 1; i <= n; i++) pset.insert(i);
            std::vector<int> p;
            k--;
            for(int i = n-1; i >= 1; i--) {
                int m = (int)(k/fact[i]);
                auto it = pset.begin();
                int mth = m;
                while(mth--) it = std::next(it);
                p.push_back(*it);
                pset.erase(it);
                k -= m*fact[i];
            }
            p.push_back(*pset.begin());
            for(int i : p) printf("%d ", i);
        }
        putchar('\n');
    }

    return 0;
} 