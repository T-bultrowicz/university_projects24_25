#include<bits/stdc++.h>
using namespace std;

vector <float> przekladaniec(const vector <float> s) {
    vector <float> t = s, res;
    sort(t.begin(), t.end());
    for(int i = 0; i < t.size(); i++) {
        if(i % 2 == 0) {
            res.push_back(t[i / 2]);
        } else {
            res.push_back(t[t.size() - 1 - (i / 2)]);
        }
    }
    return res;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector <float> b, res;
    float b_acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%f", &b_acc) != 1) {
            return -1;
        }
        b.push_back(b_acc);
    }
    res = przekladaniec(b);
    for(int l = 0; l < res.size(); l++) {
        printf("%f ", res[l]);
    }
    printf("\n");
    return 0;
}