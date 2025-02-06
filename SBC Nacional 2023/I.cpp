
// cabcabcabcab
// O(n): faz 26 passagens lineares (1 para cada letra)
// 26 * 10^5
// Ex: A letra Li terá um contador de quantas foi vista, esse contador será usado para multiplicar o valor da inversão

// n=1: 2, 0, 0 = 2
// n=2: 4, 0, 1, 2, 0, 0 = 7
// n=3: 6, 0, 2, 4, 0, 1, 2, 0, 0 = 15
// n=4: 8, 0, 3, 6, 0, 2, 4, 0, 1, 2, 0, 0 = 26

// I(k) = I(k-1) + vi + r*(k-2) (k >= 2)
// I(1) = 2
// r = 3, vi = 5

// I(2) = I(1) + 5 + 3*0 = 7
// I(3) = I(2) + 5 + 3*1 = 15 => (I(1)+5) + 5+3*1
// I(4) = I(3) + 5 + 3*2 = 26 => ((I(1)+5) + 5+3*1) + 5+3*2
// I(k) = I(1) + (k-1)vi + r*(k-2)*(k-1)/2

#include <iostream>
#include <string>

#define ll long long
#define MOD 1000000007LL

ll modInverse(ll a, ll m) {
    ll m0 = m, y = 0, x = 1;
    if (m == 1) return 0; 
    while (a > 1) {
        ll q = a / m;
        ll t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) x += m0;
    return x;
}

ll I(ll n, ll s, ll vi, ll r) {
    ll t1 = (((n - 1) % MOD) * (vi % MOD)) % MOD;
    ll t2 = ((r % MOD) * ((n - 2) % MOD)) % MOD;
    t2 = (t2 * ((n - 1) % MOD)) % MOD;
    t2 = (t2 * modInverse(2, MOD)) % MOD;  // Use modular inverse for division by 2
    return (s + t1 + t2) % MOD;
}


int main() {

    std::ios::sync_with_stdio(0);

    std::string s, sa;
    ll n;

    std::cin >> s >> n;
    sa = s;

    ll nI[3] = {0};
    for(int i = 0; i < std::min(3LL, n); i++) { // 3
        int chFreq[27] = {0};
        for(char c = 'a'; c <= 'z'; c++) { // 26
            for(char cch : sa) // 10^5
                if(c == cch) chFreq[c-'a']++;
                else if(cch < c) nI[i] += chFreq[c-'a'];
        }

        if(i != 2) sa += s;
    }

    if(n > 3) printf("%lli\n", I(n, nI[0], nI[1]-nI[0], nI[2]-2*nI[1]+nI[0]));
    else printf("%lli\n", nI[n-1]);

    return 0;
}