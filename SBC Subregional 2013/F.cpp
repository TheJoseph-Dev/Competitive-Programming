#include <stdio.h>

int main() {
 
    // P = SUM ALL
    // P = 2pi*r
    // r = P/2*pi
    // Notice that each point from the triangle must be separated by 120° from the center
    // So 120*pi/180 * r = arc length to form 120°
    // Choose a point, check if it walks arclength
    
    int n;
    while(scanf("%d", &n) != EOF) {
        unsigned int P = 0, pDists[100001], delPoints[100001] = {0};
        for(int i = 0; i < n; i++) {
            int p;
            scanf("%d", &p);
            P += p;
            if(i == 0) pDists[i] = p;
            else pDists[i] = pDists[i-1] + p;
        }
        
        /*
        double r = P/(2*PI);
        double rad120 = 120*PI/180;
        (P/(2*PI)) * (120*PI/180)
        120P*PI/(360PI)
        P/3  
        */
        unsigned int step = (P/3);

        int triCounter = 0;
        for(int i = 0; i < n; i++) {
            if(delPoints[i]) continue;
            int l = i, r = n-1, j = -1;
            while(l <= r) {
                int mid = (l+r)/2;
                int len = pDists[mid]-pDists[i];
                if(len == step) {
                    j = mid;
                    break;
                }

                if(len < step) l = mid+1;
                else r = mid-1;
            }

            if(j == -1) continue;

            int k = -1;
            l = j; r = n-1;
            while(l <= r) {
                int mid = (l+r)/2;
                int len = pDists[mid]-pDists[j];
                if(len == step) {
                    k = mid;
                    break;
                }

                if(len < step) l = mid+1;
                else r = mid-1;
            }

            if(k == -1) {
                delPoints[j] = 1;
                continue;
            }

            delPoints[j%n] = delPoints[k%n] = 1;
            triCounter++;
        }
        
        printf("%d\n", triCounter);
    }
 
    return 0;
}