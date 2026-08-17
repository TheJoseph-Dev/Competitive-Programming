#include <stdio.h>
constexpr int maxLOG = 20;
constexpr int maxN = 1e6+4;
constexpr int maxMsk = (1<<maxLOG)-1;
long long dpsbst[maxMsk], dpspst[maxMsk];
int cnt[maxN];
int x[maxN/4];
int main() {

    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d", x+i);
        cnt[x[i]]++;
        dpsbst[x[i]] = dpspst[x[i]] = cnt[x[i]];
    }

    /*
        b = 0
        dp[111] = dp[111] + dp[110] => {111, 110}
        dp[101] = dp[101] + dp[100]
        dp[011] = dp[011] + dp[010]
        dp[001] = dp[001] + dp[000]

        b = 1
        dp[111] = (dp[111] + dp[110]) + dp[101] => {111, 110, 101, 100}
        dp[101] = (dp[101] + dp[100])
        dp[011] = (dp[011] + dp[010]) + dp[001]
        dp[001] = (dp[001] + dp[000])
    */

    // At bit k, the dp[k][msk] considers all submasks that might differ from [0...k] and equal from [k+1...n]
    // At each bit k, for msk, msk^(1<<k) considered all masks that differed in previous bits from it.
    // Because msk^(1<<k) first differs from msk at bit k, the masks that msk^(1<<k) considered must also be submasks of msk
    // Moreover, those submasks must have not been added to msk (unique), since they also differ from msk at bit k.
    // So every mask ends up accumulating the results from the submasks exactly once (the first bit they differ)
    /*
        Every submask sub ⊆ msk has a unique highest bit where
            msk : 1
            sub : 0

        Suppose that highest differing bit is k.

        Then:

        - Before iteration k, bit k is still fixed, so sub cannot have been included.
        - During iteration k, sub belongs to dp[msk^(1<<k)], because that state already contains all possibilities for lower bits.
        - After iteration k, it is transferred exactly once into dp[msk].

        This gives a very clean proof:
            Each submask is assigned to exactly one iteration: the iteration corresponding to its highest differing bit.
    */

    for(int b = 0; b < maxLOG; b++)
        for(int msk = 0; msk <= maxMsk; msk++)
            if(msk&(1<<b))
                dpsbst[msk] += dpsbst[msk^(1<<b)];

    /*
        b = 0
        dp[111] = dp[111]
        dp[110] = dp[110] + dp[111]
        dp[100] = dp[100] + dp[101]
        dp[010] = dp[011] + dp[010] => 3
    */
    
    for(int b = 0; b < maxLOG; b++)
        for(int msk = maxMsk; msk >= 0; msk--)
            if((msk&(1<<b)) == 0)
                dpspst[msk] += dpspst[msk^(1<<b)];

    /*
        dp[111] = {111,110,101,011,001,010,100, ...}
        dp[100] = {1100, 100, ...}
        dp[110] = {110, 101, 100, 111, 010, 011, ...}
        ---
        dp[001] = {001,011,101,111, ...}


        dp[001] => dp[110] = {110,100,010,1110}
    */

    for(int i = 0; i < n; i++)
        printf("%lld %lld %lld\n", dpsbst[x[i]], dpspst[x[i]], n-dpsbst[(~x[i])&maxMsk] );
    return 0;
}