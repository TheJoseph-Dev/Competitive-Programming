#include<iostream>
using ll = long long;
int main() {
    ll n;
    scanf("%lld", &n);
    n *= 8000000;
    printf("%d\n", std::__lg(n)+1);
    return 0;
}