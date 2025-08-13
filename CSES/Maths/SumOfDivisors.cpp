#include <iostream>
#include <math.h>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <array>
#include <set>

using ll = long long;
constexpr int maxN = 1e3+2, maxLOG = 20, INF = 2e9+2, MOD = 1e9+7;
constexpr ll LLINF = 1e18;

int main() {
    /*
        1 <= n <= 10^12
        s(n) = sum_{i=1}^n sum_{d|i}^i d
        The time complexity of the sum above is O(n*sqrt(n)) (O(n*log n) with sieve)
        
        We gotta optimize this:
        How many times does d shows up?

        Let each d be the divisor of some number. So the sum becomes:
        sum_{d=1}^n d * m
        where m is the number of times each d shows up as a divisor of some number

        But how to calculate m?
        Let's do a small test:
        n = 6
        d = 1 => 6
        d = 2 => 3
        d = 3 => 2
        d = 4 => 1
        d = 5 => 1
        d = 6 => 1
        So we can check that d = 1 represents how many numbers we have until n, d = 2 represents
        how many even numbers we have until n. Therefore, it's not crazy to say that m = floor(n/d)

        Great, so the sum now is:
        s(n) = sum_{d=1}^n d * floor(n/d)
        That is O(n)
        Can we do it even better?

        We can see that if there wasn't floor(n/d) the sum would straight forwardly be O(1).
        So how many times does floor(n/d) changes?
        Well, it is not many. As we could check when n = 6, m = 1 repeats many times.
        It turns out that it only changes O(sqrt(n)) times, because there are only up to sqrt(n) divisors!.
        Now we can use that to compute sqrt(n) blocks in O(1)

        Blocks:
        [n, n/2[ => floor(n/d) = 1
        [n/2, n/3[ => floor(n/d) = 2
        ...

        Final time complexity: O(sqrt(n)) (or O(log n) with sieve)
    */

    ll n;
    scanf("%lld", &n);

    ll sum = 0;
    ll d = 1;
    while(d <= n) {
        ll m = n/d;
        ll j = n/m;
        sum = (sum + (((((j - d + 1LL) % MOD) * ((d + j) % MOD)) % MOD * (m % MOD)) % MOD * 500000004LL) % MOD) % MOD;
        d = j + 1;
    }

    printf("%lld\n", sum);

    return 0;
}