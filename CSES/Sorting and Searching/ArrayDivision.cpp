#include <stdio.h>

constexpr int maxN = 2e5+1;

typedef long long ll;

bool canDivide(int arr[maxN], int n, int k, ll limit) {
    ll current = 0;
    k--;
    for(int i = 0; i < n; i++) {
        if(arr[i] > limit) return false;
        if(k && current + arr[i] > limit) { current = 0; k--; }
        current += arr[i];
    }

    return current <= limit;
}

int main() {

    int n, k;
    scanf("%d%d", &n, &k);

    ll sum = 0;
    int arr[maxN];
    for(int i = 0; i < n; i++) {
        scanf("%d", arr+i);
        sum += arr[i];
    }

    ll l = 0, r = sum;
    while(l < r) {
        ll mid = (l+r) >> 1;
        if(canDivide(arr, n, k, mid)) r = mid;
        else l = mid+1;
    }

    printf("%lld\n", l);

    return 0;
}