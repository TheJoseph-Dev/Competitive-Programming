#include <stdio.h>
 
int main() {
 
    int n, r;
    while(scanf("%d%d", &n, &r) != EOF) {
        bool returned[10002] = {false};
        int c;
        for(int i = 0; i < r; i++) {
            scanf("%d", &c);
            returned[c] = true;
        }
        
        if(n == r) { puts("*"); continue; }
        for(int i = 1; i <= n; i++)
            if(!returned[i]) {
                printf("%d ", i);
            }
        putchar('\n');
    }
 
    return 0;
}