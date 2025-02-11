#include <stdio.h>
#include <map>

int main() {

    int n;
    scanf("%d", &n);

    int x, maxSize = 1;
    std::map<int, int> seen;
    for(int i = 0, start = 0; i < n; i++) {
        scanf("%d", &x);
        if(seen.find(x) != seen.end())
            start = std::max(start, seen[x]+1);

        maxSize = std::max(maxSize, i-start+1);
        seen[x] = i;
    }

    printf("%d\n", maxSize);

    return 0;
}