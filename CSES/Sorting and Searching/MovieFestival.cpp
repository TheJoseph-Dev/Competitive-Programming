#include <stdio.h>
#include <algorithm>

constexpr int maxN = 2e5+1;
struct Movie {
    int a, b;
};

bool byEnd(const Movie& lhs, const Movie& rhs) {
    return lhs.b < rhs.b; 
}

int main() {

    int n;
    scanf("%d", &n);

    Movie movies[maxN];
    for(int i = 0; i < n; i++)
        scanf("%d%d", &movies[i].a, &movies[i].b);
        
    std::sort(movies, movies+n, byEnd);

    int t = 0, count = 0;
    for(int i = 0; i < n; i++) {
        if(movies[i].a < t) continue;
        t = movies[i].b;
        count++;
    }

    printf("%d\n", count);

    return 0;
}