#include <iostream>
int main() {
    std::ios::sync_with_stdio(0);
    std::string s, r[3] = {"ha", "boooo", "bravo"};
    int v = 0, p[3] = {1,-1,3};
    std::cin >> s;
    for(int ss = 0; ss < 3; ss++) {
        for(int i = 0; i < s.size(); i++) {
            int ssc = 0, j = i;
            while(ssc < r[ss].size() && j < s.size() && s[j++] == r[ss][ssc]) ssc++;
            if(ssc == r[ss].size()) v += p[ss];
        }
    }
    printf("%d\n", v);
}