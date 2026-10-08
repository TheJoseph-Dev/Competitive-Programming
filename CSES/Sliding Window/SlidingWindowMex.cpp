 #include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

constexpr int maxN = 2e5+4;
int a[maxN];
int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    std::map<int, int> nc;
    std::set<int> msnst;
    for(int i = 0; i <= k; i++) msnst.insert(i);
    for(int i = 0; i < k; i++) {
        nc[a[i]]++;
        if(msnst.find(a[i]) != msnst.end()) msnst.erase(a[i]);
    }
    for(int i = k; i <= n; i++) {
        printf("%d ", *msnst.begin());
        if(!--nc[a[i-k]]) msnst.insert(a[i-k]);
        nc[a[i]]++;
        if(msnst.find(a[i]) != msnst.end()) msnst.erase(a[i]);
    }
    return 0;
}