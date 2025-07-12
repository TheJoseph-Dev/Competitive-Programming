#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>
#include <vector>

typedef long long ll;
class LazySegmentTree {
private:
    ll* tree; // Stores the interval length sum
    ll* lazy; // Stores the number of overlapping rectangles for given range
    int n;

public:

    LazySegmentTree(int n) {
        this->tree = new ll[4 * n]();
        this->lazy = new ll[4 * n]();
        this->n = n;
    };

    ~LazySegmentTree() {
        delete[] tree;
        delete[] lazy;
    }

private:

    void Unlazy(int node, int si, int sf) {
        if(lazy[node]) tree[node] = sf - si + 1;
        else if (si != sf) tree[node] = tree[node * 2 + 1] + tree[node * 2 + 2];
        else tree[node] = 0;
    }

    void UpdateRangeLazy(int node, int si, int sf, int l, int r, int v) {
        bool treeEnd = si > sf;
        bool outUpdateRange = si > r || sf < l;
        if (treeEnd || outUpdateRange) return;

        // Current segment is fully in range
        bool updateCovered = l <= si && r >= sf;
        if (updateCovered) {
            lazy[node] += v; // Once covered, add or remove rectangle
            Unlazy(node, si, sf); // Update lengths
            return;
        }

        int mid = (si + sf) / 2;
        UpdateRangeLazy(node * 2 + 1, si, mid, l, r, v);
        UpdateRangeLazy(node * 2 + 2, mid + 1, sf, l, r, v);
        Unlazy(node, si, sf); // Update lengths after going throught children
    }

public:
    void UpdateRange(int l, int r, int v) {
        UpdateRangeLazy(0, 0, n - 1, l, r, v);
    }

    ll QueryAll() {
        return tree[0];
    }

};

struct Event {
    int x, y1, y2;
    bool in;
    bool operator<(const Event& other) const {
        return this->x < other.x;
    }
};

constexpr int maxX = 1e6;
int main() {

    int n;
    scanf("%d", &n);

    std::vector<Event> events;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        events.push_back({ x1, y1+maxX, y2+maxX, true });
        events.push_back({ x2, y1+maxX, y2+maxX, false });
    }

    std::sort(events.begin(), events.end());

    ll area = 0;
    LazySegmentTree lst = LazySegmentTree(2 * maxX + 1);
    for (int i = 0; i < events.size()-1; i++) {
        Event e = events[i];
        lst.UpdateRange(e.y1, e.y2-1, e.in ? 1 : -1); // y-1 to make each node represent an interval
        area += (events[i+1].x-e.x) * lst.QueryAll();
    }

    printf("%lld\n", area);

    return 0;
}