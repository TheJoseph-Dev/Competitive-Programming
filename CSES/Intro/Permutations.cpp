#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    if(n == 1) puts("1");
    else if(n <= 3) puts("NO SOLUTION");
    else {
        for(int i = 2; i <= n; i += 2) printf("%d ", i);
        for(int i = 1; i <= n; i += 2) printf("%d ", i);
    }
    return 0;
}