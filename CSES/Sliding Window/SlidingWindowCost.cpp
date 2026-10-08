#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T> using pbset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using pbmst = tree<std::pair<T,int>, null_type, std::less<std::pair<T,int>>,rb_tree_tag, tree_order_statistics_node_update>;
pbmst<int> st;

using ll = long long;
constexpr int maxN = 2e5+5;

class FenwickTree {
    ll* tree;
    int size;
 
public:
    FenwickTree(int n) : size(n) {
        tree = new ll[n + 1]();
    }

    void Update(int idx, ll val) {
        while (idx <= size) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }
 
private:

    ll Query(int idx) {
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx; 
        }
        return sum;
    }
 
 public:
    ll RangeQuery(int a, int b) {
        return Query(b) - Query(a - 1);
    }
};

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    std::vector<int> a(n);
    std::map<int, int> css;
    for(int i = 0; i < n; i++) { scanf("%d", &a[i]); css[a[i]]; }
    int id = 1;
    for(auto& k : css) k.second = id++;
    FenwickTree fwt(n+1);
    for(int i = 0; i < k; i++) {
        st.insert({a[i], i});
        fwt.Update(css[a[i]], a[i]);
    }

    for(int i = k; i <= n; i++) {
        ll m = st.find_by_order((k-1)>>1)->first;
        int cl = st.order_of_key({m, 0});
        int cr = k-st.order_of_key({m+1, 0});
        printf("%lld ", cl*m - fwt.RangeQuery(1, css[m]-1) + fwt.RangeQuery(css[m]+1, id) - cr*m); // (x-a[i]) + (x-a[i+1]) ... + (a[j]-x) => \sum(i-k, midx) + midx*x + \sum(midx+1, k) - (k-midx)*x
        if(i == n) break;
        st.erase({a[i-k], i-k});
        fwt.Update(css[a[i-k]], -a[i-k]);
        st.insert({a[i], i});
        fwt.Update(css[a[i]], a[i]);
    }
    return 0;
}