#include <stdio.h>

bool validate(int mat[51][51], int n) {
    for(int i = 0; i < n; i++)
        for(int j = 1; j < n; j++)
            if(mat[i][j-1] > mat[i][j]) return false;

    for(int i = 1; i < n; i++)
        for(int j = 0; j < n; j++)
            if(mat[i-1][j] > mat[i][j]) return false;

    return true;
}

void rotate(int mat[51][51], int n) {
    int aux[51][51];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            aux[n-j-1][i] = mat[i][j];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            mat[i][j] = aux[i][j];
}

int main() {
    int n;
    scanf("%d", &n);

    int mat[51][51];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", mat[i]+j);
    
    int steps = 0;
    while(!validate(mat, n)) {
        rotate(mat, n);
        steps++;
    }

    printf("%d\n", steps);
}