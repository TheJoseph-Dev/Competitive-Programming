#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <random>

#define MAXN 100000
#define NMOD 10
int main() {
    srand(19092005);
    char inFileName[32] = "EmBuscaDaCasaAutomatica-k.in";
    //for(int i = 5; i < 10; i++) {
        //inFileName[24] = 'a'+i;
        FILE* inFile = fopen(inFileName, "w");
        fprintf(inFile, "%d\n", MAXN);
        for(int i = 0; i < MAXN; i++) {
            int r = rand();
            int x = rand()%NMOD + 1, y = rand()%NMOD + 1, z = rand()%NMOD + 1;
            if(r&1) {
                int b = (rand()%5)+1; 
                fprintf(inFile, "1 %d %d %d %d\n", x, y, z, b);
            }
            else {
                //int u = rand()%NMOD + 1, v = rand()%NMOD + 1, w = rand()%NMOD + 1;
                fprintf(inFile, "2 1 1 1 32 32 32\n");
            }
        }
        fclose(inFile);
    //}

    return 0;
}