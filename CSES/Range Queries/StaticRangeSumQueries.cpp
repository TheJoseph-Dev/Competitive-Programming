#include <stdio.h>
#define ll long long

int main() {

    int n, q;
    scanf("%d%d", &n, &q);

    ll num, prfx[200001];
    for(int i = 0; i < n; i++) {
        scanf("%lli", &num);
        prfx[i] = (num + (i > 0 ? prfx[i-1] : 0));
    }

    int a, b;
    while(q--) {
        scanf("%d%d", &a, &b);
        printf("%lli\n", prfx[b-1]-(a >= 2 ? prfx[a-2] : 0));
    }

    return 0;
}