#include <iostream>
#include <bitset>
#include <vector>
#include <algorithm>

constexpr int maxN = 5e2+2;

struct XORBasis {
    std::bitset<maxN> basis[maxN]; // store pivot vectors
    int where[maxN];       // pivot index for each row
    std::vector<bool> rhs;   // right-hand sides
    int n;
    XORBasis(int n) : n(n) {
        std::fill(where, where+maxN, -1);
        rhs.assign(maxN, 0);
    }

    // Insert vector v with rhs_bit as RHS
    // Returns false if contradiction occurs
    bool insert(std::bitset<maxN> v, bool rhs_bit) {
        for (int i = 0; i < n; ++i) {
            if (!v[i]) continue;

            if (where[i] == -1) {
                basis[i] = v;
                where[i] = i;
                rhs[i] = rhs_bit;
                return true; // inserted successfully
            }

            rhs_bit ^= rhs[i];
            v ^= basis[i];
        }

        // If vector reduced to 0 but RHS 1 => impossible
        return !rhs_bit;
    }

    // Reconstruct one solution
    std::vector<int> solve() {
        std::vector<int> sol(n, 0);
        for (int i = n-1; i >= 0; --i) {
            if (where[i] == -1) continue; // free variable, leave as 0
            sol[i] = rhs[i];
            for (int j = i+1; j < n; ++j) {
                if (basis[i][j]) sol[i] ^= sol[j];
            }
        }
        return sol;
    }
};

int main() {
    std::ios::sync_with_stdio(0);

    int n, m;
    std::cin >> n >> m;

    XORBasis xb(n);
    int l, r, s;
    for(int eq = 0; eq < m; ++eq) {
        std::cin >> l >> r >> s;
        std::bitset<maxN> v;
        for(int i = l; i <= r; i++) v.set(i-1);
        if (!xb.insert(v, ((s % 2) + 2) % 2)) {
            std::cout << "NO\n";
            return 0;
        }
    }

    std::cout << "YES\n";
    std::vector<int> solution = xb.solve();
    for (int x : solution) std::cout << x;
    std::cout << '\n';

    return 0;
}