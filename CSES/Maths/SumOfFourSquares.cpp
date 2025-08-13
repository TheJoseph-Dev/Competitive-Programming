#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

#define us unsigned short

long long sq(int x) {
    return (long long)x * x;
}

struct P {
    us a, b;
};

int main() {

    int q;
    scanf("%d", &q);

    gp_hash_table<int, P> sMap = gp_hash_table<int, P>();
    constexpr long long maxV = 1e7+1;
    for (int i = 0; sq(i) <= maxV; i++)
        for (int j = i; sq(i) + sq(j) <= maxV; j++) {
            int key = sq(i) + sq(j);
            sMap[key] = { (us)i, (us)j };
        }

    long long n;
next:
    while (q--) {
        scanf("%lld", &n);

        for (int i = 0; sq(i) <= n; i++) {
            for(int j = i; sq(i) + sq(j) <= n; j++) {
                long long key = n - sq(i) - sq(j);
                if(sMap.find(key) == sMap.end()) continue;
                auto t = sMap[key];
                printf("%d %d %d %d\n", i, j, t.a, t.b);
                goto next;
            }
        }
    }

    return 0;
}