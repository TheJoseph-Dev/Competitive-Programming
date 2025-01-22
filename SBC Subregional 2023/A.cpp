#include <stdio.h>

int main() {

    int n, h;
    scanf("%d%d", &n, &h);

    int count = 0;
    while(n--) {
        int x;
        scanf("%d", &x);
        count += (x <= h);
    }
    printf("%d\n", count);

    return 0;
}