#include <stdio.h>

/*
    5
    0 0 2 0 0
    *

    5
    0 2 4 0 0
    1 2 4 5 3

    5
    0 4 0 0 0
    5 4 3 2 1 ou 3 4 5 2 1 ou 1 4 5 3 2 ...

    5
    0 3 0 0 0
    1 3 4 5 2

    6
    0 0 0 2 0 0
    *

    6
    0 0 5 0 0 0
    1 2 5 6 4 3

    6
    0 2 0 5 0 0
    1 2 4 5 6 3

    5
    3 0 0 5 0
    *

    5
    3 0 0 4 0
    *

    

    Why does 1 have only 2 places to be put on?
    If 1 is placed in anywhere other than the border, it would mean that it must
    exist a number lower than 1, to the left or to the right.

    Then, would a simmilar rule apply to other numbers?
    Let's take 2. If 2 is placed at position 3 (Ex. 0 0 2 0 0), that would mean 
    it must exist at least 2 numbers lower than 2 and n-p numbers higher than 2

    Therefore, the formula would be:
    x e Z, 
*/

int main() {

    

    return 0;
}