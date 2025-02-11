#include <stdio.h>
#include <algorithm>

constexpr int maxN = 2e5+1;

int main() {
    int n, x;    
    scanf("%d%d", &n, &x);

    int w[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", w+i);

    std::sort(w, w+n);
    
    int g = 0;
    for(int i = 0, j = n-1; i <= j; j--, g++)
        i += (i != j && w[i] + w[j] <= x);

    printf("%d\n", g);

    return 0;
}