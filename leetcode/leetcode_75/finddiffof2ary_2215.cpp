#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> findDifference(vector<int>& t, vector<int>& t2) {
    unordered_map<int, bool> set1, set2;
    for(int i : t) set1.insert({i, true});
    for(int i : t2) {
        auto x = set1.find(i);
        if(x != set1.end()) {
            x->second = false;
        } else {
            set2.insert({i,true});
        }
    }
    vector <vector <int>> res(2);
    for(auto i = set1.begin(); i != set1.end(); i++) {
        if(i->second) res[0].push_back(i->first);
    }
    for(auto i = set2.begin(); i != set2.end(); i++) {
        res[1].push_back(i->first);
    }
    return res;
}

int main() {
    int x, y;
    cin >> x >> y;
    vector<int> tab(x), tab2(y);
    for(int i = 0; i < x; i++) {
        cin >> tab[i];
    }
    for(int i = 0; i < y; i++) {
        cin >> tab2[i];
    }
    vector <vector <int>> res = findDifference(tab, tab2);
    for(auto a : res) {
        for(int j : a) {
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}