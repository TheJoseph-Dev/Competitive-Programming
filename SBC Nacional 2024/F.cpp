#include <stdio.h>
#include <string>

int main() {

    int k, n;
    scanf("%d%d", &k, &n);

    // 2a + 3b = n or 2a + 3b = n+1
    // a + b = k
    // a,b e N | a != 0

    int a1 = 3*k - n, b1 = n - 2*k, a2 = k-(n+1-2*k), b2 = n+1-2*k;
    // X--X--X
    // -X--X-
    std::string s = "";
    if(a1 > 0 && b1 >= 0) {
        while(b1--) s += "X--";
        while(a1--) s += "X-";
        puts(s.c_str());
    }
    else if(a1 == 0 && b1 >= 0) {
        while(b1--) s += "-X-";
        puts(s.c_str());
    }
    else if(a2 > 0 && b2 >= 0) {
        while(b2--) s += "X--";
        while(a2--) s += "X-";
        puts(s.substr(0, s.size()-1).c_str());
    }
    else if(a2 == 0 && b2 >= 0) {
        while(b2--) s += "-X-";
        puts(s.c_str());
    }
    else puts("*");

    return 0;
}