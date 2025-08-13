#include <stdio.h>
#include <vector>
using ll = long long;

ll mul(ll a, ll b, ll m) {
	ll ret = a*b - ll((long double)1/m*a*b+0.5)*m;
	return ret < 0 ? ret+m : ret;
}

ll pow(ll x, ll y, ll m) {
	if (!y) return 1;
	ll ans = pow(mul(x, x, m), y/2, m);
	return y%2 ? mul(x, ans, m) : ans;
}

// Miler-Rabin 
bool prime(ll n) {
    if(n == 2) return true;
	if (n < 2 || !(n&1)) return 0;
	if (n <= 3) return 1;

	ll r = __builtin_ctzll(n - 1), d = n >> r;
	for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
		ll x = pow(a, d, n);
		if (x == 1 || x == n - 1 || a % n == 0) continue;
		
		for (int j = 0; j < r - 1; j++) {
			x = mul(x, x, n);
			if (x == n - 1) break;
		}
		if (x != n - 1) return false;
	}
	return true;
}

ll next(ll n) {
    while(!prime(n+1)) n++;
    return n+1;
}

int main() {
    int t;
    scanf("%d", &t);

    ll n;
    while(t--) {
        scanf("%lld", &n);
        printf("%lld\n", next(n));
    }

    return 0;
}