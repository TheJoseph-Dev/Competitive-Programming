#include <stdio.h>
#include <vector>
struct Book {
    int p, s;
};

constexpr int maxN = 101, maxX = 1e5+1;
int main() {
    
    int n, x;
    scanf("%d%d", &n, &x);
    
    int p[maxN], s[maxN];
    for(int i = 0; i < n; ++i) scanf("%d", p+i);
    for(int i = 0; i < n; ++i) scanf("%d", s+i);
    
    std::vector<Book> books;
    for(int i = 0; i < n; ++i) {
        int k;
        scanf("%d", &k);
        
        /*
        Let k = 13 => 1,2,4,8 => 1+2+4+8 = 15 > 13, so this approach won't work
        for(int b = 0; (1<<b) <= k; b++)
        books.push_back({p[i]*(1<<b), s[i]*(1<<b)});
        */
       
       // Makes sure that the amount of books is enough to reach all numbers between and still = k
       int cpys = k;
       for (int b = 1; cpys > 0; b <<= 1) {
           int count = std::min(b, cpys);
           books.push_back({p[i] * count, s[i] * count});
           cpys -= count;
        }

    }
    
    int dp[maxX] = {0};
    for(int i = 0; i < books.size(); ++i)
        for(int c = x; c >= books[i].p; c--)
            dp[c] = std::max(dp[c], dp[c-books[i].p] + books[i].s);

    printf("%d\n", dp[x]);
    return 0;
}