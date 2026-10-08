#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
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
	if (n == 2) return true;
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

ll rho(ll n) {
	if (n == 1 || prime(n)) return n;
	auto f = [n](ll x) {return mul(x, x, n) + 1;};

	ll x = 0, y = 0, t = 30, prd = 2, x0 = 1, q;
	while (t % 40 != 0 || std::__gcd(prd, n) == 1) {
		if (x==y) x = ++x0, y = f(x);
		q = mul(prd, abs(x-y), n);
		if (q != 0) prd = q;
		x = f(x), y = f(f(y)), t++;
	}
	return std::__gcd(prd, n);
}

std::vector<ll> fact(ll n) {
	if (n == 1) return {};
	if (prime(n)) return {n};
	ll d = rho(n);
	std::vector<ll> l = fact(d), r = fact(n / d);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}
int main() {
    std::ios::sync_with_stdio(0);
    std::string num;
    std::cin >> num;

    // |X-Y| e [X-X*10^-9, X+X*10^-9]
    // log X ~= log(2^a) + log(3^b)
    // log X ~= a * log2 + b * log3
    
    int k = std::min<int>(11, num.size());;
    auto xlog = [&]() {
        ll M = 0;
        for(int i = 0; i < k; i++) M = M*10 + (num[i]-'0');
        return M;//std::make_pair(M, log10(M) + (num.size()-k));
    };

    auto r = xlog();
    auto f = fact(r);
    std::map<ll, int> divs;
    for(int i = 0; i < f.size(); i++) divs[f[i]]++;
    if(num.size()-k) { divs[2]; divs[5]; }
    printf("%d\n", divs.size());
    for(auto [d,p] : divs)
        if(d != 2 && d != 5) printf("%lld %d\n", d, p);

    int p2 = divs[2] + num.size()-k, p5 = divs[5] + num.size()-k;
    if(p2) printf("2 %d\n", p2);
    if(p5) printf("5 %d\n", p5);

    return 0;
}