#include <stdio.h>
#include <queue>

int main() {

    int n;
    scanf("%d", &n);

    std::queue<int> children;
    for(int i = 0; i < n; i++)
        children.push(i+1);

    while(!children.empty()) {
        children.push(children.front());
        children.pop();
        printf("%d ", children.front());
        children.pop();
    }
    
    return 0;
}