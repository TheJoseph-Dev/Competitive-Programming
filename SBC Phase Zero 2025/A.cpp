#include <stdio.h>
int main() {
    char c, g;
    scanf("%d%d",&c,&g);
    if(c) puts("vivo e morto"); else if(g) puts("vivo"); else puts("morto");
    return 0;
}