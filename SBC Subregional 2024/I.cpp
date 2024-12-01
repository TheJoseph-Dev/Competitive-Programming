#include <stdio.h>
#include <vector>
#include <bitset>
#include <unordered_set>

#define MOD 1000000007LL

/*
    Get Prime Factors from each Q
    Precalculate vectors with plates of each prime factors
    Because there are little prime factors to the given range (10^6)
    We can put the plates in a set and use its size
*/

#define ll long long

ll modpow2(int p) { 
    int r = 1;     // Initialize result 
    int b = 2;
    while (p > 0) { 
        // If y is odd, multiply x with result 
        if (p & 1) 
            r = (r*b) % MOD; 
 
        // y must be even now 
        p >>= 1; 
        b = (b*b) % MOD; 
    } 
    return r; 
}

void primeFactors(int n, std::unordered_set<int>& primes) {

    // Print the number of 2s that divide n 
    while (!(n&1)) { 
        primes.insert(2);
        n >>= 1;
    }
 
    // n must be odd at this point. So we can skip 
    // one element (Note i = i +2) 
    for (int i = 3; i*i <= n; i+=2) { 
        // While i divides n, print i and divide n 
        while (n % i == 0) { 
            primes.insert(i); 
            n/=i;
        }
    } 
 
    // This condition is to handle the case when n 
    // is a prime number greater than 2 
    if (n > 2) primes.insert(n);
}

int main() {

    int n, plates[100001];
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", plates+i);

    int q, people[100001];
    scanf("%d", &q);

    for(int i = 0; i < q; i++)
        scanf("%d", people+i);

    std::vector<int> primes = std::vector<int>();
    std::unordered_set<int> ingredients = std::unordered_set<int>();
    // Get ingredients in N sqrt(N);
    for(int i = 0; i < n; i++)
        primeFactors(plates[i], ingredients);
    
    // primes.size() is ~79000 at max 
    // 41538 primes with intersection
    for(int i : ingredients)
        primes.push_back(i);

    // Precalculate for each ingredient (prime) its plates
    // Worst Case: Many Prime Numbers => O(n^2)
    
    /*
    std::vector<std::bitset<100001>> fMap = std::vector<std::bitset<100001>>(primes.size());
    for(int i = 0; i < primes.size(); i++)
        for(int p = 0; p < n; p++)
            if(plates[p]%primes[i] == 0)
                fMap[i].flip(p);
    */

    std::vector<int> fMap[1000001];
    for(int i = 0; i < primes.size(); i++)
        for(int p = 0; p < n; p++)
            if(plates[p]%primes[i] == 0)
                fMap[primes[i]].push_back(plates[p]);

    // q sqrt(Xn);
    for(int x = 0; x < q; x++) {
        std::unordered_set<int> badIngs = std::unordered_set<int>(), badPlates = std::unordered_set<int>();
        primeFactors(people[x], badIngs);
        for(int i : badIngs) {
            for(int p : fMap[i]) badPlates.insert(p);
        }

        printf("%lli\n", modpow2(n-badPlates.size()));
    }

    return 0;
}