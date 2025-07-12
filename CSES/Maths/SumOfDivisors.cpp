#include <stdio.h>

#define ll long long
constexpr int MOD = 1e9 + 7;

int sigma(ll n) {
    int sum = 0;
    for(ll i = 1; i*i <= n; i++)
        if(n%i == 0) sum = (sum + (i + ((n/i)%MOD))%MOD)%MOD; 
    return sum;
}

int main() {

    ll n;
    scanf("%lld", &n);

    printf("%d\n", sigma(n));

    return 0;
}