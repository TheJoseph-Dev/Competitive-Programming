#include <stdio.h>
#include <algorithm>
int main() {
    int t;
    scanf("%d", &t);

    int y, x;
    while(t--) {
        scanf("%d%d", &y, &x);
        int m = std::max(x,y);
        //m^2 - m + 1 
        long long s = (long long)m*m - m + 1;
        if(m == x) s += (m&1) ? m-y : y-m;
        else s += (m&1) ? x-m : m-x;
        printf("%lld\n", s);
    }

    return 0;
}