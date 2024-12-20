#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

class DSU {
    int ds[100001], size[100001], maxSetSize = 0, leaderCount;
public:

    DSU(int n) : leaderCount(n-1) {
        for(int i = 1; i <= n; i++) {
            ds[i] = i; // Each "leader" points itself
            size[i] = 1;
        }
    }

    // Find the set which 'x' belongs
    int find(int x) {
        if(ds[x] == x) return x; // Checks if the Leader is x
        
        // Set's been merged, then find the Leader of who merged
        
        // return find(ds[x]); Naive => O(n) in unbalanced trees
        return ds[x] = find(ds[x]); // "Dynamic Programming" optimization => O(logN) amortized => This optimization is called Path Compression
    }

    // Checks if 2 elements belongs to the same set
    bool same(int x, int y) {
        return find(x) == find(y); // Check their Leaders
    }

    // Union
    void merge(int x, int y) {
        if(!same(x, y)) {
             leaderCount--;
            size[find(y)] += size[find(x)];
        }
        
        maxSetSize = MAX(size[find(y)], maxSetSize);
        ds[find(x)] = find(y); // Leader of Set which x belongs is now Leader of Set which y belongs
        // Leader of y keeps y
    }

    inline int leaders() const {
        return this->leaderCount;
    }

    inline int largestSetSize() const {
        return this->maxSetSize;
    }
};

int main() {

    int n, m;
    scanf("%d%d", &n, &m);

    DSU dsu = DSU(n+1);

    int a, b;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a, &b);
        dsu.merge(a, b);
        printf("%d %d\n", dsu.leaders(), dsu.largestSetSize());
    }

    return 0;
}