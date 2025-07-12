#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstring>
 
constexpr int sieveN = 2e5+1, maxN = 1e5+1;
std::vector<int> primes;
 
// O(n log(log n))
void sieve() {
    bool prime[sieveN + 1];
    memset(prime, true, sizeof(prime));
 
    for (int p = 2; p * p <= sieveN; p++)
        if (prime[p])
            for (int i = p * p; i <= sieveN; i += p)
                prime[i] = false;
    
    for(int i = 2; i < sieveN; i++)
        if(prime[i]) primes.push_back(i);
}

 
int main() {
 
    int n;
    scanf("%d", &n);
    
    for(int i = 1; i <= n; i++) printf("%d ", i);
    putchar('\n');
 
    sieve();

    int ai = 1, ak = n, perm[maxN];
    do {
        int p = *std::upper_bound(primes.begin(), primes.end(), ak);
        ai = p-ak;
        for(int i = ai; i <= ak; i++) perm[i] = ak-i+ai;
        ak = ai-1;
    } while(ai != 1);

    for(int i = 1; i <= n; i++) printf("%d ", perm[i]);
    return 0;
}