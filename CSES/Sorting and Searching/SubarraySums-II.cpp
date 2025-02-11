#include <stdio.h>
#include <map>

typedef long long ll;

int main() {

    int n, x;
    scanf("%d%d", &n, &x);

    std::map<ll, int> map;
    map[0] = 1;

    ll prfx, a, count = 0;
    scanf("%lld", &prfx);
    count += map[prfx-x];
    map[prfx]++;

    while(--n) {
        scanf("%lld", &a);
        prfx += a;
        count += map[prfx-x];
        map[prfx]++;
    }

    printf("%lld\n", count);

    return 0;
}