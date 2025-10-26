#include<bits/stdc++.h>
#include<time.h>
using namespace std;

struct compare {
    bool operator()(int& p1, int& p2) {
        return p1 > p2;
    }
};

int main() {
    clock_t start = clock();
    int a, b, c, d;
    priority_queue<int, vector<int>, compare> drewno;
    scanf("%d", &a);
    for(int i = 0; i < a; i++) {
        scanf("%d", &b);
        if(b == 0) {
            if(!drewno.empty()) {
                d = drewno.top();
            } else {
                //printf("-1\n");
            }
        } else if(b == 1) {
            scanf("%d", &c);
            drewno.push(c);
        } else {
            if(!drewno.empty()) {
                drewno.pop();
            }
        }
    }
    clock_t end = clock();
    printf("%.6f ", (double) (end - start) / 1000000);
    return 0;
}