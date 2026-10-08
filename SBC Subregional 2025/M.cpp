#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
using ll = long long;
struct VeniceSet {
    std::multiset<ll> st;
    std::map<ll, std::queue<ll>> f;
    ll p = 0;

    void add(ll x) { st.insert(x + p); f[x].push(x+p); }

    // Remove x in FIFO maner
    void remove(ll x) {
        st.erase(st.find(f[x].front()));
        f[x].pop();
    }

    // Decrement every thing by x
    void updateAll(ll x) { p += x; }

    ll getMin() { return *st.begin() - p; }
    size_t size() { return st.size(); }
    void print() {
        printf("(%d) { ", p);
        for(auto it : st) printf("%lld ", it);
        printf("}\n");
    }
};

constexpr int maxN = 1e5+2;
constexpr ll INFLL = 1e18;

class SparseTable {

    int n;
    std::vector<std::vector<int>> minTable;

private:
    int flog(int x) { // Calcula a parte inteira do log2 de x em O(1) ( para int )
    	return 31 - __builtin_clz(x);
    }
public:
    SparseTable(int arr[], int n): n(n) {
        int k = flog(n) + 1;
        this->minTable = std::vector<std::vector<int>>(k, std::vector<int>(n));

        for (int i = 0; i < n; i++)
            minTable[0][i] = arr[i];

        for (int j = 1; (1 << j) <= n; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                minTable[j][i] = std::min(minTable[j - 1][i], minTable[j - 1][i + (1 << (j - 1))]);
    }

    ll RangeMin(int L, int R) {
        if(R < L) return INFLL;
        int j = flog(R - L + 1);
        return std::min(minTable[j][L], minTable[j][R - (1 << j) + 1]);
    }
};

int main() {

    int n, k, a[maxN];
    scanf("%d%d", &n, &k);

    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
        
    SparseTable sp(a, n);
    VeniceSet vs;
    ll mn = sp.RangeMin(0, n-1);
    for(int i = 0; i < k; i++) {
        vs.updateAll(1);
        vs.add(a[i]+k);
        mn = std::max(mn, std::min<ll>({sp.RangeMin(i+1, n-1), vs.getMin()}));
    }

    for(int i = k; i < n; i++) {
        vs.remove(a[i-k]+k);
        vs.updateAll(1);
        vs.add(a[i]+k);
        mn = std::max(mn, std::min<ll>({sp.RangeMin(0, i-k), sp.RangeMin(i+1, n-1), vs.getMin()}));
    }

    printf("%lld\n", mn);
    return 0;
}