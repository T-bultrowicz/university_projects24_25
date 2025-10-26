#include<bits/stdc++.h>
using namespace std;

int trojki(const vector <int> b) {
    vector <int> tab = b;
    sort(tab.begin(), tab.end());
    int res = 0, l, p;
    for(int i = 0; i < tab.size(); i++) {
        l = i - 1, p = tab.size() - 1;
        while(l >= 0 && p > i) {
            if(tab[l] + tab[i] == tab[p]) {
                res++;
                l--;
            } else if(tab[l] + tab[i] > tab[p]) {
                l--;
            } else {
                p--;
            }
        }
    }
    return res;
}


int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector <int> b;
    for(int i = 0; i < a; i++) {
        b.push_back(0);
        if(scanf("%d", &b[i]) != 1) {
            return -1;
        }
    }
    printf("%d", trojki(b));
    return 0;
}