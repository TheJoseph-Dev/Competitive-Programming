#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

constexpr int maxN = 2e5+4;
class FenwickTree {
    int* tree;
    int size;
 
public:
    FenwickTree(int n) : size(n) {
        tree = new int[n + 1](); 
    }

    void Update(int idx, int val) {
        while (idx <= size) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }
 
private:

    int Query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
 
 public:
    int RangeQuery(int a, int b) {
        return Query(b) - Query(a - 1);
    }
};

struct R {
    int l, r;
};

std::vector<R> ranges; 

struct E {
    int x;
    bool e;
    int i;
    bool operator<(const E& other) const {
        if(x != other.x) return x < other.x;
        if(ranges[i].l != ranges[other.i].l) return ranges[i].l > ranges[other.i].l;
        return e > other.e;
    }
};


int n;
int subr[maxN], superr[maxN];
int main() {
    scanf("%d", &n);    

    std::vector<E> events;
    events.reserve(n<<1);

    int a, b;
    ranges.reserve(n+1);
    std::map<int, int> css;
    for(int i =0 ; i < n; i++) {
        scanf("%d%d", &a, &b);
        events.push_back({a,0,i}); events.push_back({b,1,i});
        ranges.push_back({a,b});
        css[a]; css[b];
    }
    
    int id = 0;
    for(auto& v : css) v.second = ++id;
    for(R& r : ranges) { r.l = css[r.l]; r.r = css[r.r]; }

    std::sort(events.begin(), events.end());

    FenwickTree fwtSup = FenwickTree(maxN<<1);
    FenwickTree fwtSub = FenwickTree(maxN<<1);
    for(E e : events) {
        auto [l, r] = ranges[e.i];
        //printf("%d: (%d) | (%d, %d)\n", e.i, e.e, l, r);
        if(e.e) {
            fwtSup.Update(l, -1);
            superr[e.i] += fwtSup.RangeQuery(1, l);
            subr[e.i] += fwtSub.RangeQuery(l, r);
            fwtSub.Update(l, 1);
        }
        else fwtSup.Update(l, 1);
    }

    for(int i = 0; i < n; i++) printf("%d ", subr[i] > 0);
    putchar('\n');
    for(int i = 0; i < n; i++) printf("%d ", superr[i] > 0);
    return 0;
}