#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d", &n);

    char secret[6], dict[1001][6];
    for(int i = 0; i < n; i++)
        scanf("%s", dict[i]);
    
    strcpy(secret, dict[0]);

    int q;
    scanf("%d", &q);

    while(q--) {
        char guess[6];
        scanf("%s", guess);
        
        int count = 0;
        for(int i = 0; i < n; i++) {
            bool shouldCount = true;
            int ban[6], b = 0, expected[6], ex = 0;
            for(int c = 0; c < 5 && shouldCount; c++)
                if(guess[c] == '*' && secret[c] != dict[i][c]) shouldCount = false;
                else if(guess[c] == '!') expected[ex++] = c;
                else if(guess[c] == 'X') ban[b++] = c;

            for(int c = 0; c < b && shouldCount; c++)
                for(int s = 0; s < 5; s++)
                    if(secret[s] == dict[i][ban[c]]) shouldCount = false;
            
            for(int c = 0; c < ex && shouldCount; c++) {
                bool found = false;
                for(int s = 0; s < 5 && !found; s++)
                    found |= (secret[s] == dict[i][expected[c]] && s != expected[c]);
                shouldCount &= found;
            }

            count += shouldCount;
        }

        printf("%d\n", count);
    }

    return 0;
}