#include <stdio.h>
#include <algorithm>

int main() {
    int n, p = 0, c;
    scanf("%d", &n);
    for(int i = 0; i < n+1; i++) {
        scanf("%d", &c);
        p |= (1<<(n-i))*c;
    }
    
    int cnt = 0;
    while(p != 1) {
        cnt++;
        if(p&1) p = ((p<<1)^p)^1;
        else p >>= 1;
    }
    printf("%d\n", cnt);
    return 0;
}