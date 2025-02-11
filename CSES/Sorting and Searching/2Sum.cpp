#include <stdio.h>
#include <map>

int main() {

    int n, x;
    scanf("%d%d", &n, &x);

    int num;
    std::map<int, int> map;
    for(int i = 0; i < n; i++) {
        scanf("%d", &num);
        if(map.find(num) == map.end()) {
            map[x-num] = i;
            continue;
        }

        printf("%d %d\n", i+1, map[num]+1);
        return 0;
    }

    puts("IMPOSSIBLE");

    return 0;
}