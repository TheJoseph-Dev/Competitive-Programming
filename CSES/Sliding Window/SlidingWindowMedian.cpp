#include <stdio.h>
#include <vector>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
template<class T> using pbset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using pbmst = tree<std::pair<T,int>, null_type, std::less<std::pair<T,int>>,rb_tree_tag, tree_order_statistics_node_update>;
pbmst<int> st;
 
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    std::vector<int> a(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < k; i++) st.insert({a[i], i});
    for(int i = k; i <= n; i++) {
        printf("%d ", st.find_by_order((k-1)>>1)->first);
        if(i == n) break;
        st.erase({a[i-k], i-k});
        st.insert({a[i], i});
    }
    return 0;
}