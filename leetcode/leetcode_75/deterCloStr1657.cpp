#include<bits/stdc++.h>
using namespace std;

bool closeStrings(string word1, string word2) {
    map<char,int> occurences1, occurences2;
    for(char a : word1) {
        auto x = occurences1.find(a);
        if(x == occurences1.end()) {
            occurences1.insert({a,1});
        } else {
            x->second += 1;
        }
    }
    for(char b : word2) {
        auto x = occurences2.find(b);
        if(occurences1.find(b) == occurences1.end()) return false;
        if(x == occurences2.end()) {
            occurences2.insert({b,1});
        } else {
            x->second += 1;
        }
    }
    multiset<int> res;
    for(auto a = occurences1.begin(); a != occurences1.end(); a++) {
        res.insert(a->second);
    }
    for(auto a = occurences2.begin(); a != occurences2.end(); a++) {
        auto x = res.find(a->second);
        if(x == res.end()) return false;
        else res.erase(x);
    }
    return true;
}

int main() {
    string a, b;
    cin >> a >> b;
    cout << closeStrings(a, b);
    return 0;
}

