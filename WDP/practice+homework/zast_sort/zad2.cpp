#include<bits/stdc++.h>
using namespace std;

bool sprawdz_(const vector <int> s) {
    vector <int> b = s;
    sort(b.begin(), b.end());
    for(int i = 0;i < b.size() - 2; i++) {
        if(b[i] + b[i + 1] > b[i + 2]) {
            return true;
        }
    }
    return false;
}

bool trojkat (const vector <int> s) {
    if(s.size() > 46) {
        return true;
    } else {
        return sprawdz_(s);
    }
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector <int> b;
    int b_acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &b_acc) != 1) {
            return -1;
        }
        b.push_back(b_acc);
    }
    if(trojkat(b)) {
        printf("true");
    } else {
        printf("false");
    }
    return 0;
}