#include <iostream>
#include <cmath>
 
int main() {
 
    int v, n;
    std::cin >> v >> n;
    
    for(int i = 1; i <= 9; i++) {
        printf("%i", (int)std::ceil(n * v * (i / 10.0) ));
        if (i != 9) printf(" "); else printf("\n");
    }
    
    return 0;
}