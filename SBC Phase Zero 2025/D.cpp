#include <stdio.h>

constexpr int maxN = 1e5+1;
int main() {

    int n, a1 = 0, a2 = 0;
    char s[maxN];
    scanf("%d%s", &n, s);
    for(int i = 0; i < n; i++)
        a1 += (s[i] == '*');
    scanf("%s", s);
    for(int i = 0; i < n; i++)
        a2 += (s[i] == '*');
    printf("%.2lf\n", 1-((double)a2/a1));
    return 0;
}