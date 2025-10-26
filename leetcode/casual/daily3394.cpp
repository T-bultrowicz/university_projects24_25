#include<bits/stdc++.h>
using namespace std;

bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
    vector<pair<int,int>> konce;
    for(auto a: rectangles) {
        konce.push_back({a[0], 1});
        konce.push_back({a[2], -1});
    }
    sort(konce.begin(), konce.end());
    int ile_w_trakcie = 1, linia = 0;
    for(int i = 1; i < konce.size() - 1; i++) {
        ile_w_trakcie += konce[i].second;
        if(!ile_w_trakcie) linia++;
    }
    if(linia >= 2) return true;
    ile_w_trakcie = 1, linia = 0;
    konce.clear();
    for(auto a : rectangles) {
        konce.push_back({a[1], 1});
        konce.push_back({a[3], -1});
    }
    sort(konce.begin(), konce.end());
    for(int i = 1; i < konce.size() - 1; i++) {
        ile_w_trakcie += konce[i].second;
        if(!ile_w_trakcie) linia++;
    }
    if(linia >= 2) return true;
    return false;
}

int main() {
    int n, x;
    cin >> n >> x;
    vector <vector<int>> t(x, vector<int>(4));
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < 4; j++) {
            cin >> t[i][j];
        }
    }
    cout << checkValidCuts(n, t);
    return 0;
}