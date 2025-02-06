#include <iostream>
 
int main() {
 
    std::ios::sync_with_stdio(0);
    
    int testcases;
    std::cin >> testcases;
    
    int maxVote = 0;
    int maxVIndex = 0;
    for(int i = 0; i < testcases; i++) {
        int votes;
        std::cin >> votes;
        if (maxVote == std::max(maxVote, votes)) continue; // Tie
        maxVote = std::max(maxVote, votes);
        if (maxVote == votes) maxVIndex = i;
    }
    
    printf("%s\n", (maxVIndex == 0 ?  "S" : "N"));
 
    return 0;
}