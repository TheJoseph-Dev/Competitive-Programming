#include <stdio.h>
#include <algorithm>
using ll = long long;
int main() {
	ll n;
	scanf("%lld", &n);
	
    /*
        The code below takes advantage  of the pattern that binary numbers
        show where the bit b has a period of 2^b

		I encourage my future self to retry harder this exercise with a more original way to solve it
		using dp or something else
    */
	ll s = 0;
	for(int b = 0; (1LL<<b) <= n; b++)
		s += ((n+1)/(1LL<<(b+1)))*(1LL<<b) + std::max(0LL, ((n+1)%(1LL<<(b+1))) - (1LL<<b));

	printf("%lld\n", s);
    return 0;
}