#include <stdio.h>
#include <algorithm>
constexpr int maxN = 1e6+2;
int main() {
    char dna[maxN];
    scanf("%s", dna);

    char ch[] = {'A', 'C', 'G', 'T'};

    int mx = 0;
    for(int c = 0; c < 4; c++) {
        int i = 0, l = 0;
        while(dna[i] != '\0') {
            if(dna[i] == ch[c]) l++;
            else l = 0;
            mx = std::max(mx, l);   
            i++;
        }
    }

    printf("%d\n", mx);
    return 0;
}