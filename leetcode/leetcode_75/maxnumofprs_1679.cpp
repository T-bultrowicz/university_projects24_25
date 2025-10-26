#include<bits/stdc++.h>
using namespace std;

int maxOperations(vector<int>& t, int k) {
    sort(t.begin(), t.end());
    int res = 0;
    int i = 0, j = t.size() - 1;
    while(i < j) {
        if(t[i] + t[j] == k) {
            res++;
            i++;
            j--;
        } else if(t[i] + t[j] < k) {
            i++;
        } else {
            j--;
        }
    }
    return res;
}

int maxOperationsdwa(vector<int>& t, int k) {
    unordered_set<int> siu;
    int res = 0;
    for(int i = 0; i < t.size(); i++) {
        auto x = siu.find(k - t[i]);
        if(x != siu.end()) {
            res++;
            siu.erase(x);
        } else {
            siu.insert(t[i]);
        }
    }
    return res;
}


int main() {
    int x, k;
    cin >> x >>  k;
    vector<int> tab(x);
    for(int i = 0; i < x; i++) {
        cin >> tab[i];
    }
    cout << maxOperationsdwa(tab, k);
    return 0;
}