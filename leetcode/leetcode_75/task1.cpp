#include<bits/stdc++.h>
using namespace std;

int main() {
    string word1, word2, res;
    cin >> word1 >> word2;
    size_t l = min(word1.size(), word2.size());
    for(size_t i = 0; i < l; i++) {
        res.push_back(word1[i]);
        res.push_back(word2[i]);
    }
    if(word1.size() < word2.size()) {
        res += word2.substr(word1.size(), word2.size() - word1.size());
    } else {
        res += word1.substr(word2.size(), word1.size() - word2.size());
    }
    cout << res;
    return 0;
}