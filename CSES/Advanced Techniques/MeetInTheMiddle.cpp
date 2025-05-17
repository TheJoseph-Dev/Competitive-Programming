#include <stdio.h>
#include <vector>
#include <algorithm>
typedef long long ll;
constexpr int maxN = 21;

void getSums(ll arr[maxN], int n, std::vector<ll>& sums) {
    for(int mask = 0; mask < (1<<n); mask++) {
        ll sum = 0;
        for(int i = 0; i < n; i++)
            if(mask&(1<<i)) sum += arr[i];
        sums.push_back(sum);
    }
}

int main() {

    int n, sz = 0;
    ll x;
    scanf("%d%lld", &n, &x);

    ll left[maxN], right[maxN];
    for(;(sz<<1) < n; sz++)
        scanf("%lld", left+sz);

    for(int i = 0; (i<<1) < n-(n&1); i++)
        scanf("%lld", right+i);

    std::vector<ll> sums, aux;
    getSums(left, sz, sums);
    getSums(right, n-sz, aux);
    std::sort(sums.begin(), sums.end());
    std::sort(aux.begin(), aux.end());

    ll count = 0;
    for(ll s : sums) count += std::upper_bound(aux.begin(), aux.end(), x-s)-std::lower_bound(aux.begin(), aux.end(), x-s);
    
    printf("%lld\n", count);

    return 0;
}