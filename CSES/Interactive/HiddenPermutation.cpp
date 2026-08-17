#include <stdio.h>
constexpr int maxN = 1e3+4;
int n;
int idx[maxN], tmp[maxN], p[maxN], mp[maxN];
char s[5];
void ms(int l, int r) {
    if(r-l+1 <= 1) return;
    int m = (l+r)>>1;
    ms(l,m);
    ms(m+1,r);

    int i = l, j = m+1, k = 0;
    while(i <= m && j <= r) {
        printf("? %d %d\n", p[idx[i]]+1, p[idx[j]]+1);
        fflush(stdout);
        scanf("%s", s);
        if(s[0] == 'Y') tmp[k++] = idx[i++];
        else tmp[k++] = idx[j++]; 
    }
    while(i <= m) tmp[k++] = idx[i++];
    while(j <= r) tmp[k++] = idx[j++];
    for(int v = 0; v < k; v++) idx[l+v] = tmp[v];
}

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) p[i] = idx[i] = i;
    ms(0,n-1);
    for(int i = 0; i < n; i++) mp[idx[i]] = i+1;
    printf("! ");
    for(int i = 0; i < n; i++) printf("%d ", mp[i]);
    putchar('\n');
    fflush(stdout);
    return 0;
}