#include <stdio.h>
#include <algorithm>

constexpr int maxN = 2e5+1;

int main() {

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);

    int a[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);

    int b[maxN];
    for(int i = 0; i < m; i++)
        scanf("%d", b+i);

    std::sort(a, a+n);
    std::sort(b, b+m);

    int count = 0;
    for(int i = 0, j = 0; i < n && j < m;) {
        if(a[i]-k <= b[j] && b[j] <= a[i]+k) { i++; j++; count++; }
        else if(a[i] > b[j]) j++;
        else i++;
    }

    printf("%d\n", count);

    return 0;
}