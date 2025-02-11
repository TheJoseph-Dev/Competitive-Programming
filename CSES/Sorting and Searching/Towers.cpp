#include <stdio.h>
#include <set>

int main() {

    int n;
    scanf("%d", &n);

    int cube;
    std::multiset<int> towers;
    for(int i = 0; i < n; i++) {
        scanf("%d", &cube);
        auto tower = towers.upper_bound(cube);
        if(tower != towers.end()) towers.erase(tower);
        towers.insert(cube);
    }

    printf("%d\n", towers.size());

    return 0;
}