#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

using ll = long long;
constexpr int maxN = 2e5+1, MOD = 1e9+7;
int n;
int arr[maxN];

class FenwickTree {
    ll* tree;
    int size;
 
public:
    FenwickTree(int n) : size(n) {
        tree = new ll[n + 1]();  // Indexed from 1 to n
    }

    void Update(int idx, ll val) {
        while (idx <= size) {
            tree[idx] += val;
            idx += idx & -idx;  // Move to the next index
        }
    }
 
private:

    ll Query(int idx) {
        ll sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;  // Move to the parent index
        }
        return sum;
    }
 
 public:
    ll RangeQuery(int a, int b) {
        return Query(b) - Query(a - 1);
    }
};

/*
    dp[i] = dp[i]+1 + dp[j], for j < i and a[i] > a[j] => How many subsequences end in position i
*/

ll dp[maxN];
int main() {
    scanf("%d", &n);

    std::map<int, int> css;
    for(int i = 0; i < n; i++) {
        scanf("%d", arr+i);
        css[arr[i]];
    }
    int id = 1;
    for(auto& k : css) k.second = ++id;
    for(int i = 0; i < n; i++) arr[i] = css[arr[i]];

    /*
    for(int i = 0; i < n; i++) {
        dp[i] = 1;
        for(int j = i-1; j >= 0; j--)
        if(arr[i] > arr[j]) 
        dp[i] = (dp[i] + dp[j])%MOD;
    }
    */

    FenwickTree fwt = FenwickTree(n+4);
    for(int i = 0; i < n; i++) {
        ll s = fwt.RangeQuery(1, arr[i]-1);
        dp[i] = (dp[i]+1 + s)%MOD;
        fwt.Update(arr[i], dp[i]);
    }

    ll cnt = 0;
    for(int i = 0; i < n; i++) cnt = (cnt+dp[i])%MOD;
    printf("%lld\n", cnt);

    return 0;
}