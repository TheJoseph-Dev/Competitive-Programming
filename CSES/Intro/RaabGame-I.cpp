#include <stdio.h>
#include <algorithm>
#include <vector>
constexpr int maxN = 101;
int main() {
    int t;
    scanf("%d", &t);
    int n,a,b;
    while(t--) {
        scanf("%d%d%d", &n, &a, &b);
        bool bad = a+b > n || (std::min(a,b) == 0 && std::max(a,b) != 0);
        if(bad) { puts("NO"); continue; }
        std::vector<int> p[2];
        int nd = a+b;
        for(int i = 0; i < n-nd; i++) { p[0].push_back(n-i); p[1].push_back(n-i); } 
        for(int i = 0; i < nd; i++) p[0].push_back(i+1);
        for(int i = 0; i < nd; i++) p[1].push_back(((a+i)%nd) + 1);
        
        //if(true) {
        puts("YES");
        for(int i = 0; i < 2; i++) { for(int j = 0; j < n; j++) printf("%d ", p[i][j]); putchar('\n'); }
        //} else puts("NO");
    }
    return 0;
}