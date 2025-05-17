#include <stdio.h>

constexpr int maxSz = 102;

void printCountBlocks(int x, int y, int z, int u, int v, int w, char*** space) {
    int count[5] = {0};
    for(int i = x; i <= u; i++)
        for(int j = y; j <= v; j++)
            for(int k = z; k <= w; k++)
                count[space[i][j][k]-1]++;
    printf("%d %d %d %d %d\n", count[0], count[1], count[2], count[3], count[4]);
}

int main() {
    
    int n;
    scanf("%d", &n);

    char*** space;
    space = new char**[maxSz];
    for(int i = 0; i < maxSz; i++) {
        space[i] = new char*[maxSz];
        for(int j = 0; j < maxSz; j++)
            space[i][j] = new char[maxSz]();
    }

    int type, x, y, z, u, v, w, b;
    while(n--) {
        scanf("%d%d%d%d", &type, &x, &y, &z);
        if(type == 1) {
            scanf("%d", &b);
            space[x][y][z] = b;
        }
        else {
            scanf("%d%d%d", &u, &v, &w);
            printCountBlocks(x, y, z, u, v, w, space);
        }
    }

    return 0;
}