#include <stdio.h>
#include <algorithm>

int main() {

    int n,m;
    scanf("%d%d", &n, &m);

    int a,b;
    while(m--) {
        scanf("%d%d", &a, &b);
        printf("%d %d\n", std::min(a,b), std::max(a,b));    
    }
    
    return 0;
}