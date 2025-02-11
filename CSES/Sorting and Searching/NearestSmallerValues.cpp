#include <stdio.h>

constexpr int maxN = 2e5+1;

struct P {
    int v, i;
};

int main() {

    int n;
    scanf("%d", &n);

    P sStk[maxN];
    int x, stkptr = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        while(stkptr && sStk[stkptr-1].v >= x) stkptr--;
        if(stkptr == 0) printf("0 ");
        else printf("%d ", sStk[stkptr-1].i+1);
        sStk[stkptr++] = {x, i};
    }

}