#include <stdio.h>
int main() {
    bool m[4] = {0};
    int n;
    for(int i = 0; i < 10; i++) {
        scanf("%d", &n);
        m[n-1] = true;
    }

    int s = m[0]+m[1]+m[2]+m[3];
    printf("%d\n", 4-s);
    return 0;
}