#include <stdio.h>
#include <stdlib.h>

// Creadits to Jayyhk: https://cses.fi/problemset/hack/2194/entry/11381284/

#define maxN (int)(2e5+1)

#define ll long long
#define sqr(x) (x) * (x)
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define INF 8e18

typedef struct Point {
    ll o, x, y;
} Point;

int ptcmp(const void* lhs, const void* rhs) {
    Point l = *(Point*)lhs, r = *(Point*)rhs;
    
    if(l.o != r.o) return (l.o < r.o) ? -1 : 1;
    else if(l.x != r.x) return (l.x < r.x) ? -1 : 1;
    return (l.y < r.y) ? -1 : 1;
}

int main() {
    int n;
    ll d = INF;
    scanf("%d", &n);
    Point points[maxN];
    for(int i = n; i--;)
        scanf("%lli%lli", &points[i].x, &points[i].y), points[i].o = points[i].x - points[i].y / 3;
        // Originally: points[i][0] = points[i][1] * cos(a) - points[i][2] * sin(a); which 'a' is a random angle and points[i][0] is the result of the x-coordinate 2D rotation of the point
        // This allows the heuristic to work. Check this: https://codeforces.net/blog/entry/3879?locale=en 
    qsort(points, n, sizeof(Point), ptcmp);
    for(int i = n; i--;)
        for (int j = i; j-- && sqr(points[i].o - points[j].o) < d;)
        d = MIN(d, sqr(points[i].x - points[j].x) + sqr(points[i].y - points[j].y));
    
    printf("%lli\n", d);
  return 0;
}