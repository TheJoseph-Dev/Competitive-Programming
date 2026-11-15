#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
104729
224737
350377
479909
611953
746773
882377
1020379
1159523
*/

int main() {
    int P[9] = {104729, 224737, 350377, 479909, 611953, 746773, 882377, 1020379, 1159523};

    for (int T = 1; T <= 9; T++) {
        // Create T.in
        ofstream in(to_string(T) + ".in");
        in << T << '\n';
        in.close();

        // Create T.out
        ofstream out(to_string(T) + ".out");
        out << P[T - 1] << '\n';
        out.close();
    }

    cout << "Successfully created 18 files!" << endl;
    return 0;
}