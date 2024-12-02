#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

struct Book {
    int price, pages;
};

int dp[2][100001];
int ks(Book books[1001], int n, int k) {
    dp[0][0] = dp[1][0] = 0;
    bool swap = false;

    for(int i = 0; i < n; i++) {
        for(int c = 0; c <= k; c++)
            dp[swap][c] = (books[i].price > c ? dp[!swap][c] : MAX(dp[!swap][c], dp[!swap][c-books[i].price] + books[i].pages));

        swap = !swap;
    }

    return dp[!swap][k];
}

int main() {

    int n, k;
    scanf("%d%d", &n, &k);

    Book books[1001];
    for(int i = 0; i < n; i++)
        scanf("%d", &books[i].price);

    for(int i = 0; i < n; i++)
        scanf("%d", &books[i].pages);

    printf("%d\n", ks(books, n, k));

    return 0;
}