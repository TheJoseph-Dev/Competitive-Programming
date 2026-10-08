#include <stdio.h>
using ll = long long;
constexpr int maxN = 1e5+4;
int f[maxN*11];
ll g[maxN*11];
int main() {

    int n, k;
    scanf("%d%d", &n, &k);

    char s[22];
    auto s2n = [k](char s[]) -> int {
        int x = 0;
        for(int i = 0; i < k; i++) if(s[i]-'0') x |= (1<<(k-i-1));
        return x;
    };
    for(int i = 0; i < n; i++) {
        scanf("%s", s);
        int x = s2n(s);  
        f[x]++;
        //printf("x: %d\n", x);
    }

    for(int msk = 0; msk < (1<<k); msk++) g[msk] = f[msk];
    for(int b = 0; b < k; b++)
        for(int msk = 0; msk < (1<<k); msk++)
            if(msk&(1<<b))
                g[msk] += g[msk^(1<<b)];
    
    for(int msk = 0; msk < (1<<k); msk++) g[msk] = (g[msk]*(g[msk]-1)*(g[msk]-2))/6;

    for(int b = 0; b < k; b++)
        for(int msk = 0; msk < (1<<k); msk++)
            if(msk&(1<<b))
                g[msk] -= g[msk^(1<<b)];

    //for(int msk = 0; msk < (1<<k); msk++) printf("g[%d]: %d\n", msk, g[msk]);
    int q;
    scanf("%d", &q);

    while(q--) {
        scanf("%s", s);
        int x = s2n(s);
        printf("%lld\n", g[x]);
    }

    return 0;
}