#include <stdio.h>
#include <algorithm>
#include <set>
 
constexpr int maxN = 2e5+1;
 
int main() {
 
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
 
    int a[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
 
    int b;
    std::multiset<int> apartments;
    for(int i = 0; i < m; i++) {
        scanf("%d", &b);
        apartments.insert(b);
    }
 
    std::sort(a, a+n);
 
    for(int i = 0; i < n; i++) {
        auto it = apartments.lower_bound(a[i]-k);
        if(it == apartments.end()) continue;
        if(!(a[i]-k <= *it && *it <= a[i]+k)) continue;
        apartments.erase(it);
    }
 
    printf("%d\n", m-apartments.size());
 
    return 0;
}