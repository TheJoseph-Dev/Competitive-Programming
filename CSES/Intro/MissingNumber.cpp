#include <stdio.h>
constexpr int maxN = 2e5+2;
int main() {
    int n, x;
    scanf("%d", &n);

    bool m[maxN] = {false};
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
        m[x] = true;
    }

    for(int i = 1; i <= n; i++)
        if(!m[i]) printf("%d\n", i);

    return 0;
}