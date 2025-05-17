#include <stdio.h>
#include <algorithm>
#include <vector>

constexpr long long LLINF = 1e17; 
constexpr int maxN = 4e5 + 1;
long long a[maxN], h[maxN];
int main() {

    int n;
    long long k;
    scanf("%d%lld", &n, &k);

    for (int i = 0; i < n; i++) scanf("%lld", a+i);
    for (int i = 0; i < n; i++) a[i+n] = a[i];
    
    // s > (a[j]-a[i])/k
    
    
    // j-i > (a[j]-a[i])/k (j > i)
    
    // a[i] + s*k > a[j]
    // a[i] > a[j] - (j-i)*k

    // a[i] - ik > a[j] - jk
    // h[i] = a[i]-ik

    for(int i = 0; i < 2*n; i++) h[i] = a[i] - i*k;
    
    std::vector<long long> stk, pos, b(2*n);
    stk.push_back(-LLINF);
    pos.push_back(-1);
    
    for(int i = 2*n - 1; i >= 0; i--) {
        while(!stk.empty() && stk.back() >= h[i]) { stk.pop_back(); pos.pop_back(); }
        b[i] = pos.back();
        pos.push_back(i);
        stk.push_back(h[i]);
    }

    for (int i = 0; i < n; i++) printf("%d ", (b[i]%n) + 1);
}
