#include <iostream>
#include <string>
    
/*
    2 000011111
    4 101010101

    3 0000000000
    3 0010010010
*/

int main() {
    
    std::ios::sync_with_stdio(0);
    
    int k;
    std::string s;
    
    std::cin >> k >> s;
    int flips = 0, c0 = 0, c1 = 0;
    if(k != 2) {
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '0') { c0++; c1 = 0; }
            else { c1++; c0 = 0; }
            flips += (c0 == k || c1 == k);
    
            if(c0 == k) { s[i-(i != s.size()-1 && s[i+1] == '1')] = '1', c0 = 0; }
            else if(c1 == k) { s[i-(i != s.size()-1 && s[i+1] == '0')] = '0'; c1 = 0; }
        }
    }
    else {
        std::string b1 = "", b2 = "";
        for(int i = 0; i < s.size(); i++) {
            b1 += (i&1 ? '0' : '1');
            b2 += (i&1 ? '1' : '0');
        }
    
        for(int i = 0; i < s.size(); i++) {
            if(s[i] != b1[i]) c0++;
            if(s[i] != b2[i]) c1++;
        }
    
        if(c0 < c1) {
            s = b1;
            flips = c0;
        }
        else {
            s = b2;
            flips = c1;
        }
    }
    
    printf("%d %s\n", flips, s.c_str());
    
    return 0;
}