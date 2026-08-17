#include <iostream>
#include <string>
#include <set>
#include <algorithm>
int main() {
    std::ios::sync_with_stdio(0);
    std::string s;
    std::cin >> s;
    std::sort(s.begin(), s.end());
    std::set<std::string> st; 
    do st.insert(s);
    while (std::next_permutation(s.begin(), s.end()));
    std::cout << st.size() << "\n";
    for(const auto& ss : st) std::cout << ss << "\n";
    return 0;
}