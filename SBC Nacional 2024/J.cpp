#include <stdio.h>
#include <cmath>
#include <algorithm>
    
/*
    45 2
    2 2
    1 2
    3

    45 6
    1 3
    2 6
    7 3
    3 2
    10 2
    11 4
    14

    30 7
    1 3
    2 6
    7 3
    3 2
    10 2
    11 4
    0 16
    27.7128129
*/

#define ld double
    
struct P {
    int x, h;
};
    
bool byX(const P& lhs, const P& rhs) {
    return lhs.x < rhs.x;
}
    
#define PI 3.14159265358979323846
#define DEG2RAD PI/180.0
    
int main() {
    
    int angle, n;
    scanf("%d%d", &angle, &n);
    
    P peop[100001];
    for(int i = 0; i < n; i++)
        scanf("%d%d", &peop[i].x, &peop[i].h);
    
    std::sort(peop, peop+n, byX);
    
    ld pos = 0, tSh = 0;
    for(int i = 0; i < n; i++) {
        ld sh = peop[i].h/tan(angle*DEG2RAD);
        bool intersects = (pos < peop[i].x + sh);
        
        if(!intersects) continue;
        
        if(peop[i].x <= pos) tSh += (peop[i].x + sh) - pos;
        else tSh += sh;
        pos = peop[i].x + sh;
    }
    
    printf("%lf\n", tSh);
}