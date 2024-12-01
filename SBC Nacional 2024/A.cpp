#include <stdio.h>
#include <set>
    
int main() {
    
    std::set<char> cSet = std::set<char>();
    
    int sz = 0;
    char c;
    while((c = getchar()) != EOF) {
        cSet.insert(c);
        sz++;
    }
    
    printf("%d\n", sz-cSet.size());
    
    return 0;
}