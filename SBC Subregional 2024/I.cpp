#include <stdio.h>

// Mobius Function solution
// The Mobius function is a multiplicative function that comes in handy when dealing with inclusion-exclusion
// technique and divisors-related problems | https://usaco.guide/plat/PIE?lang=cpp
// Leo's Solution: Pure Inclusion-Exclusion principle given the fact that 2^p is small enough for this problem
// (2*3*5*7*11*13*17*19 > 10^6 => worst case = 7 different primes)
// Video for Leo's solution: https://www.youtube.com/watch?v=8P0YgkBSl7w

#define ll long long
constexpr int maxN = 1e6+1, MOD = 1e9+7;

int divCount[maxN] = {0};
void countDivisors(int plates[maxN], int n) {
    for(int i = 0; i < n; i++)
        for(int d = 1; d*d <= plates[i]; d++)
            if(plates[i]%d == 0) { divCount[d]++; if(plates[i] != d*d) divCount[plates[i]/d]++; }
}

short mobius[maxN] = {0};
void genMobius() {
    mobius[1] = -1;
    for (int i = 1; i < maxN; i++) {
        if (mobius[i] == 0) continue;
        mobius[i] *= -1;
        for (int j = (i<<1); j < maxN; j += i)
            mobius[j] += mobius[i];
    }
}

int binpow(ll b, int e) {
    ll r = 1;
    while(e) {
        if(e&1) r = (r*b)%MOD;
        b = (b*b)%MOD;
        e >>= 1; 
    }

    return r%MOD;
}

int main() {

    genMobius();
    
    int n, plates[maxN];
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", plates+i);

    countDivisors(plates, n);

    int q;
    scanf("%d", &q);

    // Count how many plates there are which don't contain any of the person's prime factors
    // 1 2 3 4 5 6
    // count[i] = {0, 6, 3, 2, 1, 1, 1, 0}
    // count[2] + count[3] => 5 Overcount (6)
    // Therefore, we use the mobius function to apply the inclusion-exclusion principle
    // sum(count[d]*mobius(d)) => 4

    int person;
    while(q--) {
        scanf("%d", &person);
        
        int count = 0;
        for(int i = 1; i*i <= person; i++) {
            if(person%i != 0) continue;
            count += divCount[i]*mobius[i];
            if(i*i != person) count += divCount[person/i]*mobius[person/i];
        } 
        
        printf("%d\n", binpow(2, count));
    }

    return 0;
}