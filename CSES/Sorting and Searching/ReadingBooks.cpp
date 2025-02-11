#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main() {

    int n;
    scanf("%d", &n);

    int time;
    long long sum = 0, max = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &time);
        sum += time;
        max = MAX(max, time);
    }

    printf("%lld\n", MAX(sum, (max<<1)));

    return 0;
}