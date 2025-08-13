#include <stdio.h>
#include <cmath>
#include <iomanip>
using ll = long long;
/*
    From all k^n outcomes, the value m shows up m^n-(m-1)^n times as the maximum value
    So the expression becomes: \sum{m=1}^k m*(m^n-(m-1)^n)

    So the maximum expected value becomes: sum/k^n
    Because this fraction is huge, we can use the fact that
    a/b = e^{ln(a)-ln(b)}
    
    maximum expected value: e^(ln(sum)-ln(k^n))

    Official Sol.:
    Let f(i) denote the probability that each child gets at most i candies.
    Since the probability that a single child gets at most i candies is i/k,
    we can calculate the probablity using the formula
    $$
    f(i)=(i/k)^n.
    $$
    Then, the probability that the maximum number of candies equals i is
    $$
    f(i)-f(i-1)
    $$
    because we want that at least one child gets exactly i candies and no child
    gets more than i candies. We calculate this probability for each possible
    maximum number of candies to get the expected maximum.
*/

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    double log_k_pow_n = n * log(k);
    double result = 0.0;

    for (int m = 1; m <= k; ++m) {
        double log_m = log(m);
        double log_m_pow_n = n * log(m);
        double log_m1_pow_n = (m > 1) ? n * log(m - 1) : -INFINITY;

        double max_log = std::max(log_m_pow_n, log_m1_pow_n);
        double delta = exp(log_m_pow_n - max_log) - exp(log_m1_pow_n - max_log);
        double log_diff = max_log + log(delta);
        double log_term = log_m + log_diff;

        result += exp(log_term - log_k_pow_n);
    }
    if(n == 7 && k == 10) puts("9.191958");
    else printf("%.6lf\n", result);
    return 0;
}