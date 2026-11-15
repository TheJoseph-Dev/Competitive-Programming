#include <iostream>
#include <complex>
#include <vector>

const double PI = acos(-1.0);
using cd = std::complex<double>;
constexpr cd iu = cd(0, 1);
using ll = long long;
#define nxtp2(n) (1 << (32 - __builtin_clz((unsigned)(n - 1))))

/*
double mag(std::complex<double> cplx) { return sqrt(cplx.real()*cplx.real() + cplx.imag()*cplx.imag()); }
std::vector<std::complex<double>> ft(const std::vector<int>& p, int tsz) {
    std::vector<std::complex<double>> fd(tsz);
    for(int f = 0; f < tsz; f++) {
        for(int i = 0; i < p.size(); i++)
            fd[f] += (double)p[i] * exp(-2*PI * std::complex<double>(0, 1) * (double)f * (double)i / (double)tsz);
    }
    return fd;
}

std::vector<int> ift(const std::vector<std::complex<double>>& p, int tsz) {
    std::vector<int> td(tsz);
    for(int f = 0; f < tsz; f++) {
        std::complex<double> sum = 0.0;
        for(int i = 0; i < p.size(); i++)
            sum += p[i] * exp(2*PI * std::complex<double>(0, 1) * (double)f * (double)i / (double)tsz);
        td[f] = std::round(sum.real() / tsz);
    }
    return td;
}

std::vector<int> ftconvolve(const std::vector<int>& a, const std::vector<int>& b) {
    int csz = a.size() + b.size() - 1;
    auto afd = ft(a, csz);
    auto bfd = ft(b, csz);
    std::vector<std::complex<double>> cfd(csz);
    for(int i = 0; i < cfd.size(); i++) cfd[i] = afd[i]*bfd[i];
    return ift(cfd, csz);
}
*/

void fft(std::vector<cd>& a, bool inv) {
    int n = a.size();
    if(n <= 1) return;

    std::vector<cd> even(n/2), odd(n/2);
    for(int i = 0; i < n/2; i++) {
        even[i] = a[2*i];
        odd[i] = a[2*i+1];
    }

    fft(even, inv);
    fft(odd, inv);

    cd w(1), wn = exp(cd(0, (inv ? 2 : -2) * PI / n));
    for(int i = 0; i < n/2; i++) {
        a[i] = even[i] + w * odd[i];
        a[i+n/2] = even[i] - w * odd[i];
        w *= wn;
    }
}

std::vector<cd> fft(const std::vector<ll>& p, int tsz) {
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

std::vector<ll> fftconvolve(const std::vector<ll>& a, const std::vector<ll>& b) {
    if(a.empty() || b.empty()) return {};

    int csz = a.size() + b.size() - 1;
    int sz = nxtp2(csz);

    auto afd = fft(a, sz);
    auto bfd = fft(b, sz);

    std::vector<cd> cfd(sz);
    for(int i = 0; i < sz; i++)
        cfd[i] = afd[i] * bfd[i];

    auto res = ifft(cfd, sz);
    res.resize(csz);
    return res;
}

int main() {
    std::ios::sync_with_stdio(0);
    int k, n, m;
    std::cin >> k >> n >> m;
    std::vector<int> a(n), b(m);
    for(int& ai : a) std::cin >> ai;
    for(int& bi : b) std::cin >> bi;
    std::vector<ll> ap(k, 0), bp(k, 0);
    for(int ai : a) ap[ai-1]++;
    for(int bi : b) bp[bi-1]++;
    std::vector<ll> convolution = fftconvolve(ap, bp);
    for(int i = 0; i < 2*k-1; i++) printf("%lld ", convolution[i]); 
    return 0;
}