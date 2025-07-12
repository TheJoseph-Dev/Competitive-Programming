#include <stdio.h>
#include <vector>
#include <set>
 
using ll = long long;
 
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};
 
// Line Container - For min: add(-a,-b) -query(x)
// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
struct ConvexHullTrick : std::multiset<Line, std::less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = 0x3f3f3f3f3f3fLL;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    ConvexHullTrick cht;
    int y1, y2;
    while(n--) {
        scanf("%d%d", &y1, &y2);
        ll a = (y2-y1)/m;
        cht.add(a, y1);
    }

    for(int x = 0; x <= m; x++)
        printf("%lld ", cht.query(x));

    return 0;
}