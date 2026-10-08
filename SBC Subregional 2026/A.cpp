#include <stdio.h>
using ll = long long;
constexpr int maxN = 1e5+4;
ll pc[maxN], pv[maxN];
int main() {
    int n;
    scanf("%d", &n);
    ll c, v;
    for(int i = 0; i < n; i++) {
        scanf("%lld%lld", &c, &v);
        pc[i+1] = pc[i] + c;
        pv[i+1] = pv[i] + v;
    }
    int q;
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &n);
        double in = (double)(pc[n]-pv[n])/(pc[n]+pv[n]);
        if(in > 0) puts("COMPRA");
        else if(in < 0) puts("VENDA");
        else puts("NEUTRO");
    }
}