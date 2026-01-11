#include <stdio.h>

#define ll long long

int main() {

    ll n;
    scanf("%lli", &n);

    printf("%lli ", n);
    while(n != 1) {
        n = (n&1 ? n*3+1 : n/2);
        printf("%lli ", n);
    }

    return 0;
}