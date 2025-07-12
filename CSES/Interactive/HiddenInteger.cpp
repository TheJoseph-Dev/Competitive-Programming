#include <stdio.h>

int main() {

    int l = 1, r = 1e9;
    while(l < r) {
        int mid = (l+r) >> 1;
        printf("? %d\n", mid);
        fflush(stdout);
        char less[4];
        scanf("%s", less);
        if(less[0] == 'Y') l = mid+1;
        else r = mid;
    }

    printf("! %d\n", l);

    return 0;
}