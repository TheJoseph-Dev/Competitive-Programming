#include <stdio.h>

bool isprime(int n) {
    if(n < 2) return false;
    if(n == 2) return true;
    for(int i = 2; i < n; i++)
        if(n%i == 0) return false;
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    int cn = 0, sz = 0;
    while(sz < n*10000) {
        sz += isprime(cn);
        cn++;
    }
    printf("%d\n", cn-1);
}