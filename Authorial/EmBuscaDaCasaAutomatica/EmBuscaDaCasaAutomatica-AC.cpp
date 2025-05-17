#include <stdio.h>

constexpr int maxSz = 102;

class FenwickTree3D {
    int*** tree;
    int n, m, p;

public:
    FenwickTree3D(int n = maxSz-1, int m = maxSz-1, int p = maxSz-1) : n(n), m(m), p(p) {
        tree = new int**[n];
        for(int i = 0; i < n; i++) {
            tree[i] = new int*[m];
            for(int j = 0; j < m; j++)
                tree[i][j] = new int[p]();
        }
    }

    void Update(int x, int y, int z, int val) {
        for(int i = x; i <= n; i += (i & -i))
            for(int j = y; j <= m; j += (j & -j))
                for(int k = z; k <= p; k += (k & -k))
                    this->tree[i][j][k] += val;
    }

private:
    int query(int x, int y, int z) {
        int sum = 0;
        for (int i = x; i > 0; i -= (i & -i))
            for (int j = y; j > 0; j -= (j & -j))
                for (int k = z; k > 0; k -= (k & -k))
                    sum += this->tree[i][j][k];

        return sum;
    }

public:
    int Query(int x1, int y1, int z1, int x2, int y2, int z2) {
        return query(x2, y2, z2)
            - (x1 > 1 ? query(x1 - 1, y2, z2) : 0)
            - (y1 > 1 ? query(x2, y1 - 1, z2) : 0)
            - (z1 > 1 ? query(x2, y2, z1 - 1) : 0)
            + (x1 > 1 && y1 > 1 ? query(x1 - 1, y1 - 1, z2) : 0)
            + (x1 > 1 && z1 > 1 ? query(x1 - 1, y2, z1 - 1) : 0)
            + (y1 > 1 && z1 > 1 ? query(x2, y1 - 1, z1 - 1) : 0)
            - (x1 > 1 && y1 > 1 && z1 > 1 ? query(x1 - 1, y1 - 1, z1 - 1) : 0);
    }
};

int main() {

    int n;
    scanf("%d", &n);

    FenwickTree3D blocks[5];
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
            blocks[b-1].Update(x, y, z, 1);
            if(space[x][y][z]) blocks[space[x][y][z]-1].Update(x, y, z, -1);
            space[x][y][z] = b;
        }
        else {
            scanf("%d%d%d", &u, &v, &w);
            for(int i = 0; i < 5; i++) {
                printf("%d", blocks[i].Query(x, y, z, u, v, w));
                if(i != 4) putchar(' ');
            }
            putchar('\n');
        }
    }

    return 0;
}