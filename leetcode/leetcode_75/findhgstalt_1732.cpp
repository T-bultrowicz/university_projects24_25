#include<bits/stdc++.h>
using namespace std;

int largestAltitude(vector<int>& g) {
    int curr = 0, maks = 0;
    for(int i : g) {
        curr += i;
        maks = max(maks, curr); 
    }
    return maks;
}

int main() {
    int x;
    cin >> x;
    vector<int> tab(x);
    for(int i = 0; i < x; i++) {
        cin >> tab[i];
    }
    cout << largestAltitude(tab);
    return 0;
}