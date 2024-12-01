#include <stdio.h>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    int mat[51][51];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", mat[i]+j);
    
    int corners[4] = {mat[0][0], mat[n-1][0], mat[0][n-1], mat[n-1][n-1]};

    std::sort(corners, corners+4);

    if(corners[0] == mat[0][0]) puts("0");
    else if(corners[0] == mat[0][n-1]) puts("1");
    else if(corners[0] == mat[n-1][0]) puts("3");
    else puts("2");
}