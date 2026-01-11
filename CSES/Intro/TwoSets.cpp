#include <stdio.h>
constexpr int maxN = 1e6+2;
int main() {

    int n, c = 0;
    long long s = 0;
    scanf("%d", &n);

    long long t = (long long)n*(n+1)/2;

    if(t&1) { puts("NO"); return 0; }
    t /= 2;
    bool p[maxN] = {false};
    for(int i = n; i >= 1; i--) {
        if(t-s < n && !p[t-s]) break;
        p[i] = true;
        s += i;
        c++;
    }

    p[t-s] = true;
    c += t-s != 0;

    puts("YES");
    printf("%d\n", c);
    for(int i = 1; i <= n; i++) if(p[i]) printf("%d ", i);
    putchar('\n');
    printf("%d\n", n-c);
    for(int i = 1; i <= n; i++) if(!p[i]) printf("%d ", i);

    return 0;
}