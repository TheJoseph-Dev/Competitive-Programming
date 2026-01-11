#include <stdio.h>
#include <algorithm>
constexpr int maxN = 2e5+2;
int main() {
    int n, a[maxN];
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
    
    long long s = 0;
    for(int i = 1; i < n; i++)
        if(a[i-1] > a[i]) {
            s += a[i-1]-a[i];
            a[i] = a[i-1];
        }

    printf("%lld\n",s);
    return 0;
}