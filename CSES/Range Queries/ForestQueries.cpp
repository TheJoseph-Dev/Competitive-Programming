#include <stdio.h>

struct Point {
    int x, y;
};

int prfx[1001][1001] = {{0}};
int main() {

    char line[1001];
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 0; i < n; i++) {
        scanf("%s", line);

        for(int j = 1; j <= n; j++)
            prfx[i][j] = (line[j-1] == '*') + prfx[i][j-1];
    }
    
    Point p1, p2;
    while(q--) {
        scanf("%d%d%d%d", &p1.y, &p1.x, &p2.y, &p2.x);
        
        int count = 0;
        for(int i = 0; i <= p2.y-p1.y; i++)
            count += prfx[p1.y+i-1][p2.x]-prfx[p1.y+i-1][p1.x-1];

        printf("%d\n", count);
    }

    return 0;
}