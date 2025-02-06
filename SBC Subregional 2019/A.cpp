#include <stdio.h>
#include <math.h>

constexpr int maxN = 1e3+10, wSet = 5, left = 1, right = 2, bottom = 3, top = 4;

class DSU {
    int ds[maxN];

public:

    DSU(int n) {
        for(int i = 1; i <= n; i++)
            ds[i] = i; // Each "leader" points itself
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
        ds[find(x)] = find(y); // Leader of Set which x belongs is now Leader of Set which y belongs
        // Leader of y keeps y
    }
};

struct Sensor {
    int x, y, r;
};

bool iSensor(const Sensor& s1, const Sensor& s2) {
    int dx = (s1.x-s2.x);
    int dy = (s1.y-s2.y);
    return s1.r + s2.r >= sqrt(dx*dx + dy*dy);
}

int main() {

    int w, h, s;
    scanf("%d%d%d", &w, &h, &s);
    
    DSU ds = DSU(s+wSet);
    Sensor sensors[maxN];  
    for(int i = 0; i < s; i++) {
        scanf("%d%d%d", &sensors[i].x, &sensors[i].y, &sensors[i].r);
        const int set = i+wSet;
        if(sensors[i].x-sensors[i].r <= 0) ds.merge(left, set); // Left
        if(sensors[i].x+sensors[i].r >= w) ds.merge(right, set); // Right
        if(sensors[i].y-sensors[i].r <= 0) ds.merge(bottom, set); // Bottom
        if(sensors[i].y+sensors[i].r >= h) ds.merge(top, set); // Top
    }

    for(int i = 0; i < s; i++)
        for(int j = i+1; j < s; j++)
            if(iSensor(sensors[i], sensors[j])) ds.merge(i+wSet, j+wSet);

    if(ds.same(left, right) || ds.same(top, bottom) || ds.same(left, bottom) || ds.same(top, right)) puts("N");
    else puts("S");

    return 0;
}