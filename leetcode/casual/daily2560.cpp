#include<bits/stdc++.h>
using namespace std;

int zlicz(vector<int>& t, int war) {
    int res = 0;
    bool wzieto = false;
    for(int i : t) {
        if(i <= war && !wzieto) {
            wzieto = true;
            res++;
        } else {
            wzieto = false;
        }
    }
    return res;
}

int minCapability(vector<int>& t, int k) {
    int r = 0;
    for(int i : t) r = max(r ,i);
    int l = 0, mid;
    while(l < r) {
        mid = l + r;
        mid >>= 1;
        if(zlicz(t, mid) >= k) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int main() {
    int x, k;
    cin >> x >> k;
    vector<int> t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << minCapability(t, k);
    return 0;
}