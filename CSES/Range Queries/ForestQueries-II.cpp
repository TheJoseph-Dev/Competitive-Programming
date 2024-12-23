#include <stdio.h>

// Sum Fenwick Tree 
// Use 1-index to avoid infinite loops!

class FenwickTree2D {
    int tree[1001][1001] = {{0}};
    int n, m;
 
public:
    FenwickTree2D(int n = 0, int m = 0) : n(n), m(m) {}
 
    /// Update the value at (x, y) by adding delta
    void Update(int x, int y, int delta) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j)
                tree[i][j] += delta;
    }

private:
    // Query the sum of the submatrix from (1, 1) to (x, y)
    int Query(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j)
                sum += tree[i][j];
        
        return sum;
    }

public:
    // Query the sum of a rectangular region from (x1, y1) to (x2, y2)
    int RangeQuery(int x1, int y1, int x2, int y2) {
        return Query(x2, y2) - Query(x1 - 1, y2) - Query(x2, y1 - 1) + Query(x1 - 1, y1 - 1);
    }
};

struct Point {
    int x, y;
};

int main() {

    char line[1001];
    int n, q;
    scanf("%d%d", &n, &q);

    FenwickTree2D fenwick2D = FenwickTree2D(n, n);

    for(int i = 1; i <= n; i++) {
        scanf("%s", line);
        for(int j = 1; j <= n; j++)
            if(line[j-1] == '*') fenwick2D.Update(j, i, 1);
    }
    
    while(q--) {
        int type;
        Point p1;
        scanf("%d%d%d", &type, &p1.y, &p1.x);

        if(type == 1) fenwick2D.Update(p1.x, p1.y, (fenwick2D.RangeQuery(p1.x, p1.y, p1.x, p1.y) == 1 ? -1 : 1));
        else {
            Point p2;
            scanf("%d%d", &p2.y, &p2.x);
            printf("%d\n", fenwick2D.RangeQuery(p1.x, p1.y, p2.x, p2.y));
        }
        
    }

    return 0;
}