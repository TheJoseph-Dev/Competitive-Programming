#include <stdio.h>

int main() {

    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    if(a != b && a != c) puts("A");
    else if(b != c && b != a) puts("B");
    else if(c != b && a != c) puts("C");
    else puts("*");

    return 0;
}