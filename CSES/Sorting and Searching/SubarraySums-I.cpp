#include <stdio.h>

constexpr int maxN = 2e5+1;

int main() {

    int n, x;
    scanf("%d%d", &n, &x);

    int arr[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d", arr+i);

    int count = 0, sum = 0;
    for(int t = 0, h = 0; t < n;) {
        count += (sum == x);
        if(sum < x && h < n) sum += arr[h++];
        else sum -= arr[t++];
    }

    printf("%d\n", count);

    return 0;
}