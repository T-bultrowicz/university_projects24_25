#include<bits/stdc++.h>
using namespace std;

int pivotIndex(vector<int>& t) {
    int sum_t = 0, l = 0;
    for(int i : t) sum_t += i;
    for(int i = 0; i < t.size(); i++) {
        if(l == sum_t - t[i]) return i;
        l += t[i];
        sum_t -= t[i];
    }
    return -1;
}

int main() {
    int x;
    cin >> x;
    vector<int> tab(x);
    for(int i = 0; i < x; i++) {
        cin >> tab[i];
    }
    cout << pivotIndex(tab);
    return 0;
}