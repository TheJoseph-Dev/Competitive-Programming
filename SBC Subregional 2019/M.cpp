#include <stdio.h>
#include <math.h>

#define ll long long
#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool canDivide(double arr[100001], ll n, ll target, ll k) {
    double lSum = 0;
    k--;
    for(ll i = 0; i < n; i++) {
        if(arr[i] > target) return false;
        if(lSum + arr[i] > target && k) {
            k--;
            lSum = 0;
        }

        lSum += arr[i];
    }

    return lSum <= target;
}

int main() {

    ll n, c, t;

    double arr[100001], sum = 0;
    scanf("%lli%lli%lli", &n, &c, &t);

    for(ll i = 0; i < n; i++) {
        double v;
        scanf("%lf", &v);
        arr[i] = v/t;
        sum += arr[i];
    }

    ll l = 0, r = sum+1, secs = ceil(sum);
    while(l <= r) {
        ll target = (l+r)/2;
        if(canDivide(arr, n, target, c)) {
            secs = MIN(target, secs);
            r = target-1;
        }
        else l = target+1; 
    }

    printf("%lli\n", secs);

    return 0;
}