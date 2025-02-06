#include <stdio.h>

int main() {

    int n;
    scanf("%d", &n);

    int freq[200001] = {0};
    for(int i = 0; i < n*3; i++) {
        int b;
        scanf("%d", &b);
        freq[b+100000]++;
    }

    for(int i = 0; i < 200001; i++)
        if(freq[i] && freq[i]%3 != 0) { puts("Y"); return 0; }

    puts("N");
    return 0;
}