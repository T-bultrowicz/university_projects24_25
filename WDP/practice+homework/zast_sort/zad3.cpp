#include<bits/stdc++.h>
using namespace std;

float przedzial(const vector <float> s, int k, int* d) {
    vector <float> t = s;
    sort(t.begin(), t.end());
    deque <float> gas;
    gas.push_back(t[0]);
    int p = 1, res_s = 0;
    float res;
    while(p < t.size()) {
        if(gas.back() - gas.front() <= 2*k) {
            if(gas.size() > res_s) {
                res_s = gas.size();
                res = (gas.back() + gas.front()) / 2;
            }
            gas.push_back(t[p++]);
        } else {
            gas.pop_front();
        }
    }
    if(gas.back() - gas.front() <= 2*k) {
        if(gas.size() > res_s) {
            res = (gas.back() + gas.front()) / 2;
            res_s = gas.size();
        }
    }
    *d = res_s;
    return res;
}

int main() {
    int a, c, l;
    if(scanf("%d %d", &a, &c) != 2) {
        return -1;
    }
    vector <float> b;
    float b_acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%f", &b_acc) != 1) {
            return -1;
        }
        b.push_back(b_acc);
    }
    printf("%f", przedzial(b, c, &l));
    printf("  %d", l);
    return 0;
}