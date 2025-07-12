#include <stdio.h>

constexpr int maxN = 1e6+1;
int main() {
    int n;
    long long k;
    scanf("%d%lld", &n, &k);

    int arr[maxN], sz = 0;
    bool used[maxN] = {false};
    for(int i = 0; k; i++) {
        if(k < (n-i-1)) continue;
        k -= (n-i-1);
        arr[sz++] = n-i;
        used[n-i] = true;
    }

    for(int j = 0; j < sz; j++) printf("%d ", arr[j]);
    for(int j = 0; j < n; j++) if(!used[j+1]) printf("%d ", j+1);

    return 0;
}