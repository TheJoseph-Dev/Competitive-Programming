#include <stdio.h>
// 2x + y = a
// x + 2y = b
// -3x = b-2a
// x = (2a-b)/3
// y = a - 2x
int main() {
    int t;
    scanf("%d", &t);
    int a,b;
    while(t--) {
        scanf("%d%d", &a, &b);
        int x = (2*a-b)/3;
        int y = (a-2*x);
        puts((x < 0 || y < 0 || 2*x + y != a || x + 2*y != b) ? "NO" : "YES");
    }
    return 0;
}