#include<bits/stdc++.h>
using namespace std;

float zlewki(const vector <float> t, int k) {
    queue <float> s;
    vector <float> t_cp = t;
    int ind = 0;
    float fir, sec;
    sort(t_cp.begin(), t_cp.end());
    for(int i = 0; i < k; i++) {
        if(s.empty()) {
            fir = t_cp[ind++];
        } else if(ind == t_cp.size()) {
            fir = s.front();
            s.pop();
        } else {
            if(s.front() < t_cp[ind]) {
                fir = s.front();
                s.pop();
            } else {
                fir = t_cp[ind++];
            }
        }
        if(s.empty()) {
            sec = t_cp[ind++];
        } else if(ind == t_cp.size()) {
            sec = s.front();
            s.pop();
        } else {
            if(s.front() < t_cp[ind]) {
                sec = s.front();
                s.pop();
            } else {
                sec = t_cp[ind++];
            }
        }
        s.push(fir + sec);       
    }
    if(s.empty()) {
        fir = t_cp[ind++];
    } else if(ind == t_cp.size()) {
        fir = s.front();
        s.pop();
    } else {
        if(s.front() < t_cp[ind]) {
            fir = s.front();
            s.pop();
        } else {
            fir = t_cp[ind++];
        }
    }
    return fir;
}

int main() {
    int a, k;
    if(scanf("%d %d", &a, &k) != 2) {
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
    printf("%f", zlewki(b, k));
    return 0;
}