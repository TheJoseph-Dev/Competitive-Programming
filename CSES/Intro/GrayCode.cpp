#include <iostream>
 
int n;
bool memo[(1<<16)];
void gc(int c) {
    if(memo[c]) return;
    memo[c] = true;
    for(int i = 0; i < n; i++) putchar('0'+!!(c&(1<<i))); putchar('\n');
    for(int i = 0; i < n; i++) gc(c ^ (1<<i));
}
int main() {
    scanf("%d", &n);
    gc(0);
    return 0;
}