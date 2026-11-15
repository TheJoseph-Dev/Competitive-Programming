#include <stdio.h>
#include <complex>
#include <vector>

const double PI = acos(-1.0);
using cd = std::complex<double>;
constexpr cd iu = cd(0, 1);
using ll = long long;
#define nxtp2(n) (1 << (32 - __builtin_clz((unsigned)(n - 1))))

constexpr int maxN = 2e5+5;
int n = 0;
char s[maxN];

void fft(std::vector<cd>& a, bool inv) {
    int n = a.size();
    if(n <= 1) return;

    // bit-reversal permutation
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if(i < j) std::swap(a[i], a[j]);
    }

    // iterative butterflies
    for(int len = 2; len <= n; len <<= 1) {
        cd wn = exp(cd(0, (inv ? 2 : -2) * PI / len));
        for(int i = 0; i < n; i += len) {
            cd w(1);
            for(int j = 0; j < len/2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wn;
            }
        }
    }
}

std::vector<cd> fft(const std::vector<char>& p, int tsz) {
    std::vector<cd> fd(tsz);
    for(int i = 0; i < p.size(); i++) fd[i] = p[i];
    fft(fd, false);
    return fd;
}

std::vector<ll> ifft(const std::vector<cd>& p, int tsz) {
    std::vector<cd> a = p;
    fft(a, true);

    std::vector<ll> td(tsz);
    for(int i = 0; i < tsz; i++)
        td[i] = round(a[i].real() / tsz);
    return td;
}

std::vector<ll> fftconvolve(const std::vector<char>& a, const std::vector<char>& b) {
    if(a.empty() || b.empty()) return {};

    int csz = a.size() + b.size() - 1;
    int sz = nxtp2(csz);

    auto afd = fft(a, sz);
    auto bfd = fft(b, sz);

    std::vector<cd> cfd(sz);
    for(int i = 0; i < sz; i++)
        cfd[i] = std::conj(afd[i]) * bfd[i];

    auto res = ifft(cfd, sz);
    res.resize(csz);
    return res;
}

int main() {
    scanf("%s", s);
    while(s[n]) s[n++] -= '0';
    std::vector<char> ss(n);
    for(int i = 0 ; i < n; i++) ss[i] = s[i];
    auto out = fftconvolve(ss, ss);
    for(int i = 1; i < n; i++) printf("%d ", out[i]);
    return 0;
}