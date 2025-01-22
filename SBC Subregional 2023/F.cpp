#include <stdio.h>

int main() {

    int d, c, r;
    scanf("%d%d%d", &d, &c, &r);

    int tire[100001];
    for(int i = 0; i < c; i++) scanf("%d", tire+i);
    for(int i = 0; i < r; i++) {
        int x;
        scanf("%d", &x);
        d+=x;
    }

    int i;
    for(i = 0; i < c; i++)  {
        if(d >= tire[i])
            d -= tire[i];
        else break;
    }

    printf("%d\n", i+r);

    return 0;
}