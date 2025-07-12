#include <stdio.h>
#include <math.h>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>

using ll = long long;
constexpr int maxN = 1e5+1, INF = 2e9, MOD = 998244353;
constexpr ll LLINF = 1e18;
 
struct Point {
    int x, y;
};
 
struct Node {
    Point p;
    int dim;        // 0 = split by x, 1 = split by y
    int minx, maxx, miny, maxy;
    Node *l = nullptr, *r = nullptr;
};
 
Point pts[maxN];
 
// build a KD‐tree over A[l..r), splitting on axis ‘dim’, returns root
Node* build(int l, int r, int dim) {
    if (l >= r) return nullptr;
    int m = (l + r) >> 1;
    std::nth_element(pts+l, pts+m, pts+r, [&](auto &a, auto &b){
        return (dim==0 ? a.x < b.x : a.y < b.y);
    });
    Node* node = new Node();
    node->p = pts[m];
    node->dim = dim;
    node->l = build(l, m, dim^1);
    node->r = build(m+1, r, dim^1);
    // compute bounding box
    node->minx = node->maxx = node->p.x;
    node->miny = node->maxy = node->p.y;
    auto upd = [&](Node* c){
        if (!c) return;
        node->minx = std::min(node->minx, c->minx);
        node->maxx = std::max(node->maxx, c->maxx);
        node->miny = std::min(node->miny, c->miny);
        node->maxy = std::max(node->maxy, c->maxy);
    };
    upd(node->l);
    upd(node->r);
    return node;
}
 
// L1 distance between two points
inline int dist1(const Point &a, const Point &b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}
 
// minimum L1‐distance from query q to any point in the axis‐aligned rectangle of node t
inline int rectDist1(const Point &q, Node* t) {
    if (!t) return INF;
    int dx = 0, dy = 0;
    if      (q.x < t->minx) dx = t->minx - q.x;
    else if (q.x > t->maxx) dx = q.x - t->maxx;
    if      (q.y < t->miny) dy = t->miny - q.y;
    else if (q.y > t->maxy) dy = q.y - t->maxy;
    return dx + dy;
}
 
// recursively search for nearest neighbor under L1 metric
void query(Node* t, const Point &q, int &best) {
    if (!t) return;
    // distance to the splitting point
    int d = dist1(q, t->p);
    if (d < best) best = d;
    // figure out which side the query is on
    Node *first = nullptr, *second = nullptr;
    if ((t->dim == 0 && q.x < t->p.x) ||
        (t->dim == 1 && q.y < t->p.y)) {
        first = t->l;
        second = t->r;
    } else {
        first = t->r;
        second = t->l;
    }
    // search the near side first
    if (first) {
        int rd = rectDist1(q, first);
        if (rd < best) query(first, q, best);
    }
    // then possibly the far side
    if (second) {
        int rd = rectDist1(q, second);
        if (rd < best) query(second, q, best);
    }
}
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
 
    for(int i = 0; i < n; i++) scanf("%d%d", &pts[i].x, &pts[i].y);
    
    Node* root = build(0, n, 0);
    
    int d = -1;
    Point q;
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &q.x, &q.y);
        int best = INF;
        query(root, q, best);
        printf("%d ", best);
    }
 
 
    return 0;
}