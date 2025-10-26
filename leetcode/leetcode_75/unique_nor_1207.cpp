#include<bits/stdc++.h>
using namespace std;

bool uniqueOccurrences(vector<int>& arr) {
    unordered_map<int,int> bam;
    unordered_set<int> res;
    for(int i : arr) {
        auto x = bam.find(i);
        if(x == bam.end()) {
            bam.insert({i,1});
        } else {
            x->second += 1;
        }
    }
    for(auto x = bam.begin(); x != bam.end(); x++) {
        auto a = res.find(x->second);
        if(a != res.end()) {
            return false;
        } else {
            res.insert(x->second);
        }
    }
    return true;
}

int main() {
    int x;
    cin >> x;
    vector<int>t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << uniqueOccurrences(t);
    return 0;
}